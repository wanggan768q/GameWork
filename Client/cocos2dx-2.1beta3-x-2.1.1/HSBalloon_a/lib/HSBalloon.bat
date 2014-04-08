@echo on

set projectRoot=F:\Wrok\IOS\Client\cocos2dx-2.1beta3-x-2.1.1\
set cocos2dProject=HSBalloon\proj.win32
set androidProject=HSBalloon_a
set libProject=libHS\proj.win32
set classFloer="%projectRoot%"\"%androidProject%"\Classes\
set resources="%projectRoot%"\"%androidProject%"\Resources\

::Base
@xcopy "%projectRoot%"\"%cocos2dProject%"\* "%classFloer%" /s /c /y /e


@xcopy "%projectRoot%"\"%libProject%"\* "%classFloer%" /s /c /y /e

::Resources
xcopy "%projectRoot%"\"%cocos2dProject%"\Resources\* "%resources%" /s /c /y







pause