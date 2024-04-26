import psutil 
import os
import time
import subprocess
import logging
from logging.handlers import TimedRotatingFileHandler

log_file = '/tmp/record_script.log'

# 创建 logger 对象
logger = logging.getLogger("my_logger")
logger.setLevel(logging.DEBUG)

# 创建 TimedRotatingFileHandler 处理程序
when = "midnight"  # 日志文件滚动的时间点，这里是每天的午夜
interval = 1  # 滚动的时间间隔，这里是每天
backup_count = 5  # 保留的备份文件数量
file_handler = TimedRotatingFileHandler(log_file, when=when, interval=interval, backupCount=backup_count)

# 创建格式化器
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
file_handler.setFormatter(formatter)

# 将处理程序添加到 logger
logger.addHandler(file_handler)

if __name__ == "__main__":

    try:
        # subprocess.run("source /data/static/bash/source.sh", shell=True, check=True)
        subprocess.run(". /data/static/bash/source.sh", shell=True, check=True)
        logging.info(f"update environment success")
    except subprocess.CalledProcessError as e:
        logging.info(f"update environment failed\n")
        logging.error(f"Error: {e}")
        exit(-1)
    
    index = 1
    whole_time = 60 * 60 * 3  # 3h
    begin = time.time()
    while True:
        command = f"/data/edge/VideoProcess/3party/bin/ffmpeg -rtsp_transport tcp -i rtsp://127.0.0.1:554/live/ZGxxK -c copy -an -f mp4 -t 00:20:30 /userdata/zzz-{index}.mp4"
        try:
            subprocess.run(command, shell=True, check=True)
            logger.info(f"record success, command: {command}")
        except subprocess.CalledProcessError as e:
            logger.error(f"Error: {e}")
        tmp = time.time()
        record_time = tmp - begin
        if record_time > whole_time:
            logger.info("exit from dead loop")
            break
        index = index + 1

    logging.log("--end---")
