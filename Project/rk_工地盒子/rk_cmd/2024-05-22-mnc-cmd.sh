#! /bin/bash 

file_name="mnc-cmd.sh"
# url="http://127.0.0.1:8001/api/"
# url="http://192.169.5.56:8000/api/"
url="http://192.169.5.63:8000/api/"
# url="http://192.169.5.54:8000/api/"
# url="http://192.169.0.152:8000/api/"

declare -A cmd_map
cmd_map[1]="-h"
cmd_map[2]="--device-info"
cmd_map[3]="--device-system-config"
cmd_map[4]="--device-update"
cmd_map[5]="--device-update-system-config"
cmd_map[6]="--device-network"
cmd_map[7]="--device-systime"
cmd_map[8]="--docs-api-list"
cmd_map[9]="--docs-camera-list"
cmd_map[10]="--docs-upload-alarm"
cmd_map[11]="--docs-warning-record-list"
cmd_map[12]="--docs-camera-add"
cmd_map[13]="--docs-camera-update"
cmd_map[14]="--docs-camera-delete"
cmd_map[15]="--docs-warning-record-view"
cmd_map[16]="--docs-warning-record-delete"
cmd_map[17]="--docs-warning-record-remark"
cmd_map[18]="--docs-warning-record-count"
cmd_map[19]="--warning-clear"
cmd_map[20]="--camera-test"
cmd_map[21]="--camera-list"

########################################################################################

function Help()
{
    echo "${file_name}  shell script for rk server"

    echo -e 
    echo "${cmd_map[1]}  output help information"
    
    echo -e
    echo "${cmd_map[2]}  get device information"
    echo "${cmd_map[3]}  get device system config information"
    echo "${cmd_map[4]}  update device name"
    echo "${cmd_map[5]}  [json file] update device system config "
    echo "${cmd_map[6]}  get device network information"
    echo "${cmd_map[7]}  get device system time"

    echo -e
    echo "${cmd_map[8]}  get document list"
    echo "${cmd_map[9]}  get document of camera list text file"
    echo "${cmd_map[12]}  get document of camera add text file"
    echo "${cmd_map[13]}  get document of camera update text file"
    echo "${cmd_map[14]}  get document of camera delete text file"
    
    echo -e 
    echo "${cmd_map[10]}  get document of upload alarm text file"
    echo "${cmd_map[11]}  get document of warning record text file"
    echo "${cmd_map[15]}  get document of warning record view text file"
    echo "${cmd_map[16]}  get document of warning record delete file"
    echo "${cmd_map[17]}  get document of warning record remark file"
    echo "${cmd_map[18]}  get document of warning record count file"
    
    echo -e 
    echo "${cmd_map[19]}  clear warning record data"

    echo -e 
    echo "${cmd_map[20]}  test input video name"
    echo "${cmd_map[21]}  camera list"
    
    echo -e 
}

########################################################################################

function DeviceInfo()
{
    uri="device/info"

    curl -X GET ${url}${uri}
    echo -e
}

function DeviceSystemConfig()
{
    uri="device/system_config"

    curl -X GET ${url}${uri}
    echo -e
}

function DeviceUpdate()
{
    uri="device/update"

    curl -X POST -d {\"name\":\"$1\"} ${url}${uri}
    echo -e
}

function DeviceUpdateSystemConfig()
{
    uri="device/system_config"

    curl -X PUT --data-binary @$1 ${url}${uri}
    echo -e
}

function DeviceNetwork()
{
    uri="device/network"

    curl -X GET ${url}${uri}
    echo -e
}

function DeviceSystime()
{
    uri="device/systime"

    curl -X GET ${url}${uri}
    echo -e
}

########################################################################################

function DocsList()
{   
    uri="docs/api_list"

    curl -X GET ${url}${uri}
    echo -e
}

function DocsCameraList()
{
    uri="docs/file/camera/list"

    curl -X GET ${url}${uri}
    echo -e
}

function DocsCameraAdd()
{
    uri="docs/file/camera/add"

    curl -X GET ${url}${uri}
    echo -e
}

function DocsCameraUpdate()
{
    uri="docs/file/camera/update"

    curl -X GET ${url}${uri}
    echo -e
}

function DocsCameraDelete()
{
    uri="docs/file/camera/delete"

    curl -X GET ${url}${uri}
    echo -e
}

function DocsUploadAlarm()
{
    uri="docs/file/warning_record/upload_alarm"

    curl -X GET ${url}${uri}
    echo -e
}

function DocsWarningRecordList()
{
    uri="docs/file/warning_record/list"
    
    curl -X GET ${url}${uri}
    echo -e
}

function DocsWarningRecordView()
{
    uri="docs/file/warning_record/view"
    
    curl -X GET ${url}${uri}
    echo -e
}

function DocsWarningRecordDelete()
{
    uri="docs/file/warning_record/delete"
    
    curl -X GET ${url}${uri}
    echo -e
}

function DocsWarningRecordRemark()
{
    uri="docs/file/warning_record/remark"
    
    curl -X GET ${url}${uri}
    echo -e
}

function DocsWarningRecordCount()
{
    uri="docs/file/warning_record/count"
    
    curl -X GET ${url}${uri}
    echo -e
}

########################################################################################

function WarningRecordClear()
{
    uri="setting/warning_record/clear"
    
    curl -X GET ${url}${uri}
    echo -e
}

########################################################################################

function CameraTest()
{
    uri="setting/camera/test"

    if [[ -z $1 ]]; then 
        echo "empty json file"
    else
        curl -X POST --data-binary @$1 ${url}${uri}
    fi 
    echo -e
}

function CameraList()
{
    uri="setting/camera/list"

    curl -X GET ${url}${uri}
    echo -e
}

########################################################################################

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
    elif [[ $1 == "${cmd_map[6]}" ]]; then 
        DeviceNetwork
    elif [[ $1 == "${cmd_map[7]}" ]]; then 
        DeviceSystime
    elif [[ $1 == "${cmd_map[8]}" ]]; then 
        DocsList
    elif [[ $1 == "${cmd_map[9]}" ]]; then 
        DocsCameraList
    elif [[ $1 == "${cmd_map[10]}" ]]; then 
        DocsUploadAlarm
    elif [[ $1 == "${cmd_map[11]}" ]]; then 
        DocsWarningRecordList
    elif [[ $1 == "${cmd_map[12]}" ]]; then 
        DocsCameraAdd
    elif [[ $1 == "${cmd_map[13]}" ]]; then 
        DocsCameraUpdate
    elif [[ $1 == "${cmd_map[14]}" ]]; then 
        DocsCameraDelete
    elif [[ $1 == "${cmd_map[15]}" ]]; then 
        DocsWarningRecordView
    elif [[ $1 == "${cmd_map[16]}" ]]; then 
        DocsWarningRecordDelete
    elif [[ $1 == "${cmd_map[17]}" ]]; then 
        DocsWarningRecordRemark
    elif [[ $1 == "${cmd_map[18]}" ]]; then 
        DocsWarningRecordCount
    elif [[ $1 == "${cmd_map[19]}" ]]; then 
        WarningRecordClear
    elif [[ $1 == "${cmd_map[20]}" ]]; then 
        CameraTest $2
    elif [[ $1 == "${cmd_map[21]}" ]]; then 
        CameraList
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