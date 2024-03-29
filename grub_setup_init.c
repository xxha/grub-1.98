/* This file is automatically generated by geninit.sh. DO NOT EDIT! */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2002,2005,2007  Free Software Foundation, Inc.
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

#include <grub_setup_init.h>

void
grub_init_all (void)
{
  grub_affs_init ();
  grub_tar_init ();
  grub_cpio_init ();
  grub_ext2_init ();
  grub_fat_init ();
  grub_hfs_init ();
  grub_hfsplus_init ();
  grub_iso9660_init ();
  grub_udf_init ();
  grub_jfs_init ();
  grub_minix_init ();
  grub_ntfs_init ();
  grub_ntfscomp_init ();
  grub_reiserfs_init ();
  grub_sfs_init ();
  grub_ufs2_init ();
  grub_ufs1_init ();
  grub_xfs_init ();
  grub_befs_be_init ();
  grub_befs_init ();
  grub_afs_be_init ();
  grub_afs_init ();
  grub_pc_partition_map_init ();
  grub_gpt_partition_map_init ();
  grub_raid_init ();
  grub_mdraid_init ();
  grub_lvm_init ();
}
void
grub_fini_all (void)
{
  grub_affs_fini ();
  grub_tar_fini ();
  grub_cpio_fini ();
  grub_ext2_fini ();
  grub_fat_fini ();
  grub_hfs_fini ();
  grub_hfsplus_fini ();
  grub_iso9660_fini ();
  grub_udf_fini ();
  grub_jfs_fini ();
  grub_minix_fini ();
  grub_ntfs_fini ();
  grub_ntfscomp_fini ();
  grub_reiserfs_fini ();
  grub_sfs_fini ();
  grub_ufs2_fini ();
  grub_ufs1_fini ();
  grub_xfs_fini ();
  grub_befs_be_fini ();
  grub_befs_fini ();
  grub_afs_be_fini ();
  grub_afs_fini ();
  grub_pc_partition_map_fini ();
  grub_gpt_partition_map_fini ();
  grub_raid_fini ();
  grub_mdraid_fini ();
  grub_lvm_fini ();
}
