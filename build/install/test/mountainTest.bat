
@echo off
SETLOCAL

CALL "%~dp0lib\mountainTest.exe" %*
EXIT /B %ERRORLEVEL%
ENDLOCAL
