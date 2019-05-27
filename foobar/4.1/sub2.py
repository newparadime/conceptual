#!/usr/bin/env python

from fractions import gcd

def getDistance(pos1, pos2):
    return (abs(pos1[0]-pos2[0])**2 + abs(pos1[1]-pos2[1])**2)**0.5

def checkIntersection(src, tgt, chk):
    dx = src[0]-tgt[0]
    dxChk = src[0]-chk[0]
    dy = src[1]-tgt[1]
    dyChk = src[1]-chk[1]
    if (dx < 0 and dxChk >= 0) or (dx >= 0 and dxChk < 0):
        return False
    if abs(dx) < abs(dxChk):
        return False
    if (dy < 0 and dyChk >= 0) or (dy >= 0 and dyChk < 0):
        return False
    if abs(dy) < abs(dyChk):
        return False
    m = float(dy)/dx
    b = src[1]-(m*src[0])
    return bool(chk[1] == (m*chk[0])+b)

def getReflections(src, tgt, dims, dist):
    R = set()
    if tgt[0] > 0:
        reflection = (tgt[0]*-1, tgt[1])
        if getDistance(src, reflection) <= dist:
            R.add(reflection)
    if tgt[1] > 0:
        reflection = (tgt[0], tgt[1]*-1)
        if getDistance(src, reflection) <= dist:
            R.add(reflection)
    if tgt[0] < dims[0]:
        reflection = (abs(tgt[0]-dims[0])+dims[0], tgt[1])
        if getDistance(src, reflection) <= dist:
            R.add(reflection)
    if tgt[1] < dims[1]:
        reflection = (tgt[0], abs(tgt[1]-dims[1])+dims[1])
        if getDistance(src, reflection) <= dist:
            R.add(reflection)
    return R

def ppToVector(p1, p2):
    x = p1[0] - p2[0]
    y = p1[1] - p2[1]
    div = abs(gcd(x, y))
    return tuple([x/div, y/div])

def answer(dims, src, tgt, dist):
    src_reflections  = set()
    last_reflections  = set()
    last_reflections.add(tuple(src))
    while(len(last_reflections) > 0):
        new_reflections = set()
        for elem in last_reflections:
            new_reflections |= getReflections(src, elem, dims, dist)
        src_reflections |= new_reflections
        last_reflections = new_reflections
        
        
    tgt_reflections  = set()
    tgt_reflections.add(tuple(tgt))
    last_reflections  = set()
    last_reflections.add(tuple(tgt))
    while(len(last_reflections) > 0):
        new_reflections = set()
        for elem in last_reflections:
            new_reflections |= getReflections(src, elem, dims, dist)
        tgt_reflections |= new_reflections
        last_reflections = new_reflections
   
    vectors = set()
    for t in tgt_reflections:
        intersects = False
        for s in src_reflections:
            if checkIntersection(src, t, s):
                intersects = True
                break
        if not intersects:
            vector = ppToVector(src, t)
            vectors.add(vector)
    return len(vectors)
        
def main1():
    ans = answer([3,2], [1,1], [2,1], 4)
    print ans
    
def main2():
    ans = answer([300,275], [150,150], [185,100], 1)
    print ans
if __name__ == "__main__":
    main2()
