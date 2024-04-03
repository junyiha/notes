#! /bin/bash 

function CleanDocker()
{
    container_id=$(docker ps -q)
    echo ${container_id}

    docker exec -it ${container_id} pkill mnc.exe
    sleep 2
    eval "docker exec -it ${container_id} rm -r /data/static/warning_pictures"
    eval "docker exec -it ${container_id} mkdir /data/static/warning_pictures"
}

function CheckSpace()
{
    path="/userdata"
    threshold=95

    used_space=$(df -P /userdata | awk 'NR==2 {print $5}')

    echo ${used_space}

    substring_to_remove="%"
    modified_string="${used_space//$substring_to_remove}"

    echo ${modified_string}

    if [ ${modified_string} -gt ${threshold} ];then 
        echo "need to clean"
        CleanDocker
    else
        echo "enough"
    fi
}


while true; do
    CheckSpace
    sleep 60  
done