:: remove c++ projects output and intermediate
rmdir _out /q /s
rmdir _tmp /q /s

:: remove build
rmdir Build /q /s

:: remove visual studio files and log files
rmdir .vs /q /s
del *.log

:: change to visual studio project folder and delete user settings
cd Tetris
del /q /s /f *.vcxproj.user