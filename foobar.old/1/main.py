#!/usr/bin/env python
def answer(S):
    LPS = genLPS(S)
    fragLen = len(S) - LPS[-1]
    if len(S) % fragLen != 0:
        return 1
    else:
        return len(S) / fragLen

def genLPS(S):
    L = [0]*len(S)
    N = len(S)
    l = 0
    i = 1
    while i < N:
        if S[i] == S[l]:
            l += 1
            L[i] = l
            i += 1
        elif l != 0:
            l = L[l-1]
        else:
            L[i] = 0
            i += 1
    return L

S = "hellohellohello"

l = answer(S)

print(l)
