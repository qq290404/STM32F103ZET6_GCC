@ECHO OFF

set HOME=%USERPROFILE%
set RootPath=%cd%

if exist tools\tmp GOTO OSBITNESSCHECK
@mkdir tools\tmp 

:OSBITNESSCHECK
if defined PROGRAMFILES(X86) (
    GOTO 64BIT
) else (
    GOTO 32BIT
)

:64BIT
echo 64-bit system detected
GOTO END

:32BIT
echo 32-bit system detected
GOTO END

:END
set path=%RootPath%\tools\linux\bin;%RootPath%\tools\toolchain\gcc-arm-none-eabi\bin;%RootPath%\tools\Python 2.7
C:\WINDOWS\system32\cmd.exe