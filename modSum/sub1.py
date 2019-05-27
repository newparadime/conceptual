#!/bin/python

import math
import os
import random
import re
import sys
from collections import defaultdict
from heapq import *
from bisect import bisect
# Complete the maximumSum function below.



def maximumSum(A, m):
    prev = 0
    P = [0] * len(A)
    M = defaultdict(int)
    for i in xrange(len(A)):
        P[i] = (prev+(A[i]%m))%m
        M[P[i]] = max(M[P[i]],i)
        prev = P[i]
    maxSum = P[0]
    K = [i for i in sorted(M.iterkeys())]
    print P[0]
    for i in xrange(len(A)):
        minGreater = 0
        j = bisect(K,P[i])
        if j < len(K) and M[K[j]] > i:
            ii = M[K[j]]
            minGreater = P[ii]
            print (j,len(K),ii,minGreater)
        thisSum = (P[i] - minGreater + m)%m
        print ("Pi",P[i])
        maxSum = max(thisSum, maxSum)
        if maxSum == m - 1: return maxSum
    return maxSum
if __name__ == '__main__':
    fptr = sys.stdout
    fin = open(sys.argv[1], "r")
    q = int(fin.readline())

    for q_itr in xrange(q):
        nm = fin.readline().split()

        n = int(nm[0])

        m = int(nm[1])

        a = map(long, fin.readline().rstrip().split())

        result = maximumSum(a, m)

        print q_itr
        fptr.write(str(result) + '\n')
    fin.close()
    fptr.close()

