#! /bin/bash 

url="http://192.169.7.32:9999"

declare -A cmd_map
cmd_map[1]="-h"
cmd_map[2]="--move-to"
cmd_map[3]="--drag"
cmd_map[4]="--set-tool"
cmd_map[5]="--delete-tool"
cmd_map[6]="--set-default-tool"
cmd_map[7]="--set-max-cart-vel"
cmd_map[8]="--set-max-joint-vel"
cmd_map[9]="--reset-max-cart-vel"
cmd_map[10]="--reset-max-joint-vel"
cmd_map[11]="--save-point"
cmd_map[12]="--delete-point"
cmd_map[13]="--get-cur-status"
cmd_map[14]="--get-tool"
cmd_map[15]="--get-max-cart-vel"
cmd_map[16]="--get-max-joint-vel"
cmd_map[17]="--get-points"
cmd_map[18]="--jnt-to-cart"
cmd_map[19]="--cart-to-jnt"
cmd_map[20]="--stop-all"

########################################################################################
function Help()
{
    echo "cob-jiasheng-cmd.sh  shell script for cob jiasheng-dev branch "
    echo -e

    echo "${cmd_map[1]}  output "
    echo "${cmd_map[2]}  output "
    echo "${cmd_map[3]}  output "
    echo "${cmd_map[4]}  output "
    echo "${cmd_map[5]}  output "

    echo -e
    echo "${cmd_map[6]}  output "
    echo "${cmd_map[7]}  output "
    echo "${cmd_map[8]}  output "
    echo "${cmd_map[9]}  output "
    echo "${cmd_map[10]}  output "

    echo -e
    echo "${cmd_map[11]}  output "
    echo "${cmd_map[12]}  output "
    echo "${cmd_map[13]}  output "
    
    echo -e
    echo "${cmd_map[14]}  output "
    echo "${cmd_map[15]}  output "
    echo "${cmd_map[16]}  output "
    echo "${cmd_map[17]}  output "
    echo "${cmd_map[18]}  output "
    echo "${cmd_map[19]}  output "
    echo "${cmd_map[20]}  output "
    echo ""
}

function MoveTo()
{
    uri="/api/control/moveTo"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function Drag()
{
    uri="/api/control/drag"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function SetTool()
{
    uri="/api/safety/setTool"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function DeleteTool()
{
    uri="/api/safety/deleteTool"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function SetDefaultTool()
{
    uri="/api/safety/setDefaultTool"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function SetMaxCartVel()
{
    uri="/api/safety/setMaxCartVel"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function SetMaxJointVel()
{
    uri="/api/safety/setMaxJointVel"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function ResetMaxCartVel()
{
    uri="/api/safety/resetMaxCartVel"

    curl -X GET ${url}${uri}
        
    echo -e
}

function ResetMaxJointVel()
{
    uri="/api/safety/resetMaxJointVel"

    curl -X GET ${url}${uri}
        
    echo -e
}

function SavePoint()
{
    uri="/api/teach/savePoint"

    curl -X GET ${url}${uri}
        
    echo -e
}

function DeletePoint()
{
    uri="/api/teach/deletePoint"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function GetCurStatus()
{
    uri="/api/common/getCurStatus"

    curl -X GET ${url}${uri}
        
    echo -e
}

function GetTool()
{
    uri="/api/safety/getTool"

    curl -X GET ${url}${uri}
        
    echo -e
}

function GetMaxCartVel()
{
    uri="/api/safety/getMaxCartVel"

    curl -X GET ${url}${uri}
        
    echo -e
}

function GetMaxJointVel()
{
    uri="/api/safety/getMaxJointVel"

    curl -X GET ${url}${uri}
        
    echo -e
}

function GetPoints()
{
    uri="/api/teach/getPoints"

    curl -X GET ${url}${uri}
        
    echo -e
}

function JntToCart()
{
    uri="/api/common/JntToCart"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function CartToJnt()
{
    uri="/api/common/CartToJnt"
    if [ -z "$1" ]; then 
        echo "Error json file "
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi
    echo -e
}

function StopAll()
{
    uri="/api/control/stop"

    curl -X GET ${url}${uri}

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
        Drag $2
    elif [[ $1 == "${cmd_map[4]}" ]]; then 
        SetTool $2
    elif [[ $1 == "${cmd_map[5]}" ]]; then 
        DeleteTool $2
    elif [[ $1 == "${cmd_map[6]}" ]]; then 
        SetDefaultTool $2
    elif [[ $1 == "${cmd_map[7]}" ]]; then 
        SetMaxJointVel $2
    elif [[ $1 == "${cmd_map[8]}" ]]; then 
        SetMaxCartVel $2
    elif [[ $1 == "${cmd_map[9]}" ]]; then 
        ResetMaxCartVel 
    elif [[ $1 == "${cmd_map[10]}" ]]; then 
        ResetMaxJointVel 
    elif [[ $1 == "${cmd_map[11]}" ]]; then 
        SavePoint 
    elif [[ $1 == "${cmd_map[12]}" ]]; then 
        DeletePoint $2
    elif [[ $1 == "${cmd_map[13]}" ]]; then 
        GetCurStatus
    elif [[ $1 == "${cmd_map[14]}" ]]; then 
        GetTool 
    elif [[ $1 == "${cmd_map[15]}" ]]; then 
        GetMaxCartVel 
    elif [[ $1 == "${cmd_map[16]}" ]]; then 
        GetMaxJointVel 
    elif [[ $1 == "${cmd_map[17]}" ]]; then 
        GetPoints 
    elif [[ $1 == "${cmd_map[18]}" ]]; then 
        JntToCart $2
    elif [[ $1 == "${cmd_map[19]}" ]]; then 
        CartToJnt $2
    elif [[ $1 == "${cmd_map[20]}" ]]; then 
        StopAll
    else 
        Help
    fi
}

if [[ $# > 0 ]]; then 
    main $*
else 
    echo "Too few arguments..."
    echo "Try './cob-jiasheng-cmd.sh -h' for more information"
fi