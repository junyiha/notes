#! /bin/bash 

declare -A fruits
fruits["apple"]="red"
fruits["banana"]="yellow"
fruits["orange"]="orange"

# 使用映射
echo "Color of apple is ${fruits["apple"]}"
echo "Color of banana is ${fruits["banana"]}"
echo "Color of orange is ${fruits["orange"]}"

declare -A cmd_map

cmd_map["-h"]="Help"
cmd_map["--move-to"]="MoveTo"
cmd_map[3]="one"

echo "help : ${cmd_map["-h"]}"
echo "3: ${cmd_map[3]}"