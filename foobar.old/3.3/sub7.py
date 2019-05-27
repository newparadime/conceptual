#!/usr/bin/env python
from sys import stdout
from math import sqrt

pi = 3.14159265358979323846
e  = 2.71828182845904523536
facts = {}
lkupP = [[]]
def answer(n):
    for i in range(0,n+1):
        lkupP.append([])
        for _ in range(0,n+1):
            lkupP[i].append(None)
    k = 2
    combs = 0
    while cSum(k) <= n:
        combs += Q(n, k)
        k += 1
    return combs
    
def Q(n, k):
    n -= nChoose2(k)
    return P(n,k)

def P(n, k):    
    if k > n or k == 0: return 0
    if k == n        : return 1

    if lkupP[n][k] is None:
        lkupP[n][k] = P(n-1, k-1) + P(n-k,k) 
    return lkupP[n][k]

def nChoose2(n):
    return fact(n) / (2*fact(n-2))

def cSum(n):
    return int((n*(n+1))/2)

def fact(n):
    if n == 0:
        return 1
    if n not in facts:
        facts[n] = int(n * fact(n-1))
    return int(facts[n])

def main1():
    for i in range(3, 200):
        s = answer(i)
        print "ans i={}, s={}".format(i,s)
def main2():
    s = answer(12)
    print "ans i={}, s={}".format(12,s)

if __name__ == "__main__":
    main1()
    #main2()
