#!/usr/bin/env python
from fractions import Fraction
from fractions import gcd
from decimal import Decimal, getcontext
def lcm(L):
    b, a = L.pop(), L.pop()
    r = (a * b)/gcd(a, b)
    while L:
        n = L.pop()
        r = (r * n)/gcd(r,n)
    return r
    
    
M = [8, 15, 10, 7]

N = [2,3,5]

O = [8,10]

P = [15,7]

print lcm(M)
print lcm(N)
print lcm(O)
print lcm(P)
print lcm([40,105])
print lcm([8,15])
print lcm([120,10])
print lcm([120,7])
getcontext().prec = 4
nl = [i**2 for i in xrange(1,10)]
nd = {i:{'days':v} for (i,v) in enumerate(nl)}
for k,f in nd.iteritems():
    getcontext().prec = 2
    print "{}: {}".format(k, f)
    
print sum(1.00/m for m in xrange(0,4) if m > 0)
