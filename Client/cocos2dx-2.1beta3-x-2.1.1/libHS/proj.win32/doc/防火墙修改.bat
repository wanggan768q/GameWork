
@echo off

@echo 为了解决win7上写Http 协议的时候 出现防火墙拦截问题。 
@echo 需要修改注册表值 有问题问 Ambition



cd %windir%\system32
Regsvr32 Msxml3.dll

Pause 
