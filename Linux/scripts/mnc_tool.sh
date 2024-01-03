#! /bin/bash 


curl -X POST --data "{\"id\":\"Qk99V\"}" http://127.0.0.1:8000/api/setting/task/stop

curl -X POST --data "{\"id\":\"Qk99V\"}" http://127.0.0.1:8000/api/setting/task/start

curl -X GET http://127.0.0.1:8000/api/setting/task/list

curl -X GET http://127.0.0.1:8000/api/setting/camera/list

# 清除所有告警记录
curl -X GET http://127.0.0.1:8000/api/setting/warning_record/clear