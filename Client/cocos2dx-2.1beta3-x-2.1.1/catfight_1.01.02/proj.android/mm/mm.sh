#!/bin/sh

#mm渠道
echo "运行mm.sh"

echo "调用origion.sh，恢复原始状态"

../origion/origion.sh


echo "拷贝资源"
cp ./assets/*.data ../assets/
cp ./assets/iphone/Data/*.data ../assets/iphone/Data/
cp ./libs/*.jar ../libs/

echo "mm.sh 运行完毕"