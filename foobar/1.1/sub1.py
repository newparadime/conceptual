#!/usr/bin/env python

import numpy as np
def answer(m):
    Q = np.matrix(m)# - np.identity(len(m[0]))
    newrow = [1 for _ in range(len(m[0]))]
    Q = np.matrix(np.vstack([Q, newrow]))
    Qt = Q.T
    Qp = Q*Qt
    blist = [0 for _ in range(len(m)-1)]
    blist.append(1)
    b = np.array(blist)
    b.shape = (len(blist),1)
    b = np.matrix(b)
    V = Qt*Qp.I
    print V
    print b
    Vs = V.squeeze()
    return Vs.tolist()
    
def main1():
    p = [[0, 1, 0, 0, 0, 1], [4, 0, 0, 3, 2, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]
    ans = answer(p)
    print ans

if __name__ == "__main__":
    main1()
