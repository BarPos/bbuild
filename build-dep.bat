mkdir build
rmdir -Fo -R build\yaml-cpp
mkdir build\yaml-cpp

cd build\yaml-cpp
clang -xc++ -c -DYAML_CPP_STATIC_DEFINE -I..\..\vendor\yaml-cpp\include\ ..\..\vendor\yaml-cpp\src\**.cpp
ar r yaml-cpp.lib *.o

