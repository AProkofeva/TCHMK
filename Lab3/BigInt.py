#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import MathFuncsDll

print "Enter string in such way:"
print "\n<name of program> <filename A> <operation>\n<filename B> <result filename C> [b] [filename with module]\n\n"
#print(sys.argv)
if len(sys.argv)<2:
    print "Fatal: You forgot to include the directory name on the command line."
    print "Usage:  python %s <directoryname>" % sys.argv[0]
    sys.exit(1)
file1 = sys.argv[1]
oper = sys.argv[2]
file2 =sys.argv[3]
result = sys.argv[4]
bin = False
if len(sys.argv) < 5 or len(sys.argv) > 7:
    print "Error! Too few or too much arguments in string"
    sys.exit(-1)
#elif :len(sys.argv) > 7:
#	print "Too much arguments in string"
 #   sys.exit(-1)
else:
	modBool = False
	base = 10
	mod = ""
	if len(sys.argv) == 6:
		if sys.argv[5] == "-b":
            #base = 256
			bin = True;
		else:
			mod = sys.argv[5]
			modBool = True;
	elif len(sys.argv) == 7:
		if sys.argv[5] == "-b":
            #base = 256
			bin = True;
		mod = sys.argv[6]
		modBool = True;

        
#print "file1: " + file1
#print "oper: " + oper
#print "file2: " + file2
#print "result: " + result
#print "bin: " + bin
#print "mod: " + mod

a = MathFuncsDll.BigInt()
b = MathFuncsDll.BigInt()
a = a.Read(file1,base,bin)
b = b.Read(file2,base,bin)

if oper == "+": 
	a = a + b
elif oper == "-": 
	a = a - b
elif oper == "*": 
	a = a * b
elif oper == "/": 
	a = a / b
elif oper == "%": 
	a = a % b
elif oper == "^":
	if modBool == True:
		m = MathFuncsDll.BigInt()
		m = m.Read(mod,base,bin)
		a = a.Power(a,b,m)
	else:
		print "\nerror: mod file not found!"
		sys.exit(-1)		
if modBool == True:
	m = MathFuncsDll.BigInt()
	m = m.Read(mod,base,bin)
	a = a % m
a.Write(result,bin)
print "\nOperation was succesfully done!"