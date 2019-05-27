#!/usr/bin/env python

from functools import reduce
import collections, itertools, math

class tcolors:
    HEADER    = '\033[95m'
    BLUE      = '\033[94m'
    GREEN     = '\033[92m'
    YELLOW    = '\033[93m'
    RED       = '\033[91m'
    ENDC      = '\033[0m'
    BOLD      = '\033[1m'
    UNDERLINE = '\033[4m'

def split(S, n):
    return S[:n], S[n:]
    
def answer(s):
    ans = 1
    n = len(s)
    lengths = sorted(list(set(reduce(list.__add__, ([i, n/i] for i in range(1, int(math.sqrt(n))) if n%i == 0)))), reverse=True)
    for length in lengths:
        for _ in range(length):
            pieces = split(s,length)
            print (pieces)
            if len(set(pieces)) == 1:
                ans = len(pieces)
    return ans

def genLPS(pat, lps, M):
    lps[0] = 0
    i      = 1
    l      = 0
    while i < M:
        if pat[i] == pat[l]:
            l      += 1
            lps[i]  = l
            i      += 1
            printOffset(pat[0:i], 0, tcolors.ENDC, i-l-1, tcolors.RED)
            printOffset(pat, i-l, tcolors.RED, l-1)
            print (l)
        else:
            if l != 0:
                l = lps[l-1]
            else:
                lps[i] = 0
                i += 1
                printOffset(pat[0:i], 0, tcolors.ENDC, l+i-1, tcolors.RED)
                printOffset(pat, i-l, tcolors.RED, l-1)

            
def printOffset(S, offset, color1, color1End, color2=tcolors.ENDC):
    offStr = " "*offset
    color1Str, color2Str = split(S, color1End+1)
    print offStr + color1 + color1Str + color2 + color2Str + tcolors.ENDC

pat = "ababcbabab"
M = len(pat)
lps = [0]*M
genLPS(pat, lps, M)
print (lps)
