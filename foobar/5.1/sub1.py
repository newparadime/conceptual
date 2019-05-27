#!/usr/bin/env python

from math import factorial

def nC2(n):
    return int((n-1)*n/2)
    
def highPrecisionIntegerDivision(n, d):
    ans = 0
    while n >= d:
        n -= d
        ans += 1
    
    return ans, n
    
def intPower(base, exp):
    intBase = int(base)
    intExp  = int(exp)
    return int(pow(intBase, intExp))
    
def answer(w, h, s):
    hC2 = nC2(h)
    wC2 = nC2(w)
    
    print hC2, wC2
    
    Gc = factorial(h) * factorial(w)
    n1 = intPower(s,(w*h))
    n2 = hC2*intPower(s,(w*(h-1)))
    n3 = wC2*intPower(s,((w-1)*h))
    n4 = hC2*wC2*intPower(s,((w-1)*(h-1)))
    n = n1 + n2 + n3 + n4
    #n = s**(w*h)
    
    #combs, rem = highPrecisionIntegerDivision(n, Gc)
    
    combs = n / Gc
    
    print n1, n2, n3, n4
    print n
    print Gc
    print combs
    return str(combs)
    
    
def main1():
        
    ans = answer(12, 12, 20)
    print (ans)
    
#def main2():
    
if __name__ == "__main__":
    main1()
