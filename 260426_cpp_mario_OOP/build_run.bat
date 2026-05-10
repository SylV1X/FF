@echo off
chcp 1251 > log
del log 

set MAIN="main.cpp GameObject.cpp MovingObject.cpp Sprite.cpp Map.cpp Level.cpp Player.cpp"
set EXE=mario.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" "%MAIN%" -o %EXE%

%EXE%