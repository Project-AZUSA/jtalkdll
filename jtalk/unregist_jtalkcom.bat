@echo off
openfiles > NUL 2>&1
if not %ERRORLEVEL% == 0 (
echo �Ǘ��Ҍ����Ŏ��s���Ă�������
pause
goto :eof
)
cd /d %~dp0
if "%PROCESSOR_ARCHITECTURE%" == "x86" (
C:\Windows\Microsoft.NET\Framework\v4.0.30319\regasm.exe JTalkCOMx86.dll /unregister
) else (
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\regasm.exe JTalkCOMx64.dll /unregister
)
pause