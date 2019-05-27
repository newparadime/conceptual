#!/usr/bin/env python
from sys import stdout
counter=[0]
called = [[None for _ in range(5)] for _ in range(1000)]
combs = [[]]
sums = [0]
def answer(T):
    maxHeight = T-2
    # List to store num of comb for a staircase with t total bricks and with t' height steps
    for _ in range(maxHeight+1):
        combs.append([])
        for __ in range(T+1):
            combs[-1].append(None)
    minHeight = int((8*T+1)**0.5-1)/2
    for i in range(1,minHeight+1):
        sums.append(sums[-1]+i)

    comb = 0
    for i in range(1,maxHeight+1):
        comb += recurs(i)

    return comb

def recurs(bricks):
    height = 0
    rCombs = 0
    i = 1
    while i < bricks:
        height += i
        bricks -= i
        rCombs += i
        rCombs += recurs(bricks)
    return rCombs


def printLookup():
    print "lkup:"
    for i in range(1, len(Pcom)):
        for j in range(1, len(Pcom[0])):
            stdout.write("[{},{}]{: <4} ".format(i,j,Pcom[i][j]))
        print
    print
    

    
def main1():
    #for i in range(3, 201):
    #    s = answer(i)
    #    print "ans i={}, s={}".format(i,s)
    s = answer(12)
    print "ans i={}, s={}".format(12,s)

if __name__ == "__main__":
    main1()
