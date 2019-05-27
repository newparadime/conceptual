#!/usr/bin/env python
from math import log, floor, sqrt

def answer(tLambs):
    if tLambs <= 3:
        return 0
    
    totGen = fastFloorLog2(tLambs+1)
    genTotPay = (1<<totGen)-1
    genRem = tLambs - genTotPay
    
    if check3([fastPow2(totGen-2), fastPow2(totGen-1)], genRem):
        totGen += 1
    
    fib = [1,1]
    fibSum = [1,2]
    
    while fibSum[-1] <= tLambs:
        fib.append(fib[-1]+fib[-2])
        fibSum.append(fibSum[-1]+fib[-1])
    fib.pop()
    fibSum.pop()
    
    stRem = tLambs - fibSum[-1]
    totSt = len(fibSum)
    
    if check3(fib, stRem):
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
