ARCH ?= x86_64

CFLAGS ?= -pedantic -Wall -Wextra -Werror --ansi
export CFLAGS ARCH

UNAME = $(shell uname)
ifeq ($(UNAME),Linux)
	OPEN=xdg-open
endif

.PHONY: Makefile README

%: Makefile
	USE_GCC=1 $(MAKE) -C$@ -j$(shell nproc)

pub.css:
	wget https://github.com/manuelp/pandoc-stylesheet/raw/acac36b976966f76544176161ba826d519b6f40c/pub.css

README: pub.css # Requires Pandoc to be installed
	pandoc README.md -s -c pub.css -o README.html
	$(OPEN) README.html
