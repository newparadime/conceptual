#!/bin/python

import math
import os
import random
import re
import sys
swaps = 0
def mergeSort(V,l,r):
    if l < r:
        m = (l+r)/2
        mergeSort(V, l, m)
        mergeSort(V, m+1, r)
        merge(V, l, m, r)
    #return swaps

def merge(V, l, m ,r):
    global swaps
    #swaps = 0
    ll = m-l+1
    lr = r-m
    L = [V[l+i] for i in xrange(ll)]
    R = [V[m+1+j] for j in xrange(lr)]
    i = 0
    j = 0
    k = l
    while i < ll and j < lr:
        if L[i] <= R[j]:
            V[k] = L[i]
            i += 1
        else:
            V[k] = R[j]
            j += 1
            swaps += 1
        k += 1
    
    while i < ll:
        V[k] = L[i]
        k += 1
        i += 1
    
    while j < lr:
        V[k] = R[j]
        k += 1
        j += 1

# Complete the countInversions function below.
def countInversions(V):
    mergeSort(V,0,len(V)-1)
    return swaps
if __name__ == '__main__':
    fptr = sys.stdout

    t = int(raw_input())

    for t_itr in xrange(t):
        n = int(raw_input())

        arr = map(int, raw_input().rstrip().split())

        result = countInversions(arr)

        fptr.write(str(result) + '\n')

    fptr.close()
