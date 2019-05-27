#!/usr/bin/env python
from math import log, floor, sqrt

def answer(tLambs):
    if tLambs <= 3:
        return 0
    totGen  = fastFloorLog2(tLambs+1)
    l2Gen = pow(2,tGenerous-2)
    l1Gen = l2Gen*2
    remGen  = tLambs - (l1Gen*2-1)
    if 
    
    tStingy   = fibIndexFromFibSum(tLambs)
    return tStingy - tGenerous


def answer(tLambs):
    if tLambs <= 3:
        return 0
    tGenerous  = fastFloorLog2(tLambs+1)
    st = 1
    stSum = sumFib(st)
    while stSum <= tLambs:
        tStingy = st
        st += 1
        stSum += sumFib(st)
    
    
    return tStingy - tGenerous


def answer(tLambs):
    if tLambs <= 3:
        return 0
    tGenerous  = fastFloorLog2(tLambs+1)
    tStingy   = fibIndexFromFibSum(tLambs)
    return tStingy - tGenerous
    
def fibIndexFromFibSum(S):
    return firstPrecedingFib(S+1) - 2

def check2(payouts, tPayout):
    if payouts[-1] > (payouts[-2] * 2):
        return False
    return True

def check3(payouts, tPayout):
    if (payouts[-3] + payouts[-2]) > payouts[-1]:
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
    
def sumFib(n):
    return fibMatrix(n+2)-1
    
def fibMatrix(n):
    v1, v2, v3 = 1, 1, 0
    for rec in bin(n)[3:]:
        v2sq = v2**2
        v1, v2, v3 = v1**2+v2sq, (v1+v3)*v2, v2sq+v3**2
        if n & 1:    v1, v2, v3 = v1+v2, v1, v2
    return v2

def invFibApprox(F):
    S5  = sqrt(5)
    GLD = (1+S5)/2
    res = floor(log(F * S5 + 0.5, GLD))
    return int(res)
    
def firstPrecedingFib(F):
    na = invFibApprox(F)
    f = fibMatrix(na)
    while f > F:
        na -= 1
        f = fibMatrix(na)
    while f <= F:
        na += 1
        f = fibMatrix(na)
    return na - 1
    

