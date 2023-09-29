UNAME = $(shell uname)
ARCH ?= x86_64
TARGET ?= efi-app-$(ARCH)
LDS ?= gnu-efi/gnuefi/elf_x86_64_efi.lds
CRT0 ?= gnu-efi/$(ARCH)/gnuefi/crt0-efi-x86_64.o
#CRT0 ?= /usr/lib/crt0-efi-x86_64.o
#LDS ?= /usr/lib/elf_x86_64_efi.lds

CFLAGS ?= -Wall
ifeq ($(UNAME),Linux)
	OPEN=xdg-open
endif

pub-css:
	-[ ! -e pub.css ] && wget https://github.com/manuelp/pandoc-stylesheet/raw/acac36b976966f76544176161ba826d519b6f40c/pub.css

README: pub-css # Requires Pandoc to be installed
	pandoc README.md -s -c pub.css -o README.html
	$(OPEN) README.html

gnu-efi:
	$(MAKE) -Cgnu-efi -j$(shell nproc)

hello.o: hello.c
	$(CC) -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -c -o $@ $<

hello.so: hello.o
	$(LD) -shared -Bsymbolic -Lgnu-efi/$(ARCH)/lib -Lgnu-efi/$(ARCH)/gnuefi -T$(LDS) $(CRT0) $< -o $@ -lgnuefi -lefi

hello.efi: hello.so
	objcopy -j .text -j .sdata -j .data -j .dynamic \
		-j .dynsym -j .rel -j .rela -j .rel.* \
		-j .rela.* -j .reloc --target $(TARGET) \
		--subsystem=10 $< $@

hello: hello.efi

.PHONY: hello gnu-efi
