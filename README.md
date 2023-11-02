# EFI-based USB Target Disk Mode
![A bouncing trident.](https://github.com/targetdisk/targetdisk-linuxfb/raw/mane/epic_bounce.gif)

This repository contains the EFI runtime component of my UEFI-based USB target
disk mode solution.

You will need a GNU/Linux machine that supports building ELF objects for your
target system (which POSIX-UEFI's toolchain converts into PE executables for
us).

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

## Building
```
make
```

## Running with Qemu
If you have a GNU/Linux system with KVM enabled, you can run a demo like so:
```
./qemu_test.sh .
```

The above will put you at Tianocore's EFI shell.  Simply type the following (and
press enter) to run the application:
```
FS0:\targetdisk.efi
```

## Running on real hardware
You can also run the `.efi` on any UEFI-compliant machine that matches the
architecture that you just compiled for.  It's easiest if you do it from the
UEFI shell.  If your machine doesn't have a Tianocore shell, you can use
something like the Arch Linux install ISO to get one.

> If you're an absolute madperson you can also add the `.efi` file to your EFI
> boot vars!

## Further reading
- [https://wiki.osdev.org/POSIX-UEFI](https://wiki.osdev.org/POSIX-UEFI)
- [https://uefi.org/specifications](https://uefi.org/specifications)
