/* grub-setup.c - make GRUB usable */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 1999,2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <grub/types.h>
#include <grub/util/misc.h>
#include <grub/device.h>
#include <grub/disk.h>
#include <grub/file.h>
#include <grub/fs.h>
#include <grub/partition.h>
#include <grub/msdos_partition.h>
#include <grub/gpt_partition.h>
#include <grub/env.h>
#include <grub/util/hostdisk.h>
#include <grub/machine/boot.h>
#include <grub/machine/kernel.h>
#include <grub/term.h>
#include <grub/i18n.h>
#include <grub/util/raid.h>
#include <grub/util/lvm.h>
#include <grub/util/getroot.h>

static const grub_gpt_part_type_t grub_gpt_partition_type_bios_boot = GRUB_GPT_PARTITION_TYPE_BIOS_BOOT;

#include <grub_setup_init.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <assert.h>
#include "progname.h"

#define _GNU_SOURCE	1
#include <getopt.h>

#define DEFAULT_BOOT_FILE	"boot.img"
#define DEFAULT_CORE_FILE	"core.img"

void
grub_putchar (int c)
{
  putchar (c);
}

int
grub_getkey (void)
{
  return -1;
}

struct grub_handler_class grub_term_input_class;
struct grub_handler_class grub_term_output_class;

void
grub_refresh (void)
{
  fflush (stdout);
}

static void
setup (const char *dir,
       const char *boot_file, const char *core_file,
       const char *root, const char *dest, int must_embed, int force, int fs_probe)
{
  char *boot_path, *core_path, *core_path_dev, *core_path_dev_full;
  char *boot_img, *core_img;
  size_t boot_size, core_size;
  grub_uint16_t core_sectors;
  grub_device_t root_dev, dest_dev;
  const char *dest_partmap;
  grub_uint8_t *boot_drive;
  grub_disk_addr_t *kernel_sector;
  grub_uint16_t *boot_drive_check;
  struct grub_boot_blocklist *first_block, *block;
  grub_int32_t *install_dos_part, *install_bsd_part;
  grub_int32_t dos_part, bsd_part;
  char *tmp_img;
  int i;
  grub_disk_addr_t first_sector;
  grub_uint16_t current_segment
    = GRUB_BOOT_MACHINE_KERNEL_SEG + (GRUB_DISK_SECTOR_SIZE >> 4);
  grub_uint16_t last_length = GRUB_DISK_SECTOR_SIZE;
  grub_file_t file;
  FILE *fp;
  struct { grub_uint64_t start; grub_uint64_t end; } embed_region;
  embed_region.start = embed_region.end = ~0UL;

  auto void NESTED_FUNC_ATTR save_first_sector (grub_disk_addr_t sector, unsigned offset,
			       unsigned length);
  auto void NESTED_FUNC_ATTR save_blocklists (grub_disk_addr_t sector, unsigned offset,
			     unsigned length);

  auto int NESTED_FUNC_ATTR find_usable_region_msdos (grub_disk_t disk,
						      const grub_partition_t p);
  int NESTED_FUNC_ATTR find_usable_region_msdos (grub_disk_t disk __attribute__ ((unused)),
						 const grub_partition_t p)
    {
      struct grub_msdos_partition *pcdata = p->data;

      /* There's always an embed region, and it starts right after the MBR.  */
      embed_region.start = 1;

      /* For its end offset, include as many dummy partitions as we can.  */
      if (! grub_msdos_partition_is_empty (pcdata->dos_type)
	  && ! grub_msdos_partition_is_bsd (pcdata->dos_type)
	  && embed_region.end > p->start)
	embed_region.end = p->start;

      return 0;
    }

  auto int NESTED_FUNC_ATTR find_usable_region_gpt (grub_disk_t disk,
						    const grub_partition_t p);
  int NESTED_FUNC_ATTR find_usable_region_gpt (grub_disk_t disk __attribute__ ((unused)),
					       const grub_partition_t p)
    {
      struct grub_gpt_partentry *gptdata = p->data;

      /* If there's an embed region, it is in a dedicated partition.  */
      if (! memcmp (&gptdata->type, &grub_gpt_partition_type_bios_boot, 16))
	{
	  embed_region.start = p->start;
	  embed_region.end = p->start + p->len;

	  return 1;
	}

      return 0;
    }

  void NESTED_FUNC_ATTR save_first_sector (grub_disk_addr_t sector, unsigned offset,
			  unsigned length)
    {
      grub_util_info ("the first sector is <%llu,%u,%u>",
		      sector, offset, length);

      if (offset != 0 || length != GRUB_DISK_SECTOR_SIZE)
	grub_util_error (_("the first sector of the core file is not sector-aligned"));

      first_sector = sector;
    }

  void NESTED_FUNC_ATTR save_blocklists (grub_disk_addr_t sector, unsigned offset,
			unsigned length)
    {
      struct grub_boot_blocklist *prev = block + 1;

      grub_util_info ("saving <%llu,%u,%u> with the segment 0x%x",
		      sector, offset, length, (unsigned) current_segment);

      if (offset != 0 || last_length != GRUB_DISK_SECTOR_SIZE)
	grub_util_error (_("non-sector-aligned data is found in the core file"));

      if (block != first_block
	  && (grub_le_to_cpu64 (prev->start)
	      + grub_le_to_cpu16 (prev->len)) == sector)
	prev->len = grub_cpu_to_le16 (grub_le_to_cpu16 (prev->len) + 1);
      else
	{
	  block->start = grub_cpu_to_le64 (sector);
	  block->len = grub_cpu_to_le16 (1);
	  block->segment = grub_cpu_to_le16 (current_segment);

	  block--;
	  if (block->len)
	    grub_util_error (_("the sectors of the core file are too fragmented"));
	}

      last_length = length;
      current_segment += GRUB_DISK_SECTOR_SIZE >> 4;
    }

  /* Read the boot image by the OS service.  */
  boot_path = grub_util_get_path (dir, boot_file);
  boot_size = grub_util_get_image_size (boot_path);
  if (boot_size != GRUB_DISK_SECTOR_SIZE)
    grub_util_error (_("the size of `%s' is not %u"),
		     boot_path, GRUB_DISK_SECTOR_SIZE);
  boot_img = grub_util_read_image (boot_path);
  free (boot_path);

  /* Set the addresses of variables in the boot image.  */
  boot_drive = (grub_uint8_t *) (boot_img + GRUB_BOOT_MACHINE_BOOT_DRIVE);
  kernel_sector = (grub_disk_addr_t *) (boot_img
				     + GRUB_BOOT_MACHINE_KERNEL_SECTOR);
  boot_drive_check = (grub_uint16_t *) (boot_img
					+ GRUB_BOOT_MACHINE_DRIVE_CHECK);

  core_path = grub_util_get_path (dir, core_file);
  core_size = grub_util_get_image_size (core_path);
  core_sectors = ((core_size + GRUB_DISK_SECTOR_SIZE - 1)
		  >> GRUB_DISK_SECTOR_BITS);
  if (core_size < GRUB_DISK_SECTOR_SIZE)
    grub_util_error (_("the size of `%s' is too small"), core_path);
  else if (core_size > 0xFFFF * GRUB_DISK_SECTOR_SIZE)
    grub_util_error (_("the size of `%s' is too large"), core_path);

  core_img = grub_util_read_image (core_path);

  /* Have FIRST_BLOCK to point to the first blocklist.  */
  first_block = (struct grub_boot_blocklist *) (core_img
						+ GRUB_DISK_SECTOR_SIZE
						- sizeof (*block));

  install_dos_part = (grub_int32_t *) (core_img + GRUB_DISK_SECTOR_SIZE
				       + GRUB_KERNEL_MACHINE_INSTALL_DOS_PART);
  install_bsd_part = (grub_int32_t *) (core_img + GRUB_DISK_SECTOR_SIZE
				       + GRUB_KERNEL_MACHINE_INSTALL_BSD_PART);

  /* Open the root device and the destination device.  */
  root_dev = grub_device_open (root);
  if (! root_dev)
    grub_util_error ("%s", grub_errmsg);

  dest_dev = grub_device_open (dest);
  if (! dest_dev)
    grub_util_error ("%s", grub_errmsg);

  grub_util_info ("setting the root device to `%s'", root);
  if (grub_env_set ("root", root) != GRUB_ERR_NONE)
    grub_util_error ("%s", grub_errmsg);

  /* Read the original sector from the disk.  */
  tmp_img = xmalloc (GRUB_DISK_SECTOR_SIZE);
  if (grub_disk_read (dest_dev->disk, 0, 0, GRUB_DISK_SECTOR_SIZE, tmp_img))
    grub_util_error ("%s", grub_errmsg);

  if (dest_dev->disk->partition && fs_probe)
    {
      grub_fs_t fs;
      fs = grub_fs_probe (dest_dev);
      if (! fs)
	grub_util_error (_("unable to identify a filesystem in %s; safety check can't be performed"),
			 dest_dev->disk->name);

      if (! fs->reserved_first_sector)
	grub_util_error (_("%s appears to contain a %s filesystem which isn't known to "
			   "reserve space for DOS-style boot.  Installing GRUB there could "
			   "result in FILESYSTEM DESTRUCTION if valuable data is overwritten "
			   "by grub-setup (--skip-fs-probe disables this "
			   "check, use at your own risk)"), dest_dev->disk->name, fs->name);
    }

  /* Copy the possible DOS BPB.  */
  memcpy (boot_img + GRUB_BOOT_MACHINE_BPB_START,
	  tmp_img + GRUB_BOOT_MACHINE_BPB_START,
	  GRUB_BOOT_MACHINE_BPB_END - GRUB_BOOT_MACHINE_BPB_START);

  /* Copy the possible partition table.  */
  if (dest_dev->disk->has_partitions)
    memcpy (boot_img + GRUB_BOOT_MACHINE_WINDOWS_NT_MAGIC,
	    tmp_img + GRUB_BOOT_MACHINE_WINDOWS_NT_MAGIC,
	    GRUB_BOOT_MACHINE_PART_END - GRUB_BOOT_MACHINE_WINDOWS_NT_MAGIC);

  free (tmp_img);

  /* If DEST_DRIVE is a hard disk, enable the workaround, which is
     for buggy BIOSes which don't pass boot drive correctly. Instead,
     they pass 0x00 or 0x01 even when booted from 0x80.  */
  if (dest_dev->disk->id & 0x80)
    /* Replace the jmp (2 bytes) with double nop's.  */
    *boot_drive_check = 0x9090;

  /* If we hardcoded drive as part of prefix, we don't want to
     override the current setting.  */
  if (*install_dos_part != -2)
    {
      /* Embed information about the installed location.  */
      if (root_dev->disk->partition)
	{
	  if (strcmp (root_dev->disk->partition->partmap->name,
		      "part_msdos") == 0)
	    {
	      struct grub_msdos_partition *pcdata =
		root_dev->disk->partition->data;
	      dos_part = pcdata->dos_part;
	      bsd_part = pcdata->bsd_part;
	    }
	  else if (strcmp (root_dev->disk->partition->partmap->name,
			   "part_gpt") == 0)
	    {
	      dos_part = root_dev->disk->partition->index;
	      bsd_part = -1;
	    }
	  else
	    grub_util_error (_("no DOS-style partitions found"));
	}
      else
	dos_part = bsd_part = -1;
    }
  else
    {
      dos_part = grub_le_to_cpu32 (*install_dos_part);
      bsd_part = grub_le_to_cpu32 (*install_bsd_part);
    }

  grub_util_info ("dos partition is %d, bsd partition is %d",
		  dos_part, bsd_part);

  if (! dest_dev->disk->has_partitions)
    {
      grub_util_warn (_("Attempting to install GRUB to a partitionless disk.  This is a BAD idea."));
      goto unable_to_embed;
    }

  if (dest_dev->disk->partition)
    {
      grub_util_warn (_("Attempting to install GRUB to a partition instead of the MBR.  This is a BAD idea."));
      goto unable_to_embed;
    }

  /* Unlike root_dev, with dest_dev we're interested in the partition map even
     if dest_dev itself is a whole disk.  */
  auto int NESTED_FUNC_ATTR identify_partmap (grub_disk_t disk,
					      const grub_partition_t p);
  int NESTED_FUNC_ATTR identify_partmap (grub_disk_t disk __attribute__ ((unused)),
					 const grub_partition_t p)
    {
      dest_partmap = p->partmap->name;
      return 1;
    }
  dest_partmap = 0;
  grub_partition_iterate (dest_dev->disk, identify_partmap);

  if (! dest_partmap)
    {
      grub_util_warn (_("Attempting to install GRUB to a partitionless disk.  This is a BAD idea."));
      goto unable_to_embed;
    }

  if (strcmp (dest_partmap, "part_msdos") == 0)
    grub_partition_iterate (dest_dev->disk, find_usable_region_msdos);
  else if (strcmp (dest_partmap, "part_gpt") == 0)
    grub_partition_iterate (dest_dev->disk, find_usable_region_gpt);
  else
    grub_util_error (_("No DOS-style partitions found"));

  if (embed_region.end == embed_region.start)
    {
      if (! strcmp (dest_partmap, "part_msdos"))
	grub_util_warn (_("This msdos-style partition label has no post-MBR gap; embedding won't be possible!"));
      else
	grub_util_warn (_("This GPT partition label has no BIOS Boot Partition; embedding won't be possible!"));
      goto unable_to_embed;
    }

  if ((unsigned long) core_sectors > embed_region.end - embed_region.start)
    {
      if (core_sectors > 62)
	grub_util_warn (_("Your core.img is unusually large.  It won't fit in the embedding area."));
      else /* embed_region.end - embed_region.start < 62 */
	grub_util_warn (_("Your embedding area is unusually small.  core.img won't fit in it."));
      goto unable_to_embed;
    }


  grub_util_info ("the core image will be embedded at sector 0x%llx", embed_region.start);

  *install_dos_part = grub_cpu_to_le32 (dos_part);
  *install_bsd_part = grub_cpu_to_le32 (bsd_part);

  /* The first blocklist contains the whole sectors.  */
  first_block->start = grub_cpu_to_le64 (embed_region.start + 1);

  /* These are filled elsewhere.  Verify them just in case.  */
  assert (first_block->len == grub_host_to_target16 (core_sectors - 1));
  assert (first_block->segment == grub_host_to_target16 (GRUB_BOOT_MACHINE_KERNEL_SEG
						    + (GRUB_DISK_SECTOR_SIZE >> 4)));

  /* Make sure that the second blocklist is a terminator.  */
  block = first_block - 1;
  block->start = 0;
  block->len = 0;
  block->segment = 0;

  /* Write the core image onto the disk.  */
  if (grub_disk_write (dest_dev->disk, embed_region.start, 0, core_size, core_img))
    grub_util_error ("%s", grub_errmsg);

  /* FIXME: can this be skipped?  */
  *boot_drive = 0xFF;

  *kernel_sector = grub_cpu_to_le64 (embed_region.start);

  /* Write the boot image onto the disk.  */
  if (grub_disk_write (dest_dev->disk, 0, 0, GRUB_DISK_SECTOR_SIZE,
		       boot_img))
    grub_util_error ("%s", grub_errmsg);

  goto finish;

unable_to_embed:

  if (must_embed)
    grub_util_error (_("embedding is not possible, but this is required when "
		       "the root device is on a RAID array or LVM volume"));

  grub_util_warn (_("Embedding is not possible.  GRUB can only be installed in this "
		    "setup by using blocklists.  However, blocklists are UNRELIABLE and "
		    "its use is discouraged."));
  if (! force)
    grub_util_error (_("if you really want blocklists, use --force"));

  /* Make sure that GRUB reads the identical image as the OS.  */
  tmp_img = xmalloc (core_size);
  core_path_dev_full = grub_util_get_path (dir, core_file);
  core_path_dev = make_system_path_relative_to_its_root (core_path_dev_full);
  free (core_path_dev_full);

  /* It is a Good Thing to sync two times.  */
  sync ();
  sync ();

#define MAX_TRIES	5

  for (i = 0; i < MAX_TRIES; i++)
    {
      grub_util_info ((i == 0) ? _("attempting to read the core image `%s' from GRUB")
		      : _("attempting to read the core image `%s' from GRUB again"),
		      core_path_dev);

      grub_disk_cache_invalidate_all ();

      file = grub_file_open (core_path_dev);
      if (file)
	{
	  if (grub_file_size (file) != core_size)
	    grub_util_info ("succeeded in opening the core image but the size is different (%d != %d)",
			    (int) grub_file_size (file), (int) core_size);
	  else if (grub_file_read (file, tmp_img, core_size)
		   != (grub_ssize_t) core_size)
	    grub_util_info ("succeeded in opening the core image but cannot read %d bytes",
			    (int) core_size);
	  else if (memcmp (core_img, tmp_img, core_size) != 0)
	    {
#if 0
	      FILE *dump;
	      FILE *dump2;

	      dump = fopen ("dump.img", "wb");
	      if (dump)
		{
		  fwrite (tmp_img, 1, core_size, dump);
		  fclose (dump);
		}

	      dump2 = fopen ("dump2.img", "wb");
	      if (dump2)
		{
		  fwrite (core_img, 1, core_size, dump2);
		  fclose (dump2);
		}

#endif
	      grub_util_info ("succeeded in opening the core image but the data is different");
	    }
	  else
	    {
	      grub_file_close (file);
	      break;
	    }

	  grub_file_close (file);
	}
      else
	grub_util_info ("couldn't open the core image");

      if (grub_errno)
	grub_util_info ("error message = %s", grub_errmsg);

      grub_errno = GRUB_ERR_NONE;
      sync ();
      sleep (1);
    }

  if (i == MAX_TRIES)
    grub_util_error (_("cannot read `%s' correctly"), core_path_dev);

  /* Clean out the blocklists.  */
  block = first_block;
  while (block->len)
    {
      block->start = 0;
      block->len = 0;
      block->segment = 0;

      block--;

      if ((char *) block <= core_img)
	grub_util_error (_("no terminator in the core image"));
    }

  /* Now read the core image to determine where the sectors are.  */
  file = grub_file_open (core_path_dev);
  if (! file)
    grub_util_error ("%s", grub_errmsg);

  file->read_hook = save_first_sector;
  if (grub_file_read (file, tmp_img, GRUB_DISK_SECTOR_SIZE)
      != GRUB_DISK_SECTOR_SIZE)
    grub_util_error (_("failed to read the first sector of the core image"));

  block = first_block;
  file->read_hook = save_blocklists;
  if (grub_file_read (file, tmp_img, core_size - GRUB_DISK_SECTOR_SIZE)
      != (grub_ssize_t) core_size - GRUB_DISK_SECTOR_SIZE)
    grub_util_error (_("failed to read the rest sectors of the core image"));

  grub_file_close (file);

  free (core_path_dev);
  free (tmp_img);

  *kernel_sector = grub_cpu_to_le64 (first_sector);

  /* FIXME: can this be skipped?  */
  *boot_drive = 0xFF;

  *install_dos_part = grub_cpu_to_le32 (dos_part);
  *install_bsd_part = grub_cpu_to_le32 (bsd_part);

  /* Write the first two sectors of the core image onto the disk.  */
  grub_util_info ("opening the core image `%s'", core_path);
  fp = fopen (core_path, "r+b");
  if (! fp)
    grub_util_error (_("cannot open `%s'"), core_path);

  grub_util_write_image (core_img, GRUB_DISK_SECTOR_SIZE * 2, fp);
  fclose (fp);

  /* Write the boot image onto the disk.  */
  if (grub_disk_write (dest_dev->disk, 0, 0, GRUB_DISK_SECTOR_SIZE, boot_img))
    grub_util_error ("%s", grub_errmsg);

 finish:

  /* Sync is a Good Thing.  */
  sync ();

  free (core_path);
  free (core_img);
  free (boot_img);
  grub_device_close (dest_dev);
  grub_device_close (root_dev);
}

static struct option options[] =
  {
    {"boot-image", required_argument, 0, 'b'},
    {"core-image", required_argument, 0, 'c'},
    {"directory", required_argument, 0, 'd'},
    {"device-map", required_argument, 0, 'm'},
    {"root-device", required_argument, 0, 'r'},
    {"force", no_argument, 0, 'f'},
    {"skip-fs-probe", no_argument, 0, 's'},
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'V'},
    {"verbose", no_argument, 0, 'v'},
    {0, 0, 0, 0}
  };

static void
usage (int status)
{
  if (status)
    fprintf (stderr, _("Try `%s --help' for more information.\n"), program_name);
  else
    printf (_("\
Usage: %s [OPTION]... DEVICE\n\
\n\
Set up images to boot from DEVICE.\n\
DEVICE must be a GRUB device (e.g. `(hd0,1)').\n\
\n\
  -b, --boot-image=FILE   use FILE as the boot image [default=%s]\n\
  -c, --core-image=FILE   use FILE as the core image [default=%s]\n\
  -d, --directory=DIR     use GRUB files in the directory DIR [default=%s]\n\
  -m, --device-map=FILE   use FILE as the device map [default=%s]\n\
  -r, --root-device=DEV   use DEV as the root device [default=guessed]\n\
  -f, --force             install even if problems are detected\n\
  -s, --skip-fs-probe     do not probe for filesystems in DEVICE\n\
  -h, --help              display this message and exit\n\
  -V, --version           print version information and exit\n\
  -v, --verbose           print verbose messages\n\
\n\
Report bugs to <%s>.\n\
"),
	    program_name,
	    DEFAULT_BOOT_FILE, DEFAULT_CORE_FILE, DEFAULT_DIRECTORY,
	    DEFAULT_DEVICE_MAP, PACKAGE_BUGREPORT);

  exit (status);
}

static char *
get_device_name (char *dev)
{
  size_t len = strlen (dev);

  if (dev[0] != '(' || dev[len - 1] != ')')
    return 0;

  dev[len - 1] = '\0';
  return dev + 1;
}

int
main (int argc, char *argv[])
{
  char *boot_file = 0;
  char *core_file = 0;
  char *dir = 0;
  char *dev_map = 0;
  char *root_dev = 0;
  char *dest_dev;
  int must_embed = 0, force = 0, fs_probe = 1;

  set_program_name (argv[0]);

  grub_util_init_nls ();

  /* Check for options.  */
  while (1)
    {
      int c = getopt_long (argc, argv, "b:c:d:m:r:hVvf", options, 0);

      if (c == -1)
	break;
      else
	switch (c)
	  {
	  case 'b':
	    if (boot_file)
	      free (boot_file);

	    boot_file = xstrdup (optarg);
	    break;

	  case 'c':
	    if (core_file)
	      free (core_file);

	    core_file = xstrdup (optarg);
	    break;

	  case 'd':
	    if (dir)
	      free (dir);

	    dir = xstrdup (optarg);
	    break;

	  case 'm':
	    if (dev_map)
	      free (dev_map);

	    dev_map = xstrdup (optarg);
	    break;

	  case 'r':
	    if (root_dev)
	      free (root_dev);

	    root_dev = xstrdup (optarg);
	    break;

	  case 'f':
	    force = 1;
	    break;

	  case 's':
	    fs_probe = 0;
	    break;

	  case 'h':
	    usage (0);
	    break;

	  case 'V':
	    printf ("grub-setup (%s) %s\n", PACKAGE_NAME, PACKAGE_VERSION);
	    return 0;

	  case 'v':
	    verbosity++;
	    break;

	  default:
	    usage (1);
	    break;
	  }
    }

  if (verbosity > 1)
    grub_env_set ("debug", "all");

  /* Obtain DEST_DEV.  */
  if (optind >= argc)
    {
      fprintf (stderr, _("No device is specified.\n"));
      usage (1);
    }

  if (optind + 1 != argc)
    {
      fprintf (stderr, _("Unknown extra argument `%s'.\n"), argv[optind + 1]);
      usage (1);
    }

  /* Initialize the emulated biosdisk driver.  */
  grub_util_biosdisk_init (dev_map ? : DEFAULT_DEVICE_MAP);

  /* Initialize all modules. */
  grub_init_all ();

  dest_dev = get_device_name (argv[optind]);
  if (! dest_dev)
    {
      /* Possibly, the user specified an OS device file.  */
      dest_dev = grub_util_get_grub_dev (argv[optind]);
      if (! dest_dev)
	{
	  fprintf (stderr, _("Invalid device `%s'.\n"), argv[optind]);
	  usage (1);
	}
    }
  else
    /* For simplicity.  */
    dest_dev = xstrdup (dest_dev);

  if (root_dev)
    {
      char *tmp = get_device_name (root_dev);

      if (! tmp)
	grub_util_error (_("invalid root device `%s'"), root_dev);

      tmp = xstrdup (tmp);
      free (root_dev);
      root_dev = tmp;
    }
  else
    {
      root_dev = grub_util_get_grub_dev (grub_guess_root_device (dir ? : DEFAULT_DIRECTORY));
      if (! root_dev)
	{
	  grub_util_info ("guessing the root device failed, because of `%s'",
			  grub_errmsg);
	  grub_util_error (_("cannot guess the root device. Specify the option `--root-device'"));
	}
    }

#ifdef __linux__
  if (grub_util_lvm_isvolume (root_dev))
    must_embed = 1;

  if (root_dev[0] == 'm' && root_dev[1] == 'd'
      && root_dev[2] >= '0' && root_dev[2] <= '9')
    {
      /* FIXME: we can avoid this on RAID1.  */
      must_embed = 1;
    }

  if (dest_dev[0] == 'm' && dest_dev[1] == 'd'
      && dest_dev[2] >= '0' && dest_dev[2] <= '9')
    {
      char **devicelist;
      int i;

      devicelist = grub_util_raid_getmembers (dest_dev);

      for (i = 0; devicelist[i]; i++)
	{
	  setup (dir ? : DEFAULT_DIRECTORY,
		 boot_file ? : DEFAULT_BOOT_FILE,
		 core_file ? : DEFAULT_CORE_FILE,
		 root_dev, grub_util_get_grub_dev (devicelist[i]), 1, force, fs_probe);
	}
    }
  else
#endif
  /* Do the real work.  */
    setup (dir ? : DEFAULT_DIRECTORY,
	   boot_file ? : DEFAULT_BOOT_FILE,
	   core_file ? : DEFAULT_CORE_FILE,
	   root_dev, dest_dev, must_embed, force, fs_probe);

  /* Free resources.  */
  grub_fini_all ();
  grub_util_biosdisk_fini ();

  free (boot_file);
  free (core_file);
  free (dir);
  free (dev_map);
  free (root_dev);
  free (dest_dev);

  return 0;
}
