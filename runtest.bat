@echo off
set BUILD_TYPE=%1
if not defined BUILD_TYPE set BUILD_TYPE=Release

rd /s /q build
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
cmake --build .
cd bin
test_executable.exe
cd ../../