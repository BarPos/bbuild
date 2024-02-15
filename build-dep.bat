mkdir mbuild
mkdir mbuild\yaml-cpp
del mbuild\yaml-cpp\*

cd mbuild\yaml-cpp
clang -xc++ -Wall -c -DYAML_CPP_STATIC_DEFINE -I..\..\vendor\yaml-cpp\include\ ..\..\vendor\yaml-cpp\src\**.cpp
llvm-ar rc yaml-cpp.lib *.o

