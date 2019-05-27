#!/usr/bin/env python
from sys import stdout
combs = [[int(0)]]
sums = [0]
from math import floor
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

    comb = 0
    height = 1
    while height < totalBricks - height:
        #print "called from main"
        comb += 1 + recurs(totalBricks-i, i,0)
    printLookup(combs)
    return comb

def recurs(totalBricks, maxHeight,indent):
    ##print ("{: #x}".format(id(combs)))
    indnt = "  "*indent
    #stdout.write("[{: 3}]{}totBricks={}, maxH={}\n".format(indent,indnt,totalBricks,maxHeight))
    if totalBricks > maxHeight:
        return 0
    if totalBricks == 3:
        return 2
    if totalBricks < 3:
        return 1
    if totalBricks > consecSum(maxHeight):
        #print "out of range"
        return 0
    minHeight = calcMinHeight(totalBricks)
    rComb = 0
    for i in range(minHeight, maxHeight):
        if combs[i][totalBricks-i] is None:
            combs[i][totalBricks-i] = recurs(totalBricks-i, i,indent+1)
        rComb += combs[i][totalBricks-i]
        #rComb += recurs(totalBricks-i, i)
    return rComb

def calcMinHeight(totalBricks):
    ccsum = invConsecSum(totalBricks)
    return int(floor((totalBricks-consecSum(ccsum)+1)/2) + ccsum)

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
    for i in range(3, 20):
        s = answer(i)
        print "ans i={}, s={}".format(i,s)
    #s = answer(12)
    #print "ans i={}, s={}".format(12,s)

if __name__ == "__main__":
    main1()
