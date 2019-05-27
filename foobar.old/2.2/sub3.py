#!/usr/bin/env python
from math import log, floor, sqrt

def answer(tLambs):
    if tLambs <= 3:
        return 0
    
    totGen = int(floor(log(tLambs+1, 2)))
    genPayouts = [pow(2,totGen-2), pow(2,totGen-1)]
    genTotPay = pow(2,totGen)-1
    
    genRem = tLambs - genTotPay
    if check3(genPayouts, genRem) and check3(genPayouts, genRem):
        totGen += 1
    
    fib = [1,1]
    fibSum = [1,2]
    
    while fibSum[-1] <= tLambs:
        fib.append(fib[-1]+fib[-2])
        fibSum.append(fibSum[-1]+fib[-1])
    fib.pop()
    fibSum.pop()
    
#    for i,val in enumerate(fibSum): print (i,fib[i],val)
    
    stRem = tLambs - fibSum[-1]
    totSt = len(fibSum)
    
    if check2(fib, stRem) and check3(fib, stRem):
        totSt += 1
    
    return totSt - totGen
    
def check2(payouts, remLamb):
    if remLamb > (payouts[-1] * 2):
        return False
    return True

def check3(payouts, remLamb):
    if (payouts[-2] + payouts[-1]) > remLamb:
        return False
    return True
    

    
def check2(payouts, remLamb):
    if remLamb > (payouts[-1] * 2):
        return False
    return True

def check3(payouts, remLamb):
    if (payouts[-2] + payouts[-1]) > remLamb:
        return False
    return True
    
def main1():
    ans = answer(143)
    print(ans)
        
if __name__ == "__main__":
    main1()
    #main2()
    #main3()
    #main4()
    #main5()
    #main6()

