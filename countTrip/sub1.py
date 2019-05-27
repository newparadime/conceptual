#!/usr/bin/env python

import math
import os
import random
import re
import sys
from collections import Counter
from sys import argv
def countTriplets(V, r):
    count = 0
    C = Counter(V)
    for k,v in C.iteritems():
        count += C[k] * C[k*r] * C[k*r*r]
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

