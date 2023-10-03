@echo off
setlocal enabledelayedexpansion
set "totalCount=0"

for /r %%i in (*.cpp *.h) do (
    for /f %%j in ('type "%%i" ^| find /c ";"') do (
        set /a "totalCount+=%%j"
    )
)

echo Total semicolons found: %totalCount%