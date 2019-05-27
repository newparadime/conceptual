#!/usr/bin/env python
pip install tinytree
import tinytree
from fractions import gcd as bltin_gcd

def coprime2(a, b):
    return bltin_gcd(a, b) == 1

def answer(M, F):
    F = int(F)
    M = int(M)
    if F > M:
        F, M = M, F
    i = 0
    while (F > 1):
        M -= F
        if F > M:
            F, M = M, F
        i += 1
    if F == 1: return i+M-1
    else: return "impossible"

def genSeq(M, F):
    bM = bool(True)
    while (M[-1] > 1 or F[-1] > 1) and not (M[-1] < 1 or F[-1] < 1):
        if M[-1] > F[-1]:
            M.append(M[-1] - F[-1])
            F.append(F[-1])
        else:
            F.append(F[-1] - M[-1])
            M.append(M[-1])
    return M, F
    
def answer2(M, F):
    print "ans2[{},{}]:".format(M,F)
    gen = 0
    if F > M:
        M, F = F, M
    while F > 1:
        imf = int(M/F)
        gen += imf
        M, F = F, M-(imf*F)
        print "  [{},{}]".format(M,F)
    print("  fin[{},{}]".format(M,F))
    if F == 1:
        return gen + M-1
    else:
        return -1
    
def main1():
    ans  = answer (4,7)
    ans2 = answer2(4,7)
    print (ans, ans2)
    ans  = answer (22,7)
    ans2 = answer2(22,7)
    print (ans, ans2)
    ans  = answer (23,7)
    ans2 = answer2(23,7)
    print (ans, ans2)
    ans  = answer (19,7)
    ans2 = answer2(19,7)
    print (ans, ans2)

def main2():
    ans = answer2(4,7)
    print(ans)
    F = [4]
    M = [7]
    M, F = genSeq(M, F)
    print (M)
    print (F)
    print (len(M)-1)
    M = pow(10,10)
    F = M-1
    print (M)
    print (F)
    print (coprime2(M,F))
    ans  = answer (M,F)
    ans2 = answer2(M,F)
    print (ans, ans2)
    
if __name__ == "__main__":
    #main1()
    main2()
