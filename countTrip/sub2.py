#!/usr/bin/env python
import math
import os
import random
import re
import sys
from collections import defaultdict
from bisect import bisect_left, bisect_right
from sys import argv

def countTriplets(V, r):
    count = 0
    M = defaultdict(list)
    for i,v in enumerate(V):
#        if V[i] % r != 0: continue
        M[v].append(i)

    for i in xrange(len(V)):
        if V[i] % r != 0: continue
        first = V[i]/r
        last = V[i]*r
        print i
        print (M[first])
        numLess = bisect_left(M[first],i)
        print numLess
        print (M[last])
        numMore = len(M[last]) - bisect_right(M[last],i)
        print numMore
        print
        count += numLess * numMore
    
    return count
    
if __name__ == '__main__':
    fptr = open(argv[1], 'r')

    nr = fptr.readline().split()

    n = int(nr[0])

    r = int(nr[1])
    
    arr = map(long, fptr.readline().rstrip().split())

    fptr.close()

    ans = countTriplets(arr, r)

    print ans

