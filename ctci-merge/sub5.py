#!/bin/python

import math
import os
import random
import re
import sys
from collections import deque
def mergeSort(V, l, r, swaps=deque()):
    swaps = 0
    if l < r:
        m = (l+r)/2
        swaps += mergeSort(V, l, m)
        swaps += mergeSort(V, m+1, r)
        swaps += merge(V, l, m+1, r)
    return swaps

def merge(V, l, m, r):
    mSwaps = 0
    i = l
    j = m
    T = dict()
    k = l
    #print "l={},m={},r={}".format(l,m,r)
    while i < m and j <= r:
        if V[i] <= V[j]:
            T[k] = V[i]
            i += 1
        else:
            T[k] = V[j]
            j += 1
            mSwaps += (m-i)
        k += 1
    #print(V)
    #print(T)
    ii = m-1
    #r - m+1 - ii - (r-j+1)
    x=j-m
    #x=j-1-i
    #print "ii={},i={},j={},m={},x={}".format(ii,i,j,m,x)
    while ii >= i:
        V[ii+x] = V[ii]
        ii -= 1
    V.update(T)
    #print(V)
    #print(T)
    return mSwaps

# Complete the countInversions function below.
def countInversions(L):
    V = dict(enumerate(L))
    return mergeSort(V, 0, len(L)-1)
if __name__ == '__main__':
    fptr = sys.stdout

    t = int(raw_input())

    for t_itr in xrange(t):
        n = int(raw_input())

        arr = map(int, raw_input().rstrip().split())

        result = countInversions(arr)

        fptr.write(str(result) + '\n')
