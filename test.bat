..\TDM-GCC-64\bin\g++.exe "./src/test.cpp" -o"test.exe" -std=c++17 -I"./includes/" -L"./bin/x64/" -L"./lib/x64/" -lgdi32 -lopengl32 -lfreeglut -lglu32 -lUser32 -lglew32
test.exe 
del test.exe
pause>nul