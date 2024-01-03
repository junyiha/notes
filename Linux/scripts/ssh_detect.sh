#! /bin/bash 

# addr="ssh -o 'proxycommand socat - PROXY:47.100.31.121:gh-rk-1004:22,proxyport=5002' root@47.100.31.121"
addr="ssh 192.169.0.152"

ssh $addr "ls" > /dev/null 2>&1

if [ $? -eq 0 ]; then 
    echo $addr >> success.txt
else 
    echo $addr >> error.txt
fi

# curl -X POST --data "{\"id\":\"Qk99V\"}" http://127.0.0.1:8000/api/setting/task/stop

# curl -X POST --data "{\"id\":\"Qk99V\"}" http://127.0.0.1:8000/api/setting/task/start

# curl -X GET http://127.0.0.1:8000/api/setting/task/list