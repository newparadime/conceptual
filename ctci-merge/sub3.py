#!/bin/python

import math
import os
import random
import re
import sys
from collections import deque
def mergeSort(V, T, l, r, swaps=deque()):
    swaps.append(0)
    if l < r:
        m = (l+r)/2
        swaps[-1] += mergeSort(V, T, l, m)
        swaps[-1] += mergeSort(V, T, m+1, r)
        swaps[-1] += merge(V, T, l, m+1, r)
    return swaps.pop()

def merge(V, T, l, m, r):
    mSwaps = 0
    i = l
    j = m
    k = l
    while i < m and j <= r:
        if V[i] <= V[j]:
            T[k] = V[i]
            i += 1
        else:
            T[k] = V[j]
            j += 1
            mSwaps += (m-i)
            #print ("swapped",m-i)
        k += 1
    
    while i < m:
        T[k] = V[i]
        k += 1
        i += 1
    
    while j <= r:
        T[k] = V[j]
        k += 1
        j += 1
    for i in xrange(l,r+1):
        V[i] = T[i]
    return mSwaps

# Complete the countInversions function below.
def countInversions(V):
    T = [None] * len(V)
    return mergeSort(V, T, 0, len(V)-1)
if __name__ == '__main__':
    fptr = sys.stdout

    t = int(raw_input())

    for t_itr in xrange(t):
        n = int(raw_input())

        arr = map(int, raw_input().rstrip().split())

        result = countInversions(arr)

        fptr.write(str(result) + '\n')

    fptr.close()

