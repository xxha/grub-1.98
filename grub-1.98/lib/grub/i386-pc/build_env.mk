TARGET_CC=gcc
TARGET_CFLAGS=-Os -DGRUB_MACHINE_PCBIOS=1 -Wall -W -Wshadow -Wpointer-arith -Wmissing-prototypes                -Wundef -Wstrict-prototypes -g -falign-jumps=1 -falign-loops=1 -falign-functions=1 -mno-mmx -mno-sse -mno-sse2 -mno-3dnow -fno-dwarf2-cfi-asm -m32 -fno-stack-protector -mno-stack-arg-probe 
TARGET_ASFLAGS=-DGRUB_MACHINE_PCBIOS=1
TARGET_CPPFLAGS=-I./include -I. -I./include -Wall -W -I/home/zxq/grub-1.98/target/lib/grub/i386-pc -I/home/zxq/grub-1.98/target/include
STRIP=strip
OBJCONV=
TARGET_MODULE_FORMAT=elf32
TARGET_APPLE_CC=0
COMMON_ASFLAGS=-nostdinc -fno-builtin -m32
COMMON_CFLAGS=-fno-builtin -mrtd -mregparm=3 -m32
COMMON_LDFLAGS=-m32 -nostdlib
