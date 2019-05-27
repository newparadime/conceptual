#!/usr/bin/env python
from math import log, floor, sqrt

def answer(tLambs):
    if tLambs <= 3:
        return 0
    
    totGen = fastFloorLog2(tLambs+1)
    genTotPay = fastPow2(2,totGen)-1
    
    genRem = tLambs - genTotPay
    if check2([fastPow2(2,totGen-2), fastPow2(2,totGen-1)], genRem):
        totGen += 1
    
    fib = [1,1]
    fibSum = 2
    
    while fibSum+fib[-1] <= tLambs:
        fib.append(fib[-1]+fib[-2])
        fibSum += fib[-1]
    
    stRem = tLambs - fibSum[-1]
    totSt = len(fibSum)
    
    if check2(fib, stRem) and check3(fib, stRem):
        totSt += 1
    
    return totSt - totGen
    
def check3(payouts, remLamb):
    if (payouts[-2] + payouts[-1]) > remLamb:
        return False
    return True
    
def fastFloorLog2(n):
    if (n < 1):
        return None
    exp = 0
    while n > 1:
        exp += 1
        n = n >> 1
    return exp
    
def fastPow2(n):
    return 1<<n
    
    
ans = answer(143)

print (ans)
