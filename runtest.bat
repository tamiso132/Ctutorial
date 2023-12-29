rd /s /q build
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
cd bin
test_executable.exe
cd ../../