@echo off

:loop
	data.exe > in.txt
	ds.exe < in.txt > std.txt
	P3792.exe < in.txt > my.txt
	fc std.txt my.txt
	if not errorlevel 1 goto loop
	pause
	goto loop
