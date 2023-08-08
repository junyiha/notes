#! /bin/bash 

file="vcr-client.sh"

# url="http://192.169.4.16:28001"
url="http://192.169.0.152:28001"

declare -A cmd_map
cmd_map[1]="-h"
cmd_map[2]="--hello"
cmd_map[3]="--init-sucker"

#######################################################

function Help()
{
    echo "${file}  shell script for VCR client"
    echo -e
    echo "${cmd_map[1]}  output help information"
    echo "${cmd_map[2]}  hello test"
    echo "${cmd_map[3]}  [param.txt] init electric sucker"

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

    curl --data-binary @$1 -H Content-Type: application/x-www-form-urlencoded ${url}${uri}
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