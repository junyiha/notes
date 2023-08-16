#! /bin/bash 

COB="./cob-cmd.sh --move-to "

${COB} ./joint_zero.json

${COB} ./joint_space.json

${COB} ./tcp_space.json

read -p "move to joint zero position ? [yes/no] >>>: " cmd

if [[ ${cmd} == "yes" ]]; then 
    ${COB} ./joint_zero.json
fi

echo "---done---"