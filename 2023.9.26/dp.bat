@echo off
:loop
	data.exe > in.txt
	std.exe < in.txt > std.txt
	SP4487.exe < in.txt > my.txt
	fc std.txt my.txt
if not errorlevel 1 goto loop
pause
goto loop
