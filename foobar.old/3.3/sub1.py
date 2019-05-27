#!/usr/bin/env python
from sys import stdout
counter=[0]
called = [[None for _ in range(5)] for _ in range(1000)]
Pcom = []
def answer(T):
    W = int(((8*T+1)**0.5-1)/2)
    Plen = [i for i in range(W+1)]
    Plen[-1] += T-(Plen[-1]*(Plen[-1]+1))/2
    Psum = [0]*(W+1)
    for i in range(1,W+1): Psum[i] = Psum[i-1]+Plen[i]
    
    # List to store num of comb for a set size t with w partitions
    for c in range(W+1):
        Pcom.append([])
        for t in range(T+1): Pcom[c].append(None)
        
    for t in range(3,T+1): Pcom[2][t] = int((t-1)/2)
    print "T={}, W={}, len(Plen)={}, len(Psum)={}, len(Pcom)={}, len(Pcom[0])={}".format(T,W,len(Plen),len(Psum), len(Pcom), len(Pcom[0]))        
    print (Plen)
    print (Psum)
    combs = 0
    for i in range(3, W+1):
        combs += recurs(Plen, Psum)
        Psum[-2] += Plen[-1]
        Psum.pop()
        Plen[-2] += Plen[-1]
        Plen.pop()
        print (Plen)
        print (Psum)

    printLookup()
    print "\n".format()
    return combs

def printLookup():
    print "lkup:"
    for i in range(1, len(Pcom)):
        for j in range(1, len(Pcom[0])):
            stdout.write("[{},{}]{: <4} ".format(i,j,Pcom[i][j]))
        print
    print
    
def recurs(Plen, Psum):
    nParts = len(Plen)-1
    if Pcom[nParts][Psum[-1]] is None:
        Pcom[nParts][Psum[-1]] = int((Plen[-1]-Plen[-2]+1)/2)
        return Pcom[nParts][Psum[-1]]
    window = int((Plen[-1]-Plen[-2]+1)/2)
    combs = 0
    while window > 0: 
        for i in range(window):
            print(nParts, Psum[-1]+i, len(Plen))
            if Pcom[nParts][Psum[-1]+i] is None:
                Plen[-2] += 1
                Plen[-1] -= 1
                Psum[-2] += 1
                Psum[-1] -= 1
                Pcom[nParts][Psum[-1]+i] = recurs(Plen, Psum)
            combs += Pcom[nParts][Psum[-1]+i]
#    called[counter[0]] = [nParts, Plen[-1], window, len(Plen), [i for i in Plen]]
    counter[0] += 1
    return combs

    
def main1():
    #for i in range(3, 201):
    #    s = answer(i)
    #    print "ans i={}, s={}".format(i,s)
    s = answer(12)
    print "ans i={}, s={}".format(23,s)

if __name__ == "__main__":
    main1()
