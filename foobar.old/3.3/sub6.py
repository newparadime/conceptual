#!/usr/bin/env python
from sys import stdout
combs = [int(0)]
from math import ceil
from collections import deque
def answer(totalBricks):
    maxHeight = totalBricks-1
    # List to store num of comb for a staircase with t total bricks and with t' height steps
    for i in range(maxHeight+1):
        combs.append([])
        for j in range(totalBricks+1):
            combs[i].append(None)
    
    minHeight = calcMinHeight(totalBricks)
    
    for i in range(1,minHeight+1):
        sums.append(sums[-1]+i)

    #comb = 0
    #height = 1
    #while height < totalBricks - calcMinHeight(height):
        #print "called from main"
        #comb += 1 + recurs(totalBricks-height, height,0)
        #height += 1
    tbd = deque([totalBricks])
    mxd = deque([maxHeight])
    
    comb = recurs(tbd,mxd,0)
    printLookup(combs)
    return comb

def recurs(tbd, mxd,indent):
    print ("{: #x}".format(id(combs)))
    indnt = "  "*indent
    stdout.write("[{: 3}]{}totBricks={}, maxH={}\n".format(indent,indnt,tbd[-1],mxd[-1]))
    if tbd[-1] < 0:
        return 0

    rComb = 0
    tbd.append(tbd[-1]-mxd[-1]-1)
    mxd.append(mxd[-1] - 1)
    #if combs[height][totalBricks-height] is None:
    #    combs[height][totalBricks-height] = recurs(totalBricks-height, height,indent+1)
    #thisComb = combs[height][totalBricks-height]
    
    while mxd[-1] > 0:
        if combs[mxd[-1]][tbd[-1]] is None:
            combs[mxd[-1]][tbd[-1]] = recurs(tbd, mxd,indent+1)
        rComb += combs[mxd[-1]][tbd[-1]]
        mxd[-1] -= 1
        tbd[-1] += 1
    mxd.pop()
    tbd.pop()
    return 1 + rComb

def calcMinHeight(totalBricks):
    
    ccsum = invConsecSum(totalBricks)
    return int(ceil((totalBricks-consecSum(ccsum)+1)/2) + ccsum)

def invConsecSum(setSum):
    return int(((8*setSum+1)**0.5-1)/2)

def consecSum(n):
    return int((n*(n+1))/2)

def printLookup(lkup):
    print "lkup:"
    for i in range(0, len(lkup)-1):
        for j in range(0, len(lkup[i])-1):
            stdout.write("[{},{}]{: <4} ".format(i,j,lkup[i][j]))
        stdout.write("\n")
    stdout.write("\n")
    

    
def main1():
    #for i in range(3, 20):
    #    s = answer(i)
    #    print "ans i={}, s={}".format(i,s)
    s = answer(12)
    print "ans i={}, s={}".format(12,s)

if __name__ == "__main__":
    main1()
