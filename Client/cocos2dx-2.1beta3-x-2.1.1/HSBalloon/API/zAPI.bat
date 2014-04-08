@echo on

del /s *.cc
del /s *.cpp
del /s *h

::option optimize_for = LITE_RUNTIME; 
::.\Debug\protoc --cpp_out=./ UserLogin.proto
::.\Debug\protoc --java_out=./ UserLogin.proto

::.\Debug\protoc.exe -I =. --cpp_out=./ PropInfo.proto

::protoc.exe -I =. --cpp_out=./ PropInfo.proto

::================================================================================

protoc.exe -I =. --cpp_out=./ HSChannel.proto
protoc.exe -I =. --java_out=./ HSChannel.proto






















































::================================================================================

ren *.cc *.cpp

set src=F:\Work\IOS\Client\cocos2d-1.0.1-x-0.10.0\HighlordStoryAPI
set dest=F:\Work\IOS\Client\cocos2d-1.0.1-x-0.10.0\HighlordStory\NetMessage

::copy "%src%"\*cpp "%dest%" /y
::copy "%src%"\*h "%dest%" /y

::del /s *.cc
::del /s *.cpp
::del /s *h

pause