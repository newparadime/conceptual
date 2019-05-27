#!/usr/bin/env python

from fractions import gcd

def getDistance(pos1, pos2):
    return float(abs(pos1[0]-pos2[0])**2 + abs(pos1[1]-pos2[1])**2)**0.5

def ppToVector(p1, p2):
    x = p1[0] - p2[0]
    y = p1[1] - p2[1]
    div = gcd(abs(x),abs(y))
    return tuple([int(x/div), int(y/div)])

def generateVectors(src, reflections):
    lkup = dict()
    for reflection in reflections:
        dist = getDistance(src, reflection)
        vector = ppToVector(src, reflection)
        if vector not in lkup or lkup[vector] > dist:
            lkup[vector] = dist
    return lkup

def getReflections(src, tgt, dims, maxDist):
    R = set()
    if tgt[0] > 0:
        reflection = (tgt[0]*-1, tgt[1])
        dist = getDistance(src, reflection)
        if dist <= maxDist:
            R.add(reflection)
    if tgt[1] > 0:
        reflection = (tgt[0], tgt[1]*-1)
        dist = getDistance(src, reflection)
        if dist <= maxDist:
            R.add(reflection)
    if tgt[0] < dims[0]:
        reflection = (abs(tgt[0]-dims[0])+dims[0], tgt[1])
        dist = getDistance(src, reflection)
        if dist <= maxDist:
            R.add(reflection)
    if tgt[1] < dims[1]:
        reflection = (tgt[0], abs(tgt[1]-dims[1])+dims[1])
        dist = getDistance(src, reflection)
        if dist <= maxDist:
            R.add(reflection)
    return R


def answer(dims, src, tgt, dist):
    src_reflections  = set()
    
    src_reflection = tuple([0,0])
    src_reflections.add(src_reflection)

    src_reflection = tuple([0,dims[1]])
    src_reflections.add(src_reflection)
        
    src_reflection = tuple([dims[0],0])
    src_reflections.add(src_reflection)
        
    src_reflection = tuple([dims[0], dims[1]])
    src_reflections.add(src_reflection)
        
    last_reflections  = set()
    last_reflections.add(tuple(src))
    last_reflections |= src_reflections
    while(len(last_reflections) > 0):
        new_reflections = set()
        for elem in last_reflections:
            new_reflections |= getReflections(src, elem, dims, dist)
        src_reflections |= new_reflections
        last_reflections = new_reflections
        
        
    tgt_reflections  = set()
    tgt_reflections.add(tuple(tgt))
    last_reflections = set()
    last_reflections |= tgt_reflections
    while(len(last_reflections) > 0):
        new_reflections = set()
        for elem in last_reflections:
            new_reflections |= getReflections(src, elem, dims, dist)
        tgt_reflections |= new_reflections
        last_reflections = new_reflections

    src_vectors = generateVectors(src, src_reflections)
    #print (src_reflections)
    #print
    #print (src_vectors)
    tgt_vectors = generateVectors(src, tgt_reflections)
    
    nShots = 0
    for key in tgt_vectors.keys():
        if key not in src_vectors or src_vectors[key] > tgt_vectors[key]:
            nShots += 1
    return nShots
        
def main1():
    ans = answer([2,5], [1,2], [1,4], 11)
    print ans
    
def main2():
    ans = answer([300,275], [150,150], [185,100], 500)
    print ans
    
def main3():
    ans = answer([10,10], [4,4], [3,3],5000)
    print ans
    
def main4():
    ans = answer([23,10], [6, 4], [3,2], 23)
    print ans
    
def main5():
    ans = answer([42,59], [34, 44], [6,34], 5000)
    print ans
    
if __name__ == "__main__":
    main1()
