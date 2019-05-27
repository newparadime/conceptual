#!/usr/bin/env python
def answer(M, F):
    gen = 0
    if F > M:
        M, F = F, M
    while F > 1:
        imf = int(M/F)
        gen += imf
        M, F = F, M-(imf*F)
    if F == 1:
        return gen + M-1
    else:
        return -1
    
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
    

def main1():
    ans  = answer (4,7)
    ans  = answer (22,7)
    ans  = answer (23,7)

def main2():
    ans = answer(4,7)
    print(ans)
    F = [4]
    M = [7]
    M, F = genSeq(M, F)
    print (M)
    print (F)
    print (len(M)-1)
    
    
    
    
    
if __name__ == "__main__":
    main1()
