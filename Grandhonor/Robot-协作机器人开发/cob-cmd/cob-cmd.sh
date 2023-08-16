#! /bin/bash 

url="http://192.169.7.32:9999"

file="joint_space.json"

declare -A cmd_map
cmd_map[1]="-h"
cmd_map[2]="--move-to"
cmd_map[3]="--test-move-line"
cmd_map[4]="--ws-sync"
cmd_map[5]="--drag-control"
cmd_map[6]="--save-status"
cmd_map[7]="--login"
cmd_map[8]="--get-point"
cmd_map[9]="--beijing-moveTo"

########################################################################################

function Help()
{
    echo "cob-cmd.sh  shell script for cob debug"
    echo -e 
    echo "${cmd_map[1]}  output help information"
    echo "${cmd_map[2]}  [json file]  move to joint space position | cart space position (m, rad)"
    echo "${cmd_map[3]}  move line demo"
    echo "${cmd_map[4]}  websocket connection to get robot status information"
    echo "${cmd_map[5]}  [json file] control drag mode"
    echo "${cmd_map[6]}  save robot status"
    echo "${cmd_map[7]}  login server"
    echo "${cmd_map[8]}  get point info"

    echo -e 
    echo "${cmd_map[9]}  beijing robot , move to command"
    
}

function MoveTo()
{
    uri="/api/control/manual/moveTo"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function TestMoveLine()
{
    uri="/api/control/manual/tcpPosition/testMovL"
    curl -X POST -d "{"hello":"world"}" ${url}${uri}
    echo -e
}

function WebSocketSync()
{
    url="ws://192.169.7.32:9999/ws_sync"
    wscat -c ${url}
    echo -e
}

function DragControl()
{
    uri="/api/teach/drag"
    
    if [ -z "$1" ]; then 
        echo "Error json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function SaveStatus()
{
    uri="/api/test/save_status"

    curl -X GET ${url}${uri}
    echo -e
}

function Login()
{
    uri="/api/login"

    if [[ -z "$1" ]]; then 
        echo "error json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

function GetPoint()
{
    uri="/api/test/getPoint"

    curl -X GET ${url}${uri}
    echo -e
}

########################################################################################

function BeijingMoveTo()
{
    uri="/api/control/moveTo"

    if [[ -z "$1" ]]; then 
        echo "error json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

########################################################################################

function main()
{
    if [[ $1 == "${cmd_map[1]}" ]]; then 
        Help
    elif [[ $1 == "${cmd_map[2]}" ]]; then 
        MoveTo $2
    elif [[ $1 == "${cmd_map[3]}" ]]; then 
        TestMoveLine
    elif [[ $1 == "${cmd_map[4]}" ]]; then 
        WebSocketSync
    elif [[ $1 == "${cmd_map[5]}" ]]; then 
        DragControl $2
    elif [[ $1 == "${cmd_map[6]}" ]]; then 
        SaveStatus
    elif [[ $1 == "${cmd_map[7]}" ]]; then 
        Login $2
    elif [[ $1 == "${cmd_map[8]}" ]]; then 
        GetPoint
    elif [[ $1 == "${cmd_map[9]}" ]]; then 
        BeijingMoveTo $2
    else
        Help
    fi
}

if [[ $# > 0 ]]; then 
    main $*
else 
    echo "Too few arguments..."
    echo "Try './cob-cmd.sh -h' for more information"
fi