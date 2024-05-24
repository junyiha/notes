#! /bin/bash 

sleep 3
nohup redshift &

sleep 1
/home/user/Videos/start.sh

sleep 1
/etc/init.d/mount.sh
