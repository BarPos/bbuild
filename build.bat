mkdir mbuild
mkdir mbuild\bbuild
del mbuild\bbuild\*

cd mbuild\bbuild
clang -xc++ -c -Wall -std=c++17 -DYAML_CPP_STATIC_DEFINE -I..\..\bbuild\src\ -I..\..\vendor\yaml-cpp\include\ ..\..\bbuild\src\**.cpp
clang -l..\yaml-cpp\yaml-cpp *.o -o bbuild.exe

