#!/bin/python

import math
import os
import random
import re
import sys
from string import ascii_lowercase
from collections import defaultdict,deque
# Complete the abbreviation function below.
def islower(c):
    if ord('a') <= ord(c) <= ord('z'): return True
    return False

def isupper(c):
    if ord('A') <= ord(c) <= ord('Z'): return True
    return False

def toupper(c):
    if isupper(c): return c
    return chr(ord('A')+ord(c)-ord('a'))

def tolower(c):
    if islower(c): return c
    return chr(ord('a')+ord(c)-ord('A'))



def abbreviation(a, b):
    #print "entered"
    if len(b) > len(a): return "NO"
    A = list(a)
    B = list(b)
#    S = defaultdict(list)
#    T = defaultdict(list)
#    m = len(B)
#    n = len(A)
#    for i in xrange(m):
#        S[A[i]].append(i)
#        T[B[i]].append(i)
#    for i in xrange(m,n):
#        S[A[i]].append(i)
    return __abbreviation(A,B)

def __abbreviation(A, B):
    while A and B:
        if A[-1] == B[-1]:
#            S[A[-1]].pop()
            A.pop()
#            T[B[-1]].pop()
            B.pop()
        elif toupper(A[-1]) == B[-1]:
            tu = toupper(A[-1])
#            S[A[-1]].pop()
            A.pop()
            res1 = __abbreviation(A ,B)
            if res1 == "YES": return "YES"
#            T[B[-1]].pop()
            if B:
                B.pop()
                res2 = __abbreviation(A,B)
                return res2
            else: return "NO"
        elif islower(A[-1]):
#            S[A[-1]].pop()
            A.pop()
        else:
            return "NO"
               
    if A and B and A != B: return "NO"
    if A and not B:
        if set(A).issubset(ascii_lowercase): return "YES"
        else: return "NO"
    if B and not A: return "NO"#+a+" "+b
    return "YES"
        
if __name__ == '__main__':
    fptr = sys.stdout
    fin = open(sys.argv[1], "r")
    q = int(fin.readline())

    for q_itr in xrange(q):
        a = fin.readline()

        b = fin.readline()

        result = abbreviation(a, b)

        fptr.write(result + '\n')

    fptr.close()
    fin.close()
