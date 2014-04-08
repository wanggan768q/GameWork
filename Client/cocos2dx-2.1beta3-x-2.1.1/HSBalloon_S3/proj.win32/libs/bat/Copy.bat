@echo 0ff

set isRun=1
if %isRun% EQU 0 exit


set cocos2dxRoot=F:\Work\IOS\Client\cocos2dx-2.1beta3-x-2.1.1\
set HSBalloonProject=HSBalloon_S3\proj.win32\
set debug="%cocos2dxRoot%Debug.win32\"
set debugCopy=%cocos2dxRoot%Debug.win32.Copy


if not exist "%debugCopy%" mkdir "%debugCopy%"
if exist "%debug%"iphone rd /s /q "%debug%"iphone
if exist "%debug%"music rd /s /q "%debug%"music
@xcopy "%cocos2dxRoot%%HSBalloonProject%Resources\*" "%debugCopy%" /s /c /y /e
@xcopy "%debug%*" "%debugCopy%" /s /c /y /e

cd %debugCopy%

del GameCacheData.data

start HSBalloon_S3.win32.exe
::pause
exit