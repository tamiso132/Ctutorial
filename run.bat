rd build
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
cd bin
MyProjectC.exe
cd ../../