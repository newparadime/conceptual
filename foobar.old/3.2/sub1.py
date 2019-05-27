#!/usr/bin/env python
from Queue import Queue
from sys import stdout
class Node(object):
    def __init__(self, row, col, dsrc=None, ddst=None):
        self.row = row
        self.col = col
        self.dsrc = dsrc
        self.ddst = ddst
    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.row == other.row and self.col == other.col
        else:
            return False
    def __str__(self):
        return "({},{}): s={: <4} d={: <4}".format(self.row, self.col, self.dsrc, self.ddst)
def printMatrix(M):
    for row in M:
        for cell in row:
            stdout.write("{} ".format(cell))
        stdout.write('\n')

def answer(T):
    N = len(T)
    M = len(T[0])
    def pathIndex(i, j):
        print (N, M, i, j, i*N+j)
        return i*M+j
    def invPathIndex(ind):
        return ind/M, ind%M
#    def printPath(P):
#        p = pathIndex(dst.row, dst.col)
#        while p is not None:
#            i, j = invPathIndex(p)
#            stdout.write('({},{}) '.format(i,j))
#            p = P[p]
#        stdout.write('\n')
                
    P = [None for _ in range(N*M)]
    src = Node(0,0,0)
    dst = Node(N-1, M-1)
    shortPosib = N+M-1
    V = [[T[i][j] for j in range(M)] for i in range(N)]
    dummy = Node(0,0)
    D = [[dummy for _ in range(M)] for _ in range(N)]
    D[0][0] = src
    Q = Queue()
    Q.put(D[0][0])
    V[src.row][src.col] = 2
    nd = src
    while not Q.empty():
        nd = Q.get()
        if nd == dst:
            break
        # Up
        if nd.row > 0 and not V[nd.row-1][nd.col]:
            D[nd.row-1][nd.col]=Node(nd.row-1, nd.col, nd.dsrc+1)
            P[pathIndex(nd.row-1,nd.col)] = pathIndex(nd.row,nd.col)
            Q.put(D[nd.row-1][nd.col])
            V[nd.row-1][nd.col] = 2

        # Down
        if nd.row+1 < N and not V[nd.row+1][nd.col]:
            D[nd.row+1][nd.col]=Node(nd.row+1, nd.col, nd.dsrc+1)
            P[pathIndex(nd.row+1,nd.col)] = pathIndex(nd.row,nd.col)
            Q.put(D[nd.row+1][nd.col])
            V[nd.row+1][nd.col] = 2

        # Left
        if nd.col > 0 and not V[nd.row][nd.col-1]:
            D[nd.row][nd.col-1]=Node(nd.row, nd.col-1, nd.dsrc+1)
            P[pathIndex(nd.row, nd.col-1)] = pathIndex(nd.row,nd.col)
            Q.put(D[nd.row][nd.col-1])
            V[nd.row][nd.col-1] = 2

        # Right
        if nd.col+1 < M and not V[nd.row][nd.col+1]:
            D[nd.row][nd.col+1]=Node(nd.row, nd.col+1, nd.dsrc+1)
            P[pathIndex(nd.row, nd.col+1)] = pathIndex(nd.row,nd.col)
            Q.put(D[nd.row][nd.col+1])
            V[nd.row][nd.col+1] = 2

    dst = D[N-1][M-1]
    dst.ddst = 0
    Q = Queue()
    Q.put(dst)
    V = [[T[i][j] for j in range(M)] for i in range(N)]
    V[dst.row][dst.col] = 2
    nd = dst
    while not Q.empty():
        nd = Q.get()
        if nd == src:
            break
        # Up
        if nd.row > 0 and not V[nd.row-1][nd.col]:
            D[nd.row-1][nd.col].ddst = nd.ddst+1
            Q.put(D[nd.row-1][nd.col])
            V[nd.row-1][nd.col] = 2

        # Down
        if nd.row+1 < N and not V[nd.row+1][nd.col]:
            D[nd.row+1][nd.col].ddst = nd.ddst+1
            Q.put(D[nd.row+1][nd.col])
            V[nd.row+1][nd.col] = 2

        # Left
        if nd.col > 0 and not V[nd.row][nd.col-1]:
            D[nd.row][nd.col-1].ddst = nd.ddst+1
            Q.put(D[nd.row][nd.col-1])
            V[nd.row][nd.col-1] = 2

        # Right
        if nd.col+1 < M and not V[nd.row][nd.col+1]:
            D[nd.row][nd.col+1].ddst = nd.ddst+1
            Q.put(D[nd.row][nd.col+1])
            V[nd.row][nd.col+1] = 2
    printMatrix(D)
    printMatrix(T)
#    printPath(P)

    p = P[pathIndex(dst.row, dst.col)]
    gd = 0
    while p is not None:
        row, col = invPathIndex(p)
        # Up
        if row > 1 and T[row-1][col] and V[row-2][col]==2:
            sDiff = D[row][col].dsrc - D[row-2][col].dsrc
            dDiff = D[row][col].ddst - D[row-2][col].ddst
            if sDiff > gd: row1, col1, row2, col2, gd = row, col, row-2, col, sDiff
            if dDiff > gd: row1, col1, row2, col2, gd = row, col, row-2, col, dDiff
        # Down
        if row+2 < N and T[row+1][col]and V[row+2][col]==2:
            sDiff = D[row][col].dsrc - D[row+2][col].dsrc
            dDiff = D[row][col].ddst - D[row+2][col].ddst
            if sDiff > gd: row1, col1, row2, col2, gd = row, col, row+2, col, sDiff
            if dDiff > gd: row1, col1, row2, col2, gd = row, col, row+2, col, dDiff
        # Left
        if col > 1 and T[row][col-1]and V[row][col-2]==2:
            sDiff = D[row][col].dsrc - D[row][col-2].dsrc
            dDiff = D[row][col].ddst - D[row][col-2].ddst
            if sDiff > gd: row1, col1, row2, col2, gd = row, col, row, col-2, sDiff
            if dDiff > gd: row1, col1, row2, col2, gd = row, col, row, col-2, dDiff
        # Right
        if col+2 < M and T[row][col+1]and V[row][col+2]==2:
            sDiff = D[row][col].dsrc - D[row][col+2].dsrc
            dDiff = D[row][col].ddst - D[row][col+2].ddst
            if sDiff > gd: row1, col1, row2, col2, gd = row, col, row, col+2, sDiff
            if dDiff > gd: row1, col1, row2, col2, gd = row, col, row, col+2, dDiff
        p = P[p]
    
    print(gd)
    
    return dst.dsrc - gd
               
def main1():
    maze =  [[0, 1, 1, 0, 0, 0], \
             [0, 0, 1, 0, 1, 0], \
             [0, 1, 0, 0, 1, 0], \
             [0, 0, 1, 0, 1, 0], \
             [0, 1, 0, 0, 1, 0], \
             [0, 0, 0, 0, 1, 0]]
    #maze = [[0 for _ in range(6)] for _ in range(7)]
    ans = answer(maze)
    print (ans)
if __name__ == "__main__":
    main1()    
