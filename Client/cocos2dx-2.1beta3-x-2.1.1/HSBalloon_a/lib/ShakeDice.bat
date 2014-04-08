@echo on

set projectRoot=F:\Work\IOS\Client\cocos2d-1.0.1-x-0.10.0
set cocos2dProject=ShakeDice
set androidProject=HSGame
set libProject=libHS
set classFloer="%projectRoot%"\"%androidProject%"\android\jni\Classes\
set resources="%projectRoot%"\"%androidProject%"\Resources\

::Base
xcopy "%projectRoot%"\"%cocos2dProject%"\* "%classFloer%" /s /c /y /e


xcopy "%projectRoot%"\"%libProject%"\* "%classFloer%" /s /c /y /e

::Resources
xcopy "%projectRoot%"\"%cocos2dProject%"\Resources\iphone\* "%resources%" /s /c /y




::pause