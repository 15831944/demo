@echo off

if exist ".\Output" (rmdir /s /q .\Output)

echo ========================================
echo ��ʼ����FilmoraScreen...
echo ========================================
set VCENV="%VS120COMNTOOLS:"=%..\IDE\devenv.com"
set log="build_x64.txt"
if exist %log% (del %log%)
%VCENV% "..\..\FilmoraScreen.sln" /rebuild "Release|x64" /Out %log%
if %errorlevel% NEQ 0 (
echo ����FilmoraScreen��������������±���... 
exit
)

echo FilmoraScreen�������

echo ========FSRecorder.exeǩ�� ......%time%

call ".\SignFile_x64.bat" _Recorder

rem ���
set COMPIL32="%systemdrive%\Program Files\Inno Setup 5(u)\ISCC.exe"
if not exist %COMPIL32% set COMPIL32="%systemdrive%\Program Files (x86)\Inno Setup 5(u)\ISCC.exe"

echo ========���FilmoraScreen(x64)��װ���� ......%time%
%COMPIL32% .\filmorascreen.iss /dCPUX64
if not %errorlevel%==0 (
echo ����:��������汾����
exit
) 
echo ^>^>^>^>^>^>^>^>FilmoraScreen(x64)��װ���������

echo д�������xml�ļ� ...
..\WSOverlay.exe /P "Output\Filmora Scrn(x64).exe" "..\Customization.xml"

echo ========��װ����ǩ�� ......%time%
call ".\SignFile_x64.bat" _Ins
if not %errorlevel%==0 (
echo ��װ��ǩ������
exit
)


echo ========================================
echo ���
echo ========================================


