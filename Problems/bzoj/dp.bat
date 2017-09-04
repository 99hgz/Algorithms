:loop
gen.cpp.exe >e:\1.txt
2333.cpp.exe<e:\1.txt >e:\a.txt 
2333-std.cpp.exe <e:\1.txt >e:\b.txt
fc e:\a.txt e:\b.txt
if not errorlevel 1 goto loop  
pause 