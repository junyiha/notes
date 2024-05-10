#! /bin/bash  

file="vcr-client.sh"

# url="http://192.169.4.16:28001"

# release
# url="http://192.169.0.152:28001"

# debug
url="http://192.169.0.152:28000"

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
cmd_map[10]="--robot-beijing-open"
cmd_map[11]="--robot-beijing-moveLine"
cmd_map[12]="--robot-beijing-dragMode"
cmd_map[13]="--robot-beijing-getPoint"
cmd_map[14]="--camera-ty-init"
cmd_map[15]="--camera-ty-open"
cmd_map[16]="--camera-ty-close"
cmd_map[17]="--detector-init"
cmd_map[18]="--detector-open"
cmd_map[19]="--detector-close"
cmd_map[20]="--detector-detect"
cmd_map[21]="--test-hi"
cmd_map[22]="--test-post-file"
cmd_map[23]="--robot-beijing-JntToCart"
cmd_map[24]="--robot-beijing-CartToJnt"
cmd_map[25]="--device-list"
cmd_map[26]="--tool-sucker-isCaptured"
cmd_map[27]="--robot-cob-stop-all"
cmd_map[28]="--robot-cob-drag"

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
    # echo "${cmd_map[5]}  sucker device , init command"
    echo "${cmd_map[8]}  sucker device , open command"
    echo "${cmd_map[6]}  sucker device , start command"
    echo "${cmd_map[7]}  sucker device , stop command"
    echo "${cmd_map[26]}  sucker device , is captured"

    echo -e
    echo "${cmd_map[10]}  beijing robot device , open command"
    echo "${cmd_map[9]}  beijing robot device , move joint command"
    echo "${cmd_map[11]}  beijing robot device , move line command"
    echo "${cmd_map[12]}  beijing robot device , drag move control command"
    echo "${cmd_map[13]}  beijing robot device , get point info command"
    echo "${cmd_map[23]}  beijing robot device , joint position to cart position"
    echo "${cmd_map[24]}  beijing robot device , cart position to joint position"

    echo -e 
    echo "${cmd_map[14]}  TYCamera device, init camera"
    echo "${cmd_map[15]}  TYCamera device, open camera"
    echo "${cmd_map[16]}  TYCamera device, close camera"

    echo -e 
    echo "${cmd_map[17]}  Detector, init detector"
    # echo "${cmd_map[18]}  Detector, open detector"
    echo "${cmd_map[20]}  Detector, detect a frame detector"
    echo "${cmd_map[19]}  Detector, close detector"

    echo -e 
    echo "${cmd_map[21]}  httplib test hi"
    echo "${cmd_map[22]}  httplib upload file"

    echo -e 
    echo "${cmd_map[25]}  device list"

    echo -e 
    echo "${cmd_map[27]}  cob robot, stop all"
    echo "${cmd_map[28]}  cob robot, drag mode"

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

function ToolSuckerIsCaptured()
{
    uri="/api/tools/sucker/isCaptured"

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

function RobotBeijingOpen()
{
    uri="/api/robots/beijing/open"

    if [ -z "$1" ]; then 
        echo "empty json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

function RobotBeijingMoveLine()
{
    uri="/api/robots/beijing/moveLine"

    if [ -z "$1" ]; then 
        echo "empty json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

function RobotBeijingDragMode()
{
    uri="/api/robots/beijing/dragMode"

    if [ -z "$1" ]; then 
        echo "empty json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

function RobotBeijingGetPoint()
{
    uri="/api/robots/beijing/getPoint"

    curl -X GET ${url}${uri}

    echo -e
}

function RobotBeijingJntToCart()
{
    uri="/api/robots/beijing/jointToCart"

    if [ -z "$1" ]; then 
        echo "empty json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

function RobotBeijingCartToJnt()
{
    uri="/api/robots/beijing/cartToJoint"

    if [ -z "$1" ]; then 
        echo "empty json file"
    else 
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

#######################################################

function TYCameraInit()
{
    uri="/api/cameras/tycamera/init"

    curl -X GET ${url}${uri}

    echo -e
}

function TYCameraOpen()
{
    uri="/api/cameras/tycamera/open"

    curl -X GET ${url}${uri}

    echo -e
}

function TYCameraClose()
{
    uri="/api/cameras/tycamera/close"

    curl -X GET ${url}${uri}

    echo -e
}

#######################################################

function DetectorInit()
{
    uri="/api/detectors/detector/init"

    curl -X GET ${url}${uri}

    echo -e   
}

function DetectorOpen()
{
    uri="/api/detectors/detector/open"

    curl -X GET ${url}${uri}

    echo -e   
}

function DetectorDetect()
{
    uri="/api/detectors/detector/detect"

    curl -X GET ${url}${uri}

    echo -e   
}

function DetectorClose()
{
    uri="/api/detectors/detector/close"

    curl -X GET ${url}${uri}

    echo -e   
}

#######################################################

# httplib_url="http://192.169.4.16:29001"
httplib_url="http://127.0.0.1:1234"

function TestHttplibHi()
{
    uri="/hi"

    curl -X GET ${httplib_url}${uri}

    echo -e
}

function TestHttplibPostFile()
{
    uri="/post"

    # curl -X POST -F image_file=@/home/user/Pictures/Selection_057.jpg ${httplib_url}${uri}

    curl -X POST -F image_file=@/mnt/remote/190-mnt/zhangjunyi/Documents/VCR/pcd_files/cloud-computer-test-aaa.pcd ${httplib_url}${uri}
    

    echo -e
}

#######################################################
function DeviceList()
{
    uri="/api/common/list"

    curl -X GET ${url}${uri}

    echo -e
}

#######################################################

function CobStopAll()
{
    uri="/api/robots/cob/stopAll"

    curl -X GET ${url}${uri}

    echo -e
}

function CobDrag()
{
    uri="/api/robots/cob/dragMode"

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
    elif [[ $1 == "${cmd_map[26]}" ]]; then 
        ToolSuckerIsCaptured  
    elif [[ $1 == "${cmd_map[8]}" ]]; then 
        ToolSuckerOpen
    elif [[ $1 == "${cmd_map[9]}" ]]; then 
        RobotBeijingMoveJoint $2
    elif [[ $1 == "${cmd_map[10]}" ]]; then 
        RobotBeijingOpen $2
    elif [[ $1 == "${cmd_map[11]}" ]]; then 
        RobotBeijingMoveLine $2
    elif [[ $1 == "${cmd_map[12]}" ]]; then 
        RobotBeijingDragMode $2
    elif [[ $1 == "${cmd_map[13]}" ]]; then 
        RobotBeijingGetPoint
    elif [[ $1 == "${cmd_map[14]}" ]]; then 
        TYCameraInit
    elif [[ $1 == "${cmd_map[15]}" ]]; then 
        TYCameraOpen
    elif [[ $1 == "${cmd_map[16]}" ]]; then 
        TYCameraClose
    elif [[ $1 == "${cmd_map[17]}" ]]; then 
        DetectorInit
    elif [[ $1 == "${cmd_map[18]}" ]]; then 
        DetectorOpen
    elif [[ $1 == "${cmd_map[19]}" ]]; then 
        DetectorClose
    elif [[ $1 == "${cmd_map[20]}" ]]; then 
        DetectorDetect
    elif [[ $1 == "${cmd_map[21]}" ]]; then 
        TestHttplibHi
    elif [[ $1 == "${cmd_map[22]}" ]]; then 
        TestHttplibPostFile
    elif [[ $1 == "${cmd_map[23]}" ]]; then 
        RobotBeijingJntToCart $2
    elif [[ $1 == "${cmd_map[24]}" ]]; then 
        RobotBeijingCartToJnt $2
    elif [[ $1 == "${cmd_map[25]}" ]]; then 
        DeviceList
    elif [[ $1 == "${cmd_map[27]}" ]]; then 
        CobStopAll
    elif [[ $1 == "${cmd_map[28]}" ]]; then 
        CobDrag $2
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