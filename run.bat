cmake CMakeLists.txt
cmake --install .
cmake --build .
copy src\\studentai_1000.txt build\\Debug\\studentai_1000.txt
cd Debug\
pirmas_obj.exe
pause