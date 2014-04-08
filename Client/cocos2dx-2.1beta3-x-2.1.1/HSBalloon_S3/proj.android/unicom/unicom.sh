#!/bin/sh


#联通版渠道

echo "运行unicom.sh"

echo "调用origion.sh，恢复原始状态"
../origion/origion.sh


echo "拷贝资源"

#拷贝res/icon.png
cp ./res/drawable-ldpi/icon.png ../res/drawable-ldpi/
cp ./res/drawable-mdpi/icon.png ../res/drawable-mdpi/
cp ./res/drawable-hdpi/icon.png ../res/drawable-hdpi/
cp ./res/drawable-xhdpi/icon.png ../res/drawable-xhdpi/
cp ./res/drawable-xxhdpi/icon.png ../res/drawable-xxhdpi/


cp ./assets/iphone/Image/*.png ../assets/iphone/Image/
cp ./assets/iphone/Image/*.data ../assets/iphone/Image/

echo "unicom.sh 运行完毕"