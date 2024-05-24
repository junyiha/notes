#! /bin/bash -x

mount -o intr 192.169.4.166:/volume1/open_space /mnt/remote/166-mnt

sleep 1

mount -o intr 192.169.4.190:/volume1/GHspace /mnt/remote/190-mnt

