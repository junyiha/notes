#! /bin/bash 

file="vcr-client.sh"

# url="http://192.169.4.16:28001"
url="http://192.169.0.152:28001"

declare -A cmd_map
cmd_map[1]="-h"
cmd_map[2]="--hello"
cmd_map[3]="--init-sucker"
cmd_map[4]="--test-post"
cmd_map[5]="--tool-sucker-init"
cmd_map[6]="--tool-sucker-start"
cmd_map[7]="--tool-sucker-stop"
cmd_map[8]="--tool-sucker-open"
cmd_map[9]="--robot-beijing-moveJoint"

#######################################################

function Help()
{
    echo "${file}  shell script for VCR client"
    echo -e
    echo "${cmd_map[1]}  output help information"
    echo "${cmd_map[2]}  hello test"
    echo "${cmd_map[3]}  [param.txt] init electric sucker"
    echo "${cmd_map[4]}  test post request with body data"

    echo -e
    echo "${cmd_map[5]}  sucker device , init command"
    echo "${cmd_map[6]}  sucker device , start command"
    echo "${cmd_map[7]}  sucker device , stop command"
    echo "${cmd_map[8]}  sucker device , open command"

    echo -e
    echo "${cmd_map[9]}  beijing robot device , move joint command"

    echo -e
}

function Hello()
{
    uri="/api/hello/world"

    curl -X GET ${url}${uri}
    echo -e 
}

function SuckerInit()
{
    uri="/api"

    if [ -z "$1" ]; then 
        echo "empty json file"
    else
        curl --data-binary @$1 -H Content-Type: application/x-www-form-urlencoded ${url}${uri}
    fi 
    echo -e
}

function TestPost()
{
    uri="/api"

    curl -X POST -d {\"hello\":\"world\"} ${url}${uri}
    echo -e
}

function ToolSuckerInit()
{
    uri="/api/tools/sucker/init"

    curl -X GET ${url}${uri}
    echo -e
}

function ToolSuckerStart()
{
    uri="/api/tools/sucker/start"

    curl -X GET ${url}${uri}
    echo -e
}

function ToolSuckerStop()
{
    uri="/api/tools/sucker/stop"

    curl -X GET ${url}${uri}
    echo -e
}

function ToolSuckerOpen()
{
    uri="/api/tools/sucker/open"

    curl -X GET ${url}${uri}
    echo -e
}

#######################################################

function RobotBeijingMoveJoint()
{
    uri="/api/robots/beijing/moveJoint"

    if [ -z "$1" ]; then 
        echo "empty json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

#######################################################

function main()
{
    if [[ $1 == "${cmd_map[1]}" ]]; then 
        Help
    elif [[ $1 == "${cmd_map[2]}" ]]; then 
        Hello
    elif [[ $1 == "${cmd_map[3]}" ]]; then 
        SuckerInit $2
    elif [[ $1 == "${cmd_map[4]}" ]]; then 
        TestPost
    elif [[ $1 == "${cmd_map[5]}" ]]; then 
        ToolSuckerInit
    elif [[ $1 == "${cmd_map[6]}" ]]; then 
        ToolSuckerStart
    elif [[ $1 == "${cmd_map[7]}" ]]; then 
        ToolSuckerStop  
    elif [[ $1 == "${cmd_map[8]}" ]]; then 
        ToolSuckerOpen
    elif [[ $1 == "${cmd_map[9]}" ]]; then 
        RobotBeijingMoveJoint $2
    else 
        Help
    fi
}

if [[ $# > 0 ]]; then 
    main $* 
else 
    echo "Too few arguments..."
    echo "Try './${file} -h' for more information"
fi