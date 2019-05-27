#!/usr/bin/env python
from string import ascii_lowercase

A = [4,3,6,9,3,1,8,7,11,21,1,2,1,1,2,3]
B = [5,6,7,8]
T = {c:list([0]*len(B)) for c in ascii_lowercase}
for k in T.iterkeys():
    print(k,len(T[k]),len(T))
import heapq
C = A[:]
heapq.heapify(C)
print (A[0],C[0])
print (A[-1],C[-1])
print (A)
print (C)
print heapq.nlargest(1,C)

AA = ""
AA = AA + 'b'*2
print AA
