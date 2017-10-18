@echo off  
:loop 
gen.exe>in.txt  
F.cpp.exe<in.txt>myout.txt  
F2.cpp.exe<in.txt>stdout.txt  
  
fc myout.txt stdout.txt  
  
if not errorlevel 1 goto loop  
  
pause  
  
goto loop  