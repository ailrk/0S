#!/bin/bash

set -e
. ./iso.sh

qemu-system-$(./target_triplet-to-arch.sh $HOST) -cdrom oyster.iso
