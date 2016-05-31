Linux: 
	swig -c++ -python MathFuncs.i 
	g++ -fPIC -c MathFuncsDll.cpp 
	g++ -fPIC -c MathFuncsDll_wrap.cxx -I/usr/include/python2.7 
	g++ -shared MathFuncsDll.o MathFuncs_wrap.o -o _MathFuncsDll.so 

Windows: 
	swig -c++ -python MathFuncs.i 
	g++ -fPIC -c MathFuncsDll.cpp 
	g++ -c MathFuncsDll_wrap.cxx -IC:\Python27\include 
	g++ MathFuncsDll.o MathFuncs_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _MathFuncsDll.pyd