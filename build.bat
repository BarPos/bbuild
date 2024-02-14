mkdir mbuild
del mbuild\bbuild.exe

cd mbuild
clang -xc++ -Wall -std=c++17 -DYAML_CPP_STATIC_DEFINE -lyaml-cpp\yaml-cpp -I..\bbuild\src\ -I..\vendor\yaml-cpp\include\ ..\bbuild\src\**.cpp -o bbuild.exe


