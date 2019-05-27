#!/usr/bin/env python
from Queue import Queue
from sys import stdout
class Node(object):
    def __init__(self, row, col):
        self.row = row
        self.col = col
    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.row == other.row and self.col == other.col
        else:
            return False
    def __str__(self):
        return "({},{})".format(self.row, self.col)

def computeDistances(T, beg, end):
    N = len(T)
    M = len(T[0])
    V = [[T[i][j] for j in range(M)] for i in range(N)]
    D = [[None for _ in range(M)] for _ in range(N)]
    D[beg.row][beg.col] = 1
    Q = Queue()
    Q.put(beg)
    V[beg.row][beg.col] = 1
    nd = beg
    while not Q.empty():
        nd = Q.get()
        if nd == end:
            break
        # Up
        if nd.row > 0 and not V[nd.row-1][nd.col]:
            D[nd.row-1][nd.col]=D[nd.row][nd.col]+1
            Q.put(Node(nd.row-1, nd.col))
            V[nd.row-1][nd.col] = 1

        # Down
        if nd.row+1 < N and not V[nd.row+1][nd.col]:
            D[nd.row+1][nd.col]=D[nd.row][nd.col]+1
            Q.put(Node(nd.row+1, nd.col))
            V[nd.row+1][nd.col] = 1

        # Left
        if nd.col > 0 and not V[nd.row][nd.col-1]:
            D[nd.row][nd.col-1]=D[nd.row][nd.col]+1
            Q.put(Node(nd.row, nd.col-1))
            V[nd.row][nd.col-1] = 1

        # Right
        if nd.col+1 < M and not V[nd.row][nd.col+1]:
            D[nd.row][nd.col+1]=D[nd.row][nd.col]+1
            Q.put(Node(nd.row, nd.col+1))
            V[nd.row][nd.col+1] = 1
    
    return D
    
def answer(T):
    N = len(T)
    M = len(T[0])
    src = Node(0,0)
    dst = Node(N-1, M-1)
    shortPosib = N+M-1
    
    Ds = computeDistances(T, src, dst)
    Dd = computeDistances(T, dst, src)
    
    if Ds[dst.row][dst.col] is not None and Dd[dst.row][dst.col] is not None:
        pathLen = Ds[dst.row][dst.col]
    else:
        pathLen = M*N+1
    
    if pathLen == shortPosib: return pathLen
    
    for row in range(N):
        for col in range(M):
            if T[row][col]==1: continue
            # Up
            if row > 1 and T[row-1][col] and T[row-2][col]==0:
                if Ds[row][col] is not None and Dd[row-2][col] is not None:
                    sdDist = Ds[row][col] + 1 + Dd[row-2][col]
                    if sdDist < pathLen: pathLen = sdDist
                if Dd[row][col] is not None and Ds[row-2][col] is not None:
                    dsDist = Dd[row][col] + 1 + Ds[row-2][col]
                    if dsDist < pathLen: pathLen = dsDist
            # Down
            if row+2 < N and T[row+1][col] and T[row+2][col]==0:
                if Ds[row][col] is not None and Dd[row+2][col] is not None:
                    sdDist = Ds[row][col] + 1 + Dd[row+2][col]
                    if sdDist < pathLen: pathLen = sdDist
                if Dd[row][col] is not None and Ds[row+2][col] is not None:
                    dsDist = Dd[row][col] + 1 + Ds[row+2][col]
                    if dsDist < pathLen: pathLen = dsDist
            # Left
            if col > 1 and T[row][col-1]and T[row][col-2]==0:
                if Ds[row][col] is not None and Dd[row][col-2] is not None:
                    sdDist = Ds[row][col] + 1 + Dd[row][col-2]
                    if sdDist < pathLen: pathLen = sdDist
                if Dd[row][col] is not None and Ds[row][col-2] is not None:
                    dsDist = Dd[row][col] + 1 + Ds[row][col-2]
                    if dsDist < pathLen: pathLen = dsDist
            # Right
            if col+2 < M and T[row][col+1] and T[row][col+2]==0:
                if Ds[row][col] is not None and Dd[row][col+2] is not None:
                    sdDist = Ds[row][col] + 1 + Dd[row][col+2]
                    if sdDist < pathLen: pathLen = sdDist
                if Dd[row][col] is not None and Ds[row][col+2] is not None:
                    dsDist = Dd[row][col] + 1 + Ds[row][col+2]
                    if dsDist < pathLen: pathLen = dsDist
                
    return pathLen
               
def main1():
    maze1 =  [[0, 1, 1, 0, 1, 0], \
              [0, 0, 1, 0, 1, 0], \
              [0, 1, 0, 0, 1, 0], \
              [0, 0, 1, 0, 1, 0], \
              [0, 1, 0, 0, 1, 0], \
              [0, 0, 0, 0, 1, 0]]
    maze2 = [[0, 1, 1, 0], [0, 0, 0, 1], [1, 1, 0, 0], [1, 1, 1, 0]]
    ans = answer(maze2)
    print (ans)
if __name__ == "__main__":
    main1()
