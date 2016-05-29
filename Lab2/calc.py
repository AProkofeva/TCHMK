	
f = open("1b.txt") 
g = open("2b.txt") 
h = open("4b.txt") 
x=int(f.read()) 
y=int(g.read()) 
z=int(h.read())
s=x+y
print '\n\n+ :\n'+str(s)
s=x-y
print '\n\n- :\n'+str(s)
s=x*y
print '\n\n* :\n'+str(s)
s=x/y
print '\n\n/ :\n'+str(s)
s=x % y
print '\n\n| :\n'+str(s)
s=pow(x, y,z) 
print '\n\n ^ & | :\n'+str(s)