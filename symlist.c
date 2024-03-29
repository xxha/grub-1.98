/* This file is automatically generated by gensymlist.sh. DO NOT EDIT! */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2002,2006,2007,2008  Free Software Foundation, Inc.
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

#include <include/grub/boot.h>
#include <include/grub/cache.h>
#include <include/grub/device.h>
#include <include/grub/disk.h>
#include <include/grub/dl.h>
#include <include/grub/elf.h>
#include <include/grub/elfload.h>
#include <include/grub/env.h>
#include <include/grub/err.h>
#include <include/grub/file.h>
#include <include/grub/fs.h>
#include <include/grub/kernel.h>
#include <include/grub/loader.h>
#include <include/grub/misc.h>
#include <include/grub/mm.h>
#include <include/grub/net.h>
#include <include/grub/parser.h>
#include <include/grub/partition.h>
#include <include/grub/msdos_partition.h>
#include <include/grub/reader.h>
#include <include/grub/symbol.h>
#include <include/grub/term.h>
#include <include/grub/time.h>
#include <include/grub/types.h>
#include <include/grub/machine/biosdisk.h>
#include <include/grub/machine/boot.h>
#include <include/grub/machine/console.h>
#include <include/grub/machine/init.h>
#include <include/grub/machine/memory.h>
#include <include/grub/machine/loader.h>
#include <include/grub/machine/vga.h>
#include <include/grub/machine/vbe.h>
#include <include/grub/machine/kernel.h>
#include <include/grub/machine/pxe.h>
#include <include/grub/i386/pit.h>
#include <include/grub/list.h>
#include <include/grub/handler.h>
#include <include/grub/command.h>
#include <include/grub/i18n.h>
#include <include/grub/env_private.h>
#include <config.h>

#define COMPILE_TIME_ASSERT(cond) switch (0) { case 1: case !(cond): ; }

void
grub_register_exported_symbols (void)
{
  struct symtab { const char *name; void *addr; };
  struct symtab *p;
  static struct symtab tab[] =
    {
      {"grub_abort", grub_abort},
      {"grub_biosdisk_check_int13_extensions", grub_biosdisk_check_int13_extensions},
      {"grub_biosdisk_get_cdinfo_int13_extensions", grub_biosdisk_get_cdinfo_int13_extensions},
      {"grub_biosdisk_get_diskinfo_int13_extensions", grub_biosdisk_get_diskinfo_int13_extensions},
      {"grub_biosdisk_get_diskinfo_standard", grub_biosdisk_get_diskinfo_standard},
      {"grub_biosdisk_get_num_floppies", grub_biosdisk_get_num_floppies},
      {"grub_biosdisk_rw_int13_extensions", grub_biosdisk_rw_int13_extensions},
      {"grub_biosdisk_rw_standard", grub_biosdisk_rw_standard},
      {"grub_boot_drive", &grub_boot_drive},
      {"grub_chainloader_real_boot", grub_chainloader_real_boot},
      {"grub_checkkey", grub_checkkey},
      {"grub_cls", grub_cls},
      {"grub_command_list", &grub_command_list},
      {"grub_current_context", &grub_current_context},
      {"grub_device_close", grub_device_close},
      {"grub_device_iterate", grub_device_iterate},
      {"grub_device_open", grub_device_open},
      {"grub_disk_ata_pass_through", &grub_disk_ata_pass_through},
      {"grub_disk_close", grub_disk_close},
      {"grub_disk_dev_iterate", grub_disk_dev_iterate},
      {"grub_disk_dev_register", grub_disk_dev_register},
      {"grub_disk_dev_unregister", grub_disk_dev_unregister},
      {"grub_disk_firmware_fini", &grub_disk_firmware_fini},
      {"grub_disk_firmware_is_tainted", &grub_disk_firmware_is_tainted},
      {"grub_disk_get_size", grub_disk_get_size},
      {"grub_disk_open", grub_disk_open},
      {"grub_disk_read", grub_disk_read},
      {"grub_disk_write", grub_disk_write},
      {"grub_divmod64", grub_divmod64},
      {"grub_dl_get", grub_dl_get},
      {"grub_dl_iterate", grub_dl_iterate},
      {"grub_dl_load_file", grub_dl_load_file},
      {"grub_dl_load", grub_dl_load},
      {"grub_dl_ref", grub_dl_ref},
      {"grub_dl_unload", grub_dl_unload},
      {"grub_dl_unref", grub_dl_unref},
      {"grub_env_find", grub_env_find},
      {"grub_env_get", grub_env_get},
      {"grub_env_iterate", grub_env_iterate},
      {"grub_env_set", grub_env_set},
      {"grub_env_unset", grub_env_unset},
      {"grub_errmsg", &grub_errmsg},
      {"grub_errno", &grub_errno},
      {"grub_error", grub_error},
      {"grub_error_pop", grub_error_pop},
      {"grub_error_push", grub_error_push},
      {"grub_exit", grub_exit},
      {"grub_fatal", grub_fatal},
      {"grub_file_close", grub_file_close},
      {"grub_file_get_device_name", grub_file_get_device_name},
      {"grub_file_open", grub_file_open},
      {"grub_file_read", grub_file_read},
      {"grub_file_seek", grub_file_seek},
      {"grub_free", grub_free},
      {"grub_fs_autoload_hook", &grub_fs_autoload_hook},
      {"grub_fs_iterate", grub_fs_iterate},
      {"grub_fs_probe", grub_fs_probe},
      {"grub_fs_register", grub_fs_register},
      {"grub_fs_unregister", grub_fs_unregister},
      {"grub_getkey", grub_getkey},
      {"grub_getkeystatus", grub_getkeystatus},
      {"grub_get_mmap_entry", grub_get_mmap_entry},
      {"grub_get_rtc", grub_get_rtc},
      {"grub_gettext", &grub_gettext},
      {"grub_get_time_ms", grub_get_time_ms},
      {"grub_halt", grub_halt},
      {"grub_handler_class_list", &grub_handler_class_list},
      {"grub_handler_register", grub_handler_register},
      {"grub_handler_set_current", grub_handler_set_current},
      {"grub_handler_unregister", grub_handler_unregister},
      {"grub_isprint", grub_isprint},
      {"grub_isspace", grub_isspace},
      {"grub_linux16_real_boot", grub_linux16_real_boot},
      {"grub_linux_is_bzimage", &grub_linux_is_bzimage},
      {"grub_linux_prot_size", &grub_linux_prot_size},
      {"grub_linux_real_addr", &grub_linux_real_addr},
      {"grub_linux_tmp_addr", &grub_linux_tmp_addr},
      {"grub_list_insert", grub_list_insert},
      {"grub_list_iterate", grub_list_iterate},
      {"grub_list_pop", grub_list_pop},
      {"grub_list_push", grub_list_push},
      {"grub_list_remove", grub_list_remove},
      {"grub_machine_fini", grub_machine_fini},
      {"grub_machine_mmap_iterate", grub_machine_mmap_iterate},
      {"grub_malloc", grub_malloc},
      {"grub_memalign", grub_memalign},
      {"grub_memcmp", grub_memcmp},
      {"grub_memmove", grub_memmove},
      {"grub_memset", grub_memset},
      {"grub_millisleep", grub_millisleep},
      {"grub_module_iterate", grub_module_iterate},
      {"grub_named_list_find", grub_named_list_find},
      {"grub_newline_hook", &grub_newline_hook},
      {"grub_os_area_addr", &grub_os_area_addr},
      {"grub_os_area_size", &grub_os_area_size},
      {"grub_parser_class", &grub_parser_class},
      {"grub_parser_cmdline_state", grub_parser_cmdline_state},
      {"grub_parser_execute", grub_parser_execute},
      {"grub_parser_split_cmdline", grub_parser_split_cmdline},
      {"grub_partition_get_name", grub_partition_get_name},
      {"grub_partition_iterate", grub_partition_iterate},
      {"grub_partition_map_iterate", grub_partition_map_iterate},
      {"grub_partition_map_register", grub_partition_map_register},
      {"grub_partition_map_unregister", grub_partition_map_unregister},
      {"grub_partition_probe", grub_partition_probe},
      {"grub_pit_wait", grub_pit_wait},
      {"grub_print_error", grub_print_error},
      {"grub_printf_", grub_printf_},
      {"grub_printf", grub_printf},
      {"grub_prio_list_insert", grub_prio_list_insert},
      {"grub_putchar", grub_putchar},
      {"grub_putcode", grub_putcode},
      {"grub_puts_", grub_puts_},
      {"grub_puts", grub_puts},
      {"grub_pxe_call", grub_pxe_call},
      {"grub_pxe_scan", grub_pxe_scan},
      {"grub_real_dprintf", grub_real_dprintf},
      {"grub_realloc", grub_realloc},
      {"grub_reboot", grub_reboot},
      {"grub_refresh", grub_refresh},
      {"grub_register_command_prio", grub_register_command_prio},
      {"grub_register_variable_hook", grub_register_variable_hook},
      {"grub_setcolorstate", grub_setcolorstate},
      {"grub_snprintf", grub_snprintf},
      {"grub_stop_floppy", grub_stop_floppy},
      {"grub_stpcpy", grub_stpcpy},
      {"grub_strchr", grub_strchr},
      {"grub_strcmp", grub_strcmp},
      {"grub_strcpy", grub_strcpy},
      {"grub_strdup", grub_strdup},
      {"grub_strlen", grub_strlen},
      {"grub_strncmp", grub_strncmp},
      {"grub_strncpy", grub_strncpy},
      {"grub_strndup", grub_strndup},
      {"grub_strrchr", grub_strrchr},
      {"grub_strstr", grub_strstr},
      {"grub_strtoul", grub_strtoul},
      {"grub_strtoull", grub_strtoull},
      {"grub_strword", grub_strword},
      {"grub_term_inputs_disabled", &grub_term_inputs_disabled},
      {"grub_term_inputs", &grub_term_inputs},
      {"grub_term_outputs_disabled", &grub_term_outputs_disabled},
      {"grub_term_outputs", &grub_term_outputs},
      {"grub_unregister_command", grub_unregister_command},
      {"grub_utf8_to_ucs4", grub_utf8_to_ucs4},
      {"grub_vbe_bios_get_controller_info", grub_vbe_bios_get_controller_info},
      {"grub_vbe_bios_get_display_start", grub_vbe_bios_get_display_start},
      {"grub_vbe_bios_get_memory_window", grub_vbe_bios_get_memory_window},
      {"grub_vbe_bios_get_mode", grub_vbe_bios_get_mode},
      {"grub_vbe_bios_get_mode_info", grub_vbe_bios_get_mode_info},
      {"grub_vbe_bios_get_scanline_length", grub_vbe_bios_get_scanline_length},
      {"grub_vbe_bios_getset_dac_palette_width", grub_vbe_bios_getset_dac_palette_width},
      {"grub_vbe_bios_set_display_start", grub_vbe_bios_set_display_start},
      {"grub_vbe_bios_set_memory_window", grub_vbe_bios_set_memory_window},
      {"grub_vbe_bios_set_mode", grub_vbe_bios_set_mode},
      {"grub_vbe_bios_set_palette_data", grub_vbe_bios_set_palette_data},
      {"grub_vbe_bios_set_scanline_length", grub_vbe_bios_set_scanline_length},
      {"grub_vga_get_font", grub_vga_get_font},
      {"grub_vga_set_mode", grub_vga_set_mode},
      {"grub_vprintf", grub_vprintf},
      {"grub_vsnprintf", grub_vsnprintf},
      {"grub_xasprintf", grub_xasprintf},
      {"grub_xvasprintf", grub_xvasprintf},
      {"grub_zalloc", grub_zalloc},
      {"memcmp", memcmp},
      {"memcpy", memcpy},
      {"memmove", memmove},
      {"memset", memset},
      {0, 0}
    };

  COMPILE_TIME_ASSERT (sizeof (tab) > sizeof (tab[0]));
  for (p = tab; p->name; p++)
    grub_dl_register_symbol (p->name, p->addr, 0);
}
