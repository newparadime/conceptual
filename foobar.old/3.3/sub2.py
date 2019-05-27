#!/usr/bin/env python
from sys import stdout
counter=[0]
called = [[None for _ in range(5)] for _ in range(1000)]
Pcom = []
def answer(setSum):
    nParts = int((8*setSum+1)**0.5-1)/2
    print(nParts)
    for c in range(nParts+1):
        Pcom.append([])
        for t in range(setSum+1): Pcom[c].append(None)
        
    for t in range(3,setSum+1): Pcom[2][t] = int((t-1)/2)
        
    
    #printLookup()
    
    combs = 0
    for i in range(2, nParts+1):
        thisCombs, setOffset = recurs(setSum, i)
        print ("thisC",thisCombs)
        combs += thisCombs
    printLookup()
    print "\n".format()
    return combs

def recurs(setSum, nParts, setOffset=0):
    lastPart = calcLastPartSize(setSum, nParts)
    window = calcWindow(lastPart,nParts-1)
    print(nParts, setSum, lastPart, window, setOffset)
    if Pcom[nParts][setSum] is None:
        currCombs = 0
        while window > 0:
            for i in range(window+1):
                thisCombs, setOffset = recurs(setSum-lastPart, nParts-1, setOffset)
                currCombs += thisCombs
                lastPart -= 1
            window = calcWindow(lastPart, (nParts-1)+setOffset-1)
            
            #called[counter[0]] = [nParts, Plen[-1], window, len(Plen), [i for i in Plen]]
            #counter[0] += 1
        #print (nParts, len(Pcom), Psum[-1], len(Pcom[0]))
        Pcom[nParts][setSum] = currCombs
    if nParts == 2:
        setOffset += window-1
    return Pcom[nParts][setSum], setOffset

def calcLastPartSize(setSum, nParts):
    return nParts + (setSum-consecSum(nParts))

def calcWindow(currPart, prevPart):
    return int((currPart-prevPart+1)/2)

def printLookup():
    print "lkup:"
    for i in range(1, len(Pcom)):
        for j in range(1, len(Pcom[0])):
            stdout.write("[{},{}]{: <4} ".format(i,j,Pcom[i][j]))
        print
    print

def genLists(T):
    Psum = [0]
    Plen = [0]
    i = 1
    while Psum[-1] < T:
        Plen.append(i)
        Psum.append(Psum[i-1] + Plen[i])
        i += 1
    Psum = Psum[:-1]
    Plen = Plen[:-1]
    Plen[-1] += T-Psum[-1]
    Psum[-1]  = Psum[-2]+Plen[-1]
    return Plen, Psum

def consecSum(n):
    return int((n*(n+1))/2)

def main1():
    #for i in range(3, 201):
    #    s = answer(i)
    #    print "ans i={}, s={}".format(i,s)
    s = answer(12)
    print "ans i={}, s={}".format(200,s)

def main2():
    W=1000
    Plen = [i for i in range(W+1)]
    Psum = [0]*(W+1)
    for i in range(1,W+1): Psum[i] = Psum[i-1]+Plen[i]
    for i in range(W):
        T1 = Psum[i]+1
        W1 = int(((8*T1+1)**0.5-1)/2)
        T2 = Psum[i+1]-1
        W2 = int(((8*T2+1)**0.5-1)/2)
        if W1 != i or W2 != i:
            print "i={}, Plen={}, Psum[i,i+1]={},{} W1={}, W2={}".format(i, Plen[i], Psum[i], Psum[i+1], W1, W2)
if __name__ == "__main__":
    main1()
    #main2()
