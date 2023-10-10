@echo off
:loop
	data.exe > in.txt
	CF1054D.exe < in.txt > my.txt
	test.exe < in.txt > std.txt
	fc my.txt std.txt
	if not errorlevel 1 goto loop
	pause
	goto loop
