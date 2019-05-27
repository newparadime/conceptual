#!/bin/python

import math
import os
import random
import re
import sys

def buildCountArr(C,V,d):
    for i in xrange(d):
        C[V[i]] += 1

def updateCountArr(C,V,add,rem):
    C[V[rem]] -= 1
    C[V[add]] += 1

def median2(C,d):
    mod = d%2
    d1 = d/2+mod
    d2 = d1 + 1
    i = 0
    count = C[i]
    while count < d1:
        i += 1
        count += C[i]
    v1 = i
    if mod == 0:
        while count < d2:
            i += 1
            count += C[i]
        v2 = i
    else: v2 = v1
    return v1+v2
       
def activityNotifications(E, d):
    C = [0] * 201
    buildCountArr(C,E,d)
    f = 0
    for i in xrange(d,len(E)):
        med = median2(C,d)
        if E[i] >= med: f += 1
        updateCountArr(C,E,i,i-d)
    return f

if __name__ == '__main__':
    fptr = sys.stdout
    din = open("./data", 'r')
    nd = din.readline().split()

    n = int(nd[0])

    d = int(nd[1])

    expenditure = map(int, din.readline().rstrip().split())
    din.close()
    #print (n,d)
    #print (expenditure)
    result = activityNotifications(expenditure, d)

    fptr.write(str(result) + '\n')

    fptr.close()
