  
@echo off

set solutiondir=%1
set target=%2

echo Copiando archivos...

xcopy %solutiondir%libs\glew-2.1.0\bin\Release\Win32\glew32.dll %target% /y /s
echo Copied Glew32.dll

echo Copia finalizada