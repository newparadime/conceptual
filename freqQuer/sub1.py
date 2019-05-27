#!/bin/python

import math
import os
import random
import re
import sys

# Complete the freqQuery function below.
def freqQuery(Q):
    D = dict()
    F = dict()
    R = list()
    for q in Q:
        cmd, val = q[0], q[1]
        if (cmd == 1):
            if val in D:
                F[D[val]] -= 1
                if F[D[val]] == 0: del F[D[val]]
                D[val] += 1
            else:
                D[val] = 1
                F[1] += 1
            if D[val] in F: F[D[val]] += 1
            else: F[D[val]] = 1
        elif (cmd == 2):
            if val in D:
                F[D[val]] -= 1
                if F[D[val]] == 0: del F[D[val]]
                D[val] -= 1
                if D[val] == 0:
                    del D[val]
                else:
                    if D[val] in F: F[D[val]] += 1
                    else: F[D[val]] = 1
        elif (cmd == 3):
            if val in F: R.append(1)
            else: R.append(0)
                
    return R
if __name__ == '__main__':
    fptr = sys.stdout

    q = int(raw_input().strip())

    queries = []

    for _ in xrange(q):
        queries.append(map(int, raw_input().rstrip().split()))

    ans = freqQuery(queries)

    fptr.write('\n'.join(map(str, ans)))
    fptr.write('\n')

    fptr.close()
