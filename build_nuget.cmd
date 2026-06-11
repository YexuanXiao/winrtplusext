@echo off
setlocal

set target_version=%1
if "%target_version%"=="" set target_version=999.999.999.999

pushd "%~dp0"
nuget pack YexuanXiao.CppWinRTPlus.Ext.nuspec -Properties target_version=%target_version%
popd
