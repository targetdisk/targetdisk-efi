ARCH ?= x86_64
CFLAGS += -pedantic -Wall -Wextra -Werror --ansi -std=gnu11
CFLAGS += -include $(CURDIR)/uefi/uefi.h

TARGET = targetdisk.efi
SRCS = $(wildcard gfx/*.c) codec/codec.c main.c

include uefi/Makefile

UNAME = $(shell uname)
ifeq ($(UNAME),Linux)
	OPEN=xdg-open
endif

.PHONY: clean

pub.css:
	wget https://github.com/manuelp/pandoc-stylesheet/raw/acac36b976966f76544176161ba826d519b6f40c/pub.css

README.html: pub.css # Requires Pandoc to be installed
	pandoc README.md -s -c pub.css -o $@
	$(OPEN) $@

clean:
	@find -name '*.o' -print0 | xargs -0 rm -vf
	@rm -vf $(TARGET)
