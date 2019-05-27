#!/usr/bin/env python
from sys import stdout
combs = {}

def _yieldParts(num,lt):
    if not num:
        yield ()
    for i in range(min(num,lt),0,-1):
        for parts in _yieldParts(num-i,i):
            yield (i,)+parts

def yieldParts(num):
    if num not in combs:
        combs[num] = {}
    for part in _yieldParts(num,num):
        if len(part) not in combs[num]:
            combs[num][len(part)] = 0
        combs[num][len(part)] += 1
        yield part
   
def main1():
    for n in range(3, 20):
        print "------------\nn={}\n------------\n".format(n)
        for parts in yieldParts(n):
            for part in parts:
                stdout.write( "{}".format(part))
            print ""
    #s = answer(12)
    #print "ans i={}, s={}".format(12,s)

if __name__ == "__main__":
    main1()
