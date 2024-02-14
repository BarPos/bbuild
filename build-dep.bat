mkdir mbuild
rmdir -Fo -R mbuild\yaml-cpp
mkdir mbuild\yaml-cpp

cd mbuild\yaml-cpp
clang -xc++ -c -DYAML_CPP_STATIC_DEFINE -I..\..\vendor\yaml-cpp\include\ ..\..\vendor\yaml-cpp\src\**.cpp
ar r yaml-cpp.lib *.o

