#!/usr/bin/env python

import math
from math import log
  
def fibRound(n):
    S5  = math.sqrt(5)
    GLD = (1+S5)/2
    res = math.floor((GLD**n)/S5 + 0.5)
    return res
    
def invFibApprox(F):
    S5  = math.sqrt(5)
    GLD = (1+S5)/2
    res = math.floor(math.log(F * S5 + 0.5, GLD))
    return int(res)
    
def fibMatrix(n):
    n = int(n)
    v1, v2, v3 = 1, 1, 0
    for rec in bin(n)[3:]:
        v2sq = v2**2
        v1, v2, v3 = v1**2+v2sq, (v1+v3)*v2, v2sq+v3**2
        if rec == '1':    v1, v2, v3 = v1+v2, v1, v2
    return v2

def sumFib(n):
    return fibMatrix(n+2)-1

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

def answer(tLambs):
    if tLambs <= 3:
        return 0
    tGenerous  = fastFloorLog2(tLambs+1)
    tStingy   = fibIndexFromFibSum(tLambs)
    return tStingy - tGenerous

def fastFloorLog2(n):
    if (n < 1):
        return None
    exp = 0
    while n > 1:
        exp += 1
        n = n >> 1
    return exp

def fibIndexFromFibSum(S):
    return firstPrecedingFib(S+1) - 2

def main1():
    width = 21
    n = 1
    while n < 100:
        fm = fibMatrix(n)
        print '[{0: <3}]'.format(n) + ' fm: {0: >{1}}'.format(fm, width)
        n+=1
        
def main2():
    width = 21
    n = 70
    for n in range(70, 101):
        fm = fibMatrix(n)
        fr = fibRound(n)
        nfm = nfibRound(fm)
        nfr = nfibRound(fr)
        print '[{0: <3}]'.format(n) + \
        ' fc:{0: >{1}}'.format(fm, width) + \
        ' fr: {0: >{1}}'.format(fr, width)+ \
        ' fm: {0: >{1}}'.format(nfm, width)+ \
        ' fn: {0: >{1}}'.format(nfr, width)

def main3():
    width = 15
    Fb = 117669030460994
    F = Fb
    while F <= Fb + 150:
        na = firstPrecedingFib(F)
        pF = fibMatrix(na)
        nF = fibMatrix(na+1)
        print '[{0: <3}]'.format(na) + \
        ' pF:{0: >{1}}'.format(pF, width) + \
        ' F :{0: >{1}}'.format(F, width) + \
        ' nF: {0: >{1}}'.format(nF, width)
        F += 1
    Fe = 190392490709135 
    F = Fe - 150 
    while F <= Fe:
        na = firstPrecedingFib(F)
        pF = fibMatrix(na)
        nF = fibMatrix(na+1)
        print '[{0: <3}]'.format(na) + \
        ' pF:{0: >{1}}'.format(pF, width) + \
        ' F :{0: >{1}}'.format(F, width) + \
        ' nF: {0: >{1}}'.format(nF, width)
        F += 1
        
def main4():
    for i in range(1, 1000000):
        idIt = 1
        sIt = fibMatrix(idIt)
        while sIt <= i:
            idIt += 1
            sIt += fibMatrix(idIt)
        
        idIt -= 1
        idFx = fibIndexFromFibSum(i)

        print (i, idIt, idFx)

def main5():
    diff = answer(143)
    print (diff)
    
def main6():
    for i in range(1, 201):
        sIt = 0
        for j in range(1,i+1):
            sIt += fibMatrix(j)
        
        sFx = sumFib(i)
        if (sIt > 1000000000): break
        print (i, sIt, sFx)

def main7():
    totGen = fastFloorLog2(143+1)
    print (totGen, pow(2,totGen))
    pow2 = [1]
    pow2sum = [1]
    
    while pow2sum[-1] <= 1000:
        pow2.append(pow2[-1]*2)
        pow2sum.append(pow2sum[-1]+pow2[-1])
        print (pow2[-1], pow2sum[-1], fastFloorLog2(pow2sum[-1]-1), log(pow2sum[-1]-1,2), fastFloorLog2(pow2sum[-1]), log(pow2sum[-1],2), fastFloorLog2(pow2sum[-1]+1), log(pow2sum[-1]+1,2))
    pow2.pop()
    pow2sum.pop()
    

    
        
if __name__ == "__main__":
    #main1()
    #main2()
    #main3()
    #main4()
    #main5()
    #main6()
    main7()


















