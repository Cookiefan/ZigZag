//对拍
:loop
datamaker.exe
a1.exe a2.exe
fc a1.out a2.out
if %errorlevel%==1 pause
goto loop