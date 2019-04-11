#!/usr/bin/env python3

from sys import stdin

def getInput():
    [n,q] = stdin.readline().split(" ")
    Q = list()
    for line in stdin.readlines():
        Q.append(line.split(" "))
        for i in range(1,len(Q[-1])):
            Q[-1][i] = int(Q[-1][i])
    return int(n),Q

def connectedComponents(n,Q):
    G = {i:set([i]) for i in range(n+1)}
    M = [i for i in range(n+1)]
    def getBase(n):
        if M[n] not in G.keys():
            M[n] = getBase(M[n])        
        return M[n]
    for q in Q:
        if q[0] == "Q":
            a = getBase(q[1])
            print(len(G[a]))
        else:
            a = getBase(q[1])
            b = getBase(q[2])
            if a != b:
                M[b] = a
                G[a].update(G.pop(b))

if __name__ == '__main__':
    n, Q = getInput()
    connectedComponents(n,Q)

