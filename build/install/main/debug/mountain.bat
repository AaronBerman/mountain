
@echo off
SETLOCAL

CALL "%~dp0lib\mountain.exe" %*
EXIT /B %ERRORLEVEL%
ENDLOCAL
