:loop
917Egen.exe > data.in
917Estd.cpp.exe < data.in >1.out
917Enaive.cpp.exe <data.in >2.out 
fc 1.out 2.out
if %errorlevel% == 0 goto loop
pause