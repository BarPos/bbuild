mkdir build
del build\bbuild.exe

cd build
clang -xc++ -Wall -std=c++17 -DYAML_CPP_STATIC_DEFINE -Lyaml-cpp\yaml-cpp -I..\bbuild\src\ -I..\vendor\yaml-cpp\include\ ..\bbuild\src\main.cpp -o bbuild.exe

