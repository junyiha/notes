#!/bin/bash

PROCESS_NAME="frpc"

check_process() {
    if pgrep -x "$PROCESS_NAME" >/dev/null; then
        echo "Process $PROCESS_NAME is running."
        return 0
    else
        echo "Process $PROCESS_NAME is not running. Restarting..."
        /userdata/frp_0.52.3_linux_arm/frpc -c /userdata/frp_0.52.3_linux_arm/frpc.toml
        return 1
    fi
}

while true; do
    check_process
    sleep 60  
done