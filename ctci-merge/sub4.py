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
        i = l
        j = m+1
        while i < r and V[i] <= V[i+1]: i += 1
        if i < m:
            swaps += mergeSort(V, l, m)
            while j < r and V[j] <= V[j+1]: j += 1
        if i < r and j < r: swaps += mergeSort(V, m+1, r)
        if i < r: swaps += merge(V, l, m+1, r)
    return swaps

def merge(V, l, m, r):
    mSwaps = 0
    i = l
    j = m
    T = dict()
    k = l
    print "l={},m={},r={}".format(l,m,r)
    while i < m and j <= r:
        if V[i] <= V[j]:
            T[k] = V[i]
            i += 1
        else:
            T[k] = V[j]
            j += 1
            mSwaps += (m-i)
        k += 1
    ii = 0
    print(V)
    print(T)
    while ii < m-i:
        V[r-ii-(r-j+1)] = V[m-ii-1]
        ii += 1
    V.update(T)
    print(V)
    print(T)
    return mSwaps

# Complete the countInversions function below.
def countInversions(L):
    V = dict(enumerate(L))
    return mergeSort(V, 0, len(L)-1)
if __name__ == '__main__':
    arr = [2,1,3,1,2]
    result = countInversions(arr)
    fptr = sys.stdout
    fptr.write(str(result) + '\n')
    fptr.close()
