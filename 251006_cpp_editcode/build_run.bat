@echo off
chcp 1251 > log
del log 

set MAIN="main.cpp random_arr.cpp amount_arr.cpp sort_arr.cpp io.cpp"
set EXE=counting_sort.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" "%MAIN%" -o %EXE%

%EXE%