#! /bin/bash 

username="root"
# remote_host="192.169.0.152"
arg1=" -o StrictHostKeyChecking=no "
remote_host="47.100.31.121"
# passwd="111111"
passwd="ematech"

success_file="/home/user/zjy-190/Documents/rk_1126/rk_release/frp_release/success.txt"
fail_file="/home/user/zjy-190/Documents/rk_1126/rk_release/frp_release/fail.txt"

echo true > ${success_file}
echo true > ${fail_file}

for i in {1001..1014}
{
    rk_index="gh-rk-"
    rk_index=${rk_index}"${i}"
    echo ${rk_index}
    ssh-keygen -f "/home/user/.ssh/known_hosts" -R "47.100.31.121"

    arg=" -o 'proxycommand socat - PROXY:47.100.31.121:${rk_index}:22,proxyport=5002' "

    echo "sshpass -p ${passwd} ssh ${arg1}  ${arg} "${username}@${remote_host}" ls"
    eval "sshpass -p ${passwd} ssh ${arg1}  ${arg} "${username}@${remote_host}" ls"

    if [ $? -eq 0 ]; then 
    {
        echo "ssh success: ${rk_index}"
        echo "ssh success: ${rk_index}" >> ${success_file}
        echo -e >> ${success_file}
    }
    else 
    {
        echo "ssh fail: ${rk_index}"
        echo "ssh fail: ${rk_index}" >> ${fail_file}
        echo -e >> ${fail_file}
    }
    fi
}