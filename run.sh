BUILD_TYPE=${1:-Debug}

rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
cmake --build .
cd bin
./MyProjectC
cd ../../
