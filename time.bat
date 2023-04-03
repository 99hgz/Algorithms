@echo off  
:loop  
    python ./gen.py > in.txt
    1.cpp.exe < in.txt > myout.txt
    2.cpp.exe < in.txt > stdout.txt
    fc myout.txt stdout.txt
if not errorlevel 1 goto loop  
pause
goto loop