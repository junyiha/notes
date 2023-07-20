#! /bin/bash 

file_name="mnc-cmd.sh"
url="http://127.0.0.1:8000/api/"

declare -A cmd_map
cmd_map[1]="-h"
cmd_map[2]="--device-info"
cmd_map[3]="--device-system-config"
cmd_map[4]="--device-update"
cmd_map[5]="--device-update-system-config"

########################################################################################

function Help()
{
    echo "${file_name}  shell script for rk server"
    echo -e 
    echo "${cmd_map[1]}  output help information"
    echo "${cmd_map[2]}  get device information"
    echo "${cmd_map[3]}  get device system config information"
    echo "${cmd_map[4]}  update device name"
    echo "${cmd_map[5]}  [json file] update device system config "
}

function DeviceInfo()
{
    uri="device/info"

    curl -X GET ${url}${uri}
}

function DeviceSystemConfig()
{
    uri="device/system_config"

    curl -X GET ${url}${uri}
}

function DeviceUpdate()
{
    uri="device/update"

    curl -X POST -d {\"name\":\"$1\"} ${url}${uri}
}

function DeviceUpdateSystemConfig()
{
    uri="device/system_config"

    curl -X POST --data-binary @$1 ${url}${uri}
}

function main()
{
    if [[ $1 == "${cmd_map[1]}" ]]; then 
        Help
    elif [[ $1 == "${cmd_map[2]}" ]]; then 
        DeviceInfo
    elif [[ $1 == "${cmd_map[3]}" ]]; then 
        DeviceSystemConfig
    elif [[ $1 == "${cmd_map[4]}" ]]; then 
        DeviceUpdate $2
    elif [[ $1 == "${cmd_map[5]}" ]]; then 
        DeviceUpdateSystemConfig $2
    else 
        Help
    fi 
}

if [[ $# >0 ]]; then 
    main $*
else 
    echo "too few argument..."
    echo "try './tool.sh -h' for more information"
fi