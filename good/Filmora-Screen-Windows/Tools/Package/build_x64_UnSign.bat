@echo off

if exist ".\Output" (rmdir /s /q .\Output)

echo ========================================
echo ��ʼ����FilmoraScreen...
echo ========================================
set VCENV="%VS120COMNTOOLS:"=%..\IDE\devenv.com"
set log="build_x64.txt"
if exist %log% (del %log%)
rem %VCENV% ../../FilmoraScreen.sln /rebuild "Release|x64" /Out %log%
rem if %errorlevel% NEQ 0 goto label_error

goto next

:label_error
echo ����FilmoraScreen��������������±���... 
pause

:next
echo FilmoraScreen�������

rem ���
set COMPIL32="%systemdrive%\Program Files\Inno Setup 5\ISCC.exe"
if not exist %COMPIL32% set COMPIL32="%systemdrive%\Program Files (x86)\Inno Setup 5\ISCC.exe"
set errorlevel=0
echo ========���FilmoraScreen(x64)��װ���� ......%time%
%COMPIL32% .\filmorascreen.iss /dCPUX64
if not %errorlevel%==0 echo ����:��������汾���� &pause

echo д�������xml�ļ� ...
..\..\Tools\WSOverlay.exe /P "Output\Filmora Scrn(x64).exe" "..\..\Tools\Customization.xml"

echo ========================================
echo ���
echo ========================================

pause


