#!/usr/bin/env python

#import collections, itertools, math

def repeatingSubstr(S):
    L = [0]*len(S)
    N = len(S)
    l = 0
    i = 1
    while i < N:
        print(L)
        if S[i] == S[l]:
            l += 1
            L[i] = l
            i += 1
        elif l != 0:
            l = L[l-1]
        else:
            L[i] = 0
            i += 1
            
    print(L)
    fragLen = len(S) - L[-1]
    if len(S) % fragLen != 0:
        return S

    return S[0:fragLen]
    
S = "helloheelohello"

l = pattern(S)

print(l)
