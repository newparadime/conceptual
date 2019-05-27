#!/bin/python

import math
import os
import random
import re
import sys
from math import ceil,floor
# Complete the minimumPasses function below.
def minimumPasses(m, w, p, n):
    t = 1
    et = n//(m*w)
    if n-(et*m*w) > 0: et+=1
    prevT = et
    if m > w: m,w=w,m
    C = m*w
    while C < n:
        #print (t,C,m,w)
        #z = raw_input()
        if C+m*w >= n: return int(t+1)
        if C < p:
            cpn = p - C
            et = cpn//(m*w)
            if cpn-(et*m*w) > 0: et+=1
            #print et
            t += et
            C += et*m*w
            #continue
        ad = C//p
        C -= ad*p
        e = min(w-m,ad)
        m += e
        ad -= e
        ad2 = ad//2
        m += ad2
        w += ad2
        ad -= ad2*2
        w += ad
        C += (m*w)
        t += 1
        cnn = n - C
        et = cnn//(m*w)
        if cnn-(et*m*w) > 0: et+=1
        if t+et > prevT: return prevT
        prevT = t+et
    return int(t)
            
if __name__ == '__main__':
    fptr = sys.stdout

    mwpn = raw_input().split()

    m = int(mwpn[0])

    w = int(mwpn[1])

    p = int(mwpn[2])

    n = int(mwpn[3])

    result = minimumPasses(m, w, p, n)

    fptr.write(str(result) + '\n')

    fptr.close()
