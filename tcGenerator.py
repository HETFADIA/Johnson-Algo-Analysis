#open repl compiler and write this code then go to shell and write python3 main.py to generate the tcs
import random;
import sys;
output=open("output.txt","w");
test=1
n=10
d=1
inf=999999
def print(a):
    output.write(str(a))
def prints(a,b):
    output.write(str(a)+" " +str(b))
def ran():
    
    return random.randint(0,1000)
def gen():
    rand=ran();
    prob=random.random()<0.00001
    if(rand>500):
        return inf;
    else:
        if(rand==-1):
            if(prob):
                return rand;
            return rand+2;
        return rand;
print(test)
print("\n")
for i in range(test):
    prints(n,d)
    print("\n")
    for j in range(n):
        for k in range(n):
            if j!=k:
                r=gen();
                print(r)
                print(" ")
            else:
                print(0)
                print(" ")
        print("\n")
