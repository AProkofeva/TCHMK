Linux:
	g++ -c MathFuncs.cpp
	g++ -shared -o MathFuncsDll.dll MathFuncsDll.o
	g++ MyDll.cpp MathFuncsDll.dll -I. -Wl,-rpath,. -L. -o crypt2

Windows (compiled with g++):
	g++ -c MathFuncs.cpp
	g++ -shared -o MathFuncsDll.dll MathFuncsDll.o
	g++ MyDll.cpp MathFuncsDll.dll -I. -Wl,-rpath,. -L. -o bigint.exe