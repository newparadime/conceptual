#!/usr/bin/env python

import math

def fastFloorLog2(n):
    exp = 0
    while n > 1:
        exp += 1
        n = n >> 1
    return exp

def sumPow2(n, l=Ellipsis):
    exp = 0
    res = 0
    cur = 1
    while res <= l and exp <= n:
        res += cur
        print (exp, cur, res)
        cur *= 2
        exp += 1
    return res

for x in range(1, 0x100):
    xf = fastFloorLog2(x)
    xl = math.log(x, 2)
    print('xf=0x%08x', xf)
    print('xl=0x%08x', xl)
    
n = 7
ns2 = sumPow2(n)
print "n={0}".format(n) + " ns2={0}".format(ns2) + " ({0:#x})".format(ns2) + "({0:#b})".format(ns2)
