#!/usr/bin/env bash

. util/logging.bash

: " * qemu_test.sh
    * ============
  "

read -d'' USAGE <<EOUSAGE
Usage: $0 BASEDIR

$(basename $0) starts an EFI virtual machine with BASEDIR mounted as a FAT filesystem.
EOUSAGE

[ -z "$1" ] && dedcat "$USAGE"
[ -z "$OVMF" ] && OVMF=/usr/share/ovmf/x64/OVMF.fd

[ -f "$OVMF" ] \
  || dedcat "ERROR: Please specify OVMF env variable as a path to a TianoCore OVMF image."

case "$OSTYPE" in
  darwin*)
    ACCEL_ARGS=""
    ;;
  linux-gnu)
    ACCEL_ARGS="-enable-kvm"
    ;;
  *)
    ACCEL_ARGS=""
    ;;
esac

[ -z "$ACCEL_ARGS" ] \
    && errcho "WARN: Suffering through software emulation..."

qemu-system-x86_64 -net none -bios "$OVMF" $ACCEL_ARGS -m 64 -hda fat:rw:"$1"
