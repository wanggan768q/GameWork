#!/bin/sh

#拷贝res/icon.png
#原始版用的是微派的计费渠道


CURRENT_PATH=$(cd "$(dirname "$0")"; pwd)

echo CURRENT_PATH=$CURRENT_PATH

rm $CURRENT_PATH/../res/drawable-ldpi/*.png
rm $CURRENT_PATH/../res/drawable-mdpi/*.png
rm $CURRENT_PATH/../res/drawable-hdpi/*.png
rm $CURRENT_PATH/../res/drawable-xhdpi/*.png
rm $CURRENT_PATH/../res/drawable-xxhdpi/*.png

rm $CURRENT_PATH/../assets/iphone/Image/*.png
rm $CURRENT_PATH/../assets/iphone/Image/*.data
rm $CURRENT_PATH/../assets/iphone/Image/*.plist

rm $CURRENT_PATH/../assets/*.data
rm $CURRENT_PATH/../assets/iphone/Data/*.data



cp $CURRENT_PATH/res/drawable-ldpi/*.png $CURRENT_PATH/../res/drawable-ldpi/
cp $CURRENT_PATH/res/drawable-mdpi/*.png $CURRENT_PATH/../res/drawable-mdpi/
cp $CURRENT_PATH/res/drawable-hdpi/*.png $CURRENT_PATH/../res/drawable-hdpi/
cp $CURRENT_PATH/res/drawable-xhdpi/*.png $CURRENT_PATH/../res/drawable-xhdpi/
cp $CURRENT_PATH/res/drawable-xxhdpi/*.png $CURRENT_PATH/../res/drawable-xxhdpi/

cp $CURRENT_PATH/../../Resources/iphone/Image/*.png $CURRENT_PATH/../assets/iphone/Image/
cp $CURRENT_PATH/../../Resources/iphone/Image/*.data $CURRENT_PATH/../assets/iphone/Image/
cp $CURRENT_PATH/../../Resources/iphone/Image/*.plist $CURRENT_PATH/../assets/iphone/Image/

cp $CURRENT_PATH/assets/*.data ../assets/
cp $CURRENT_PATH/../../Resources/iphone/Data/*.data $CURRENT_PATH/../assets/iphone/Data/

cp $CURRENT_PATH/libs/*.jar $CURRENT_PATH/../libs/
echo origion.sh执行完毕


