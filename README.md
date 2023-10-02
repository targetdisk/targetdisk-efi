Here lie my first attempts at building UEFI-executable software.  You will need
a GNU/Linux machine that supports building ELF objects for your target system
(which POSIX-UEFI's toolchain converts into PE executables for us).

## Getting build dependencies
### POSIX-UEFI
Clone our upstream submodules:
```
git submodule update --init --recursive
```

Build POSIX-UEFI:
```
make -j$(nproc) -Cposix-uefi uefi
```

## Building demos
Demos can be compiled by the names of their directories.

For instance, to compile the `hello` demo, simply run:
```
make hello
```

## Running demos
If you have a GNU/Linux system with KVM enabled, you can run a demo like so:
```
./qemu_test.sh hello
```

The above will put you at Tianocore's EFI shell.  Simply type the following (and
press enter) to run the demo:
```
FS0:\hello.efi
```

## Further reading
- [https://wiki.osdev.org/POSIX-UEFI](https://wiki.osdev.org/POSIX-UEFI)
- [https://uefi.org/specifications](https://uefi.org/specifications)
