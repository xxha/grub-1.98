#! /bin/sh
#
# Copyright (C) 2002,2006,2007,2008  Free Software Foundation, Inc.
#
# This gensymlist.sh.in is free software; the author
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

### The configure script will replace these variables.

: ${srcdir=.}
: ${CC=gcc}


cat <<EOF
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

EOF

for i in $*; do
  echo "#include <$i>"
done

cat <<EOF

#define COMPILE_TIME_ASSERT(cond) switch (0) { case 1: case !(cond): ; }

void
grub_register_exported_symbols (void)
{
EOF

cat <<EOF
  struct symtab { const char *name; void *addr; };
  struct symtab *p;
  static struct symtab tab[] =
    {
EOF

$CC  -Os -DGRUB_MACHINE_PCBIOS=1 -Wall -W -Wshadow -Wpointer-arith -Wmissing-prototypes                -Wundef -Wstrict-prototypes -g -falign-jumps=1 -falign-loops=1 -falign-functions=1 -mno-mmx -mno-sse -mno-sse2 -mno-3dnow -fno-dwarf2-cfi-asm -m32 -fno-stack-protector -mno-stack-arg-probe -DGRUB_SYMBOL_GENERATOR=1 -E -I. -Iinclude -I"$srcdir/include" $* \
  | grep -v '^#' \
  | sed -n \
        -e '/EXPORT_FUNC *([a-zA-Z0-9_]*)/{s/.*EXPORT_FUNC *(\([a-zA-Z0-9_]*\)).*/      {"\1", \1},/;p;}' \
        -e '/EXPORT_VAR *([a-zA-Z0-9_]*)/{s/.*EXPORT_VAR *(\([a-zA-Z0-9_]*\)).*/      {"\1", \&\1},/;p;}' \
  | sort -u

cat <<EOF
      {0, 0}
    };

  COMPILE_TIME_ASSERT (sizeof (tab) > sizeof (tab[0]));
  for (p = tab; p->name; p++)
    grub_dl_register_symbol (p->name, p->addr, 0);
}
EOF
