# -*- makefile -*-
#
# Copyright (C) 1994,1995,1996,1997,1998,1999,2000,2001,2002,2004,2005,2006,2007,2008,2009,2010 Free Software Foundation, Inc.
#
# This Makefile.in is free software; the author
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

### The configure script will replace these variables.

SHELL = /bin/sh



transform = s,x,x,

srcdir = .
builddir = .
top_srcdir = .

prefix = /home/xxha/git-server/open-source/grub-1.98/install
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datarootdir = ${prefix}/share
datadir = ${datarootdir}
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${datarootdir}/info
mandir = ${datarootdir}/man
includedir = ${prefix}/include
pkgdatadir = $(datadir)/`echo grub | sed '$(transform)'`
pkglibdir =  $(libdir)/`echo grub/$(target_cpu)-$(platform) | sed '$(transform)'`

# Internationalization library.
LIBINTL = 

XGETTEXT = /usr/bin/xgettext
MSGMERGE = /usr/bin/msgmerge
MSGFMT = /usr/bin/msgfmt

LINGUAS = $(shell for i in $(srcdir)/po/*.po ; do \
			if test -e $$i ; then echo $$i ; fi ; \
		done | sed -e "s,.*/po/\(.*\)\.po$$,\1,")

PACKAGE = grub
PACKAGE_NAME = GRUB
PACKAGE_TARNAME = grub
PACKAGE_VERSION = 1.98
PACKAGE_STRING = GRUB 1.98
PACKAGE_BUGREPORT = bug-grub@gnu.org

host_os = linux-gnu
host_kernel = linux
host_cpu = i686

target_cpu = i386
platform = pc

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
MKDIR_P = /bin/mkdir -p

mkinstalldirs = $(srcdir)/mkinstalldirs

LIBS =  $(LIBINTL)

CC = gcc
CFLAGS =  -DGRUB_MACHINE_PCBIOS=1
ASFLAGS = 
LDFLAGS =  $(LIBS)
CPPFLAGS =  -I$(builddir) -I$(builddir)/include -I$(srcdir)/gnulib -I$(srcdir)/include -Wall -W \
	 -DGRUB_LIBDIR=\"$(pkglibdir)\" -DLOCALEDIR=\"$(localedir)\"
TARGET_CC = gcc
TARGET_CFLAGS =  -Os -DGRUB_MACHINE_PCBIOS=1 -Wall -W -Wshadow -Wpointer-arith -Wmissing-prototypes                -Wundef -Wstrict-prototypes -g -falign-jumps=1 -falign-loops=1 -falign-functions=1 -mno-mmx -mno-sse -mno-sse2 -mno-3dnow -fno-dwarf2-cfi-asm -m32 -fno-stack-protector -mno-stack-arg-probe
TARGET_ASFLAGS =  -DGRUB_MACHINE_PCBIOS=1
TARGET_MODULE_FORMAT = elf32
TARGET_APPLE_CC = 0
OBJCONV = 
TARGET_CPPFLAGS =  -nostdinc -isystem /usr/lib/gcc/i686-linux-gnu/4.6/include -I$(srcdir)/include -I$(builddir) -I$(builddir)/include \
	-Wall -W
TARGET_LDFLAGS =  -m32 -Wl,--build-id=none
TARGET_IMG_LDSCRIPT = 
TARGET_IMG_LDFLAGS = -Wl,-N  -Wl,-Ttext,
TARGET_IMG_CFLAGS = 
TARGET_OBJ2ELF = 
EXEEXT = 
OBJCOPY = objcopy
STRIP = strip
NM = nm
RUBY = 
MAKEINFO = 
ifeq (, $(MAKEINFO))
MAKEINFO = true
endif
HELP2MAN = 
ifeq (, $(HELP2MAN))
HELP2MAN = true
else
HELP2MAN := LANG=C $(HELP2MAN) --no-info --source=FSF
endif
AWK = mawk
LIBCURSES = 
LIBUSB = 
LIBSDL = 
LIBPCIACCESS = 
YACC = bison
FONT_SOURCE = 

# Options.
enable_grub_emu_usb = 
enable_grub_emu_sdl = 
enable_grub_emu_pci = 
enable_grub_fstest = yes
enable_grub_pe2elf = @enable_grub_pe2elf@
enable_grub_mkfont = no
freetype_cflags = 
freetype_libs = 
enable_efiemu = yes

### General variables.

RMKFILES = $(wildcard conf/*.rmk)

MKFILES = $(patsubst %.rmk,%.mk,$(RMKFILES))

PKGLIB = $(pkglib_IMAGES) $(pkglib_MODULES) $(pkglib_PROGRAMS) \
	$(pkglib_DATA) $(pkglib_BUILDDIR)
PKGDATA = $(pkgdata_DATA)
PROGRAMS = $(bin_UTILITIES) $(sbin_UTILITIES)
SCRIPTS = $(bin_SCRIPTS) $(sbin_SCRIPTS) $(grub-mkconfig_SCRIPTS) \
	$(lib_SCRIPTS)
INFOS = $(info_INFOS)

CLEANFILES =
MOSTLYCLEANFILES =
DISTCLEANFILES = config.status config.cache config.log config.h \
	Makefile stamp-h stamp-h1 include/grub/cpu include/grub/machine \
	gensymlist.sh genkernsyms.sh build_env.mk \
	docs/grub.info docs/version.texi docs/stamp-vti

MAINTAINER_CLEANFILES = $(srcdir)/configure $(addprefix $(srcdir)/,$(MKFILES)) \
	$(srcdir)/DISTLIST $(srcdir)/config.h.in $(srcdir)/stamp-h.in $(INFOS)

# The default target.
all: all-local

### Include an arch-specific Makefile.
$(addprefix $(srcdir)/,$(MKFILES)): %.mk: %.rmk genmk.rb
	if test "x$(RUBY)" = x; then \
	  touch $@; \
	else \
	  $(RUBY) $(srcdir)/genmk.rb < $< > $@; \
	fi

ifeq ($(platform), emu)
include $(srcdir)/conf/any-emu.mk
else
include $(srcdir)/conf/$(target_cpu)-$(platform).mk
# For tests.
include $(srcdir)/conf/tests.mk
# For external modules.
-include $(wildcard $(GRUB_CONTRIB)/*/conf/common.mk)
endif

### General targets.

CLEANFILES += $(pkglib_DATA) $(pkgdata_DATA) po/*.mo
pkglib_DATA += moddep.lst command.lst fs.lst partmap.lst parttool.lst handler.lst video.lst crypto.lst terminal.lst
moddep.lst: $(DEFSYMFILES) $(UNDSYMFILES) genmoddep.awk
	cat $(DEFSYMFILES) /dev/null \
	  | $(AWK) -f $(srcdir)/genmoddep.awk $(UNDSYMFILES) > $@ \
	  || (rm -f $@; exit 1)

command.lst: $(COMMANDFILES)
	cat $^ /dev/null | sort > $@

fs.lst: $(FSFILES)
	cat $^ /dev/null | sort > $@

partmap.lst: $(PARTMAPFILES)
	cat $^ /dev/null | sort > $@

handler.lst: $(HANDLERFILES)
	cat $^ /dev/null | sort > $@

terminal.lst: $(TERMINALFILES)
	cat $^ /dev/null | sort > $@

parttool.lst: $(PARTTOOLFILES)
	cat $^ /dev/null | sort | uniq > $@

video.lst: $(VIDEOFILES)
	cat $^ /dev/null | sort | uniq > $@

crypto.lst: lib/libgcrypt-grub/cipher/crypto.lst
	cp $^ $@

ifneq (true, $(MAKEINFO))
info_INFOS += docs/grub.info
endif

MOSTLYCLEANFILES += vti.tmp
MAINTAINER_CLEANFILES += docs/stamp-vti docs/version.texi
docs/version.texi: docs/stamp-vti
docs/stamp-vti: docs/grub.texi configure.ac
	$(MKDIR_P) docs
	(set `$(SHELL) $(srcdir)/docs/mdate-sh $<`; \
	echo "@set UPDATED $$1 $$2 $$3"; \
	echo "@set UPDATED-MONTH $$2 $$3"; \
	echo "@set EDITION $(PACKAGE_VERSION)"; \
	echo "@set VERSION $(PACKAGE_VERSION)") > vti.tmp
	@cmp -s vti.tmp $(builddir)/docs/version.texi \
	  || (echo "Updating $(builddir)/docs/version.texi"; \
	      cp vti.tmp $(builddir)/docs/version.texi)
	-@rm -f vti.tmp
	@cp $(builddir)/docs/version.texi $@

# Use --force until such time as the documentation is cleaned up.
docs/grub.info: docs/grub.texi docs/version.texi docs/fdl.texi
	$(MKDIR_P) docs
	-$(MAKEINFO) -P $(builddir)/docs --no-split --force $< -o $@

ifeq (, $(FONT_SOURCE))
else

ifeq ($(enable_grub_mkfont),yes)

pkgdata_DATA += unicode.pf2 ascii.pf2 ascii.h
CLEANFILES += ascii.bitmaps

# Arrows and lines are needed to draw the menu, so we always include them
UNICODE_ARROWS=0x2190-0x2193
UNICODE_LINES=0x2501-0x251B

unicode.pf2: $(FONT_SOURCE) grub-mkfont
	$(builddir)/grub-mkfont -o $@ $(FONT_SOURCE)

ascii.pf2: $(FONT_SOURCE) grub-mkfont
	$(builddir)/grub-mkfont -o $@ $(FONT_SOURCE) -r 0x0-0x7f,$(UNICODE_ARROWS),$(UNICODE_LINES)

ascii.bitmaps: $(FONT_SOURCE) grub-mkfont
	$(builddir)/grub-mkfont --ascii-bitmaps -o $@ $(FONT_SOURCE)

ascii.h: ascii.bitmaps grub-bin2h
	$(builddir)/grub-bin2h ascii_bitmaps < $< > $@

TARGET_CFLAGS += -DUSE_ASCII_FAILBACK=1
endif
endif

# Used for building modules externally
pkglib_BUILDDIR += build_env.mk
build_env.mk: Makefile
	(\
	echo "TARGET_CC=$(TARGET_CC)" ; \
	echo "TARGET_CFLAGS=$(TARGET_CFLAGS)" ; \
	echo "TARGET_ASFLAGS=$(TARGET_ASFLAGS)" ; \
	echo "TARGET_CPPFLAGS=$(TARGET_CPPFLAGS) -I$(pkglibdir) -I$(includedir)" ; \
	echo "STRIP=$(STRIP)" ; \
	echo "OBJCONV=$(OBJCONV)" ; \
	echo "TARGET_MODULE_FORMAT=$(TARGET_MODULE_FORMAT)" ; \
	echo "TARGET_APPLE_CC=$(TARGET_APPLE_CC)" ; \
	echo "COMMON_ASFLAGS=$(COMMON_ASFLAGS)" ; \
	echo "COMMON_CFLAGS=$(COMMON_CFLAGS)" ; \
	echo "COMMON_LDFLAGS=$(COMMON_LDFLAGS)"\
	) > $@
pkglib_BUILDDIR += config.h grub_script.tab.h

all-local: $(PROGRAMS) $(PKGLIB) $(PKGDATA) $(SCRIPTS) $(INFOS) $(MKFILES) $(foreach lang, $(LINGUAS), po/$(lang).mo)

install: install-local

install-local: all
	$(SHELL) $(mkinstalldirs) $(DESTDIR)$(pkglibdir)
	rm -f $(DESTDIR)$(pkglibdir)/*
	@list='$(PKGLIB)'; \
	for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,'`"; \
	  $(INSTALL_DATA) $$dir$$file $(DESTDIR)$(pkglibdir)/$$dest; \
	done
	$(SHELL) $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)
	@list='$(PKGDATA)'; \
	for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,'`"; \
	  $(INSTALL_DATA) $$dir$$file $(DESTDIR)$(pkgdatadir)/$$dest; \
	done
	$(SHELL) $(mkinstalldirs) $(DESTDIR)$(bindir) $(DESTDIR)$(mandir)/man1
	@list='$(bin_UTILITIES)'; for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  $(INSTALL_PROGRAM) $$dir$$file $(DESTDIR)$(bindir)/$$dest; \
	  $(HELP2MAN) --section=1 -o $(DESTDIR)$(mandir)/man1/$$dest.1 $(builddir)/$$file; \
	done
	$(SHELL) $(mkinstalldirs) $(DESTDIR)$(sbindir) $(DESTDIR)$(mandir)/man8
	@list='$(sbin_UTILITIES)'; for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  $(INSTALL_PROGRAM) $$dir$$file $(DESTDIR)$(sbindir)/$$dest; \
	  $(HELP2MAN) --section=8 -o $(DESTDIR)$(mandir)/man8/$$dest.8 $(builddir)/$$file; \
	done
	@list='$(bin_SCRIPTS)'; for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  $(INSTALL_SCRIPT) $$dir$$file $(DESTDIR)$(bindir)/$$dest; \
	  $(HELP2MAN) --section=1 -o $(DESTDIR)$(mandir)/man1/$$dest.1 $(builddir)/$$file; \
	done
	@list='$(sbin_SCRIPTS)'; for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  $(INSTALL_SCRIPT) $$dir$$file $(DESTDIR)$(sbindir)/$$dest; \
	  $(HELP2MAN) --section=8 -o $(DESTDIR)$(mandir)/man8/$$dest.8 $(builddir)/$$file; \
	done
	$(SHELL) $(mkinstalldirs) $(DESTDIR)$(sysconfdir)/grub.d
	@list='$(grub-mkconfig_SCRIPTS)'; for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  $(INSTALL_SCRIPT) $$dir$$file $(DESTDIR)$(sysconfdir)/grub.d/$$dest; \
	done
	@list='$(grub-mkconfig_DATA)'; for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  $(INSTALL_DATA) $$dir$$file $(DESTDIR)$(sysconfdir)/grub.d/$$dest; \
	done
	$(SHELL) $(mkinstalldirs) $(DESTDIR)$(libdir)/grub
	@list='$(lib_SCRIPTS)'; \
	for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,'`"; \
	  $(INSTALL_DATA) $$dir$$file $(DESTDIR)$(libdir)/grub/$$dest; \
	done
	@langs='$(LINGUAS)'; \
	for lang in $$langs; do \
	  $(SHELL) $(mkinstalldirs) $(DESTDIR)/$(datadir)/locale/$$lang/LC_MESSAGES; \
	  file="po/$$lang.mo"; \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  $(INSTALL_DATA) $$dir$$file $(DESTDIR)/$(datadir)/locale/$$lang/LC_MESSAGES/$(PACKAGE).mo; \
	done
	$(SHELL) $(mkinstalldirs) $(DESTDIR)$(infodir)
	@list='$(info_INFOS)'; \
	for file in $$list; do \
	  if test -f "$$file"; then dir=; else dir="$(srcdir)/"; fi; \
	  dest="`echo $$file | sed 's,.*/,,'`"; \
	  $(INSTALL_DATA) $$dir$$file $(DESTDIR)$(infodir); \
	  if (install-info --version && \
	       install-info --version 2>&1 | sed 1q | grep -i -v debian) >/dev/null 2>&1; then \
	    install-info --info-dir="$(DESTDIR)$(infodir)" "$(DESTDIR)$(infodir)/$$dest" || :; \
	  fi; \
	done

install-strip:
	$(MAKE) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" install

uninstall:
	@list='$(PKGLIB)'; \
	for file in $$list; do \
	  dest="`echo $$file | sed 's,.*/,,'`"; \
	  rm -f $(DESTDIR)$(pkglibdir)/$$dest; \
	done
	@list='$(PKGDATA)'; \
	for file in $$list; do \
	  dest="`echo $$file | sed 's,.*/,,'`"; \
	  rm -f $(DESTDIR)$(pkgdatadir)/$$dest; \
	done
	@list='$(bin_UTILITIES) $(bin_SCRIPTS)'; for file in $$list; do \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  rm -f $(DESTDIR)$(bindir)/$$dest; \
	  rm -f $(DESTDIR)$(mandir)/man1/$$dest.1; \
	done
	@list='$(sbin_UTILITIES) $(sbin_SCRIPTS)'; for file in $$list; do \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  rm -f $(DESTDIR)$(sbindir)/$$dest; \
	  rm -f $(DESTDIR)$(mandir)/man8/$$dest.8; \
	done
	@list='$(grub-mkconfig_SCRIPTS) $(grub-mkconfig_DATA)'; for file in $$list; do \
	  dest="`echo $$file | sed 's,.*/,,' | sed '$(transform)'`"; \
	  rm -f $(DESTDIR)$(sysconfdir)/grub.d/$$dest; \
	done
	@list='$(lib_SCRIPTS)'; \
	for file in $$list; do \
	  dest="`echo $$file | sed 's,.*/,,'`"; \
	  echo rm -f $(DESTDIR)$(libdir)/$$dest; \
	  rm -f $(DESTDIR)$(libdir)/grub/$$dest; \
	done
	@list='$(info_INFOS)'; \
	for file in $$list; do \
	  dest="`echo $$file | sed 's,.*/,,'`"; \
	  if (install-info --version && \
	       install-info --version 2>&1 | sed 1q | grep -i -v debian) >/dev/null 2>&1; then \
	    if install-info --info-dir="$(DESTDIR)$(infodir)" --remove "$(DESTDIR)$(infodir)/$$dest"; then \
	      :; \
	    else \
	      test ! -f "$(DESTDIR)$(infodir)/$$dest" || exit 1; \
	    fi; \
	  fi; \
	  rm -f $(DESTDIR)$(infodir)/$$dest; \
	done

clean: $(CLEAN_IMAGE_TARGETS) $(CLEAN_MODULE_TARGETS) $(CLEAN_UTILITY_TARGETS)
	-test -z "$(CLEANFILES)" || rm -f $(CLEANFILES)

mostlyclean: clean $(MOSTLYCLEAN_IMAGE_TARGETS) $(MOSTLYCLEAN_MODULE_TARGETS) $(MOSTLYCLEAN_UTILITY_TARGETS)
	-test -z "$(MOSTLYCLEANFILES)" || rm -f $(MOSTLYCLEANFILES)

distclean: mostlyclean
	-test -z "$(DISTCLEANFILES)" || rm -f $(DISTCLEANFILES)
	-rm -rf $(srcdir)/autom4te.cache

maintainer-clean: distclean
	-test -z "$(MAINTAINER_CLEANFILES)" || rm -f $(MAINTAINER_CLEANFILES)

info:

dvi:

distdir=$(PACKAGE_TARNAME)-$(PACKAGE_VERSION)

DISTLIST: gendistlist.sh
	$(SHELL) $(srcdir)/gendistlist.sh > $(srcdir)/DISTLIST

distdir: DISTLIST
	-chmod -R a+w $(distdir) >/dev/null 2>&1; rm -rf $(distdir)
	$(SHELL) $(mkinstalldirs) $(distdir)
	for i in `cat $(srcdir)/DISTLIST`; do \
	  dir=`echo "$$i" | sed 's:/[^/]*$$::'`; \
	  if test -d $(srcdir)/$$dir; then \
	    $(SHELL) $(mkinstalldirs) $(distdir)/$$dir; \
	  fi; \
	  cp -p $(srcdir)/$$i $(distdir)/$$i || exit 1; \
	done
	chmod -R a+r $(distdir)

GZIP_ENV = --best

dist: distdir
	tar chof - $(distdir) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).tar.gz
	-chmod -R a+w $(distdir) >/dev/null 2>&1; rm -rf $(distdir)

distcheck: dist
	-chmod -R a+w $(distdir) >/dev/null 2>&1; rm -rf $(distdir)
	GZIP=$(GZIP_ENV) gzip -cd $(distdir).tar.gz | tar xf -
	chmod -R a-w $(distdir)
	chmod a+w $(distdir)
	mkdir $(distdir)/=build
	mkdir $(distdir)/=inst
	chmod a-w $(distdir)
	dc_instdir=`CDPATH=: && cd $(distdir)/=inst && pwd` \
	  && cd $(distdir)/=build \
	  && $(SHELL) ../configure --srcdir=.. --prefix=$$dc_instdir \
	  && $(MAKE) all dvi check install && $(MAKE) uninstall \
	  && (test `find $$dc_instdir -type f -print | wc -l` -le 1 \
	     || (echo "Error: files left after uninstall" 1>&2; \
	         exit 1)) \
	  && $(MAKE) dist && $(MAKE) distclean \
	  && rm -f $(distdir).tar.gz \
	  && (test `find . -type f -print | wc -l` -eq 0 \
	     || (echo "Error: files left after distclean" 1>&2; \
	         exit 1))
	-chmod -R a+w $(distdir) > /dev/null 2>&1; rm -rf $(distdir)
	@echo "$(distdir).tar.gz is ready for distribution" | \
	  sed 'h;s/./=/g;p;x;p;x'

check: all $(UNIT_TESTS) $(FUNCTIONAL_TESTS) $(SCRIPTED_TESTS)
	@list="$(UNIT_TESTS)"; \
	set -e; \
	for file in $$list; do \
	  $(builddir)/$$file; \
	done
	@list="$(FUNCTIONAL_TESTS)"; \
	set -e; \
	for file in $$list; do \
	  mod=`basename $$file .mod`; \
	  echo "insmod functional_test; insmod $$mod; functional_test" \
	    | $(builddir)/grub-shell; \
	done
	@list="$(SCRIPTED_TESTS)"; \
	set -e; \
	for file in $$list; do \
	  $(builddir)/$$file; \
	done

.SUFFIX:
.SUFFIX: .c .o .S .d

# Regenerate configure and Makefile automatically.
$(srcdir)/aclocal.m4: configure.ac acinclude.m4
	cd $(srcdir) && aclocal

$(srcdir)/configure: configure.ac aclocal.m4
	cd $(srcdir) && autoconf

$(srcdir)/config.h.in: stamp-h.in
$(srcdir)/stamp-h.in: configure.ac aclocal.m4
	cd $(srcdir) && autoheader
	echo timestamp > $(srcdir)/stamp-h.in

config.h: stamp-h
stamp-h: config.h.in config.status
	$(SHELL) ./config.status

Makefile: Makefile.in config.status
	$(SHELL) ./config.status

config.status: configure
	$(SHELL) ./config.status --recheck

gensymlist.sh: gensymlist.sh.in config.status
	$(SHELL) ./config.status

genkernsyms.sh: genkernsyms.sh.in config.status
	$(SHELL) ./config.status

$(srcdir)/po/$(PACKAGE).pot: po/POTFILES po/POTFILES-shell
	cd $(srcdir) && $(XGETTEXT) -ctranslate --from-code=utf-8 -o $@ -f $< --keyword=_ --keyword=N_
	cd $(srcdir) && $(XGETTEXT) -ctranslate --from-code=utf-8 -o $@ -f po/POTFILES-shell -j --language=Shell

$(foreach lang, $(LINGUAS), $(srcdir)/po/$(lang).po): po/$(PACKAGE).pot
	$(MSGMERGE) -U $@ $^

po/%.mo: po/%.po
	$(MKDIR_P) $$(dirname $@)
	$(MSGFMT) -c --statistics -o $@ $^

.PHONY: all install install-strip uninstall clean mostlyclean distclean
.PHONY: maintainer-clean info dvi dist check

# Prevent an overflow.
.NOEXPORT:

.DELETE_ON_ERROR:
