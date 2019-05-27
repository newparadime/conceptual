#!/usr/bin/env python

from fractions import *

def gcd(a, b):
    while b:      
        a, b = b, a % b
    return a
    
def lcm(a, b):
    return a * b // gcd(a, b)

def lcmm(l):
		return reduce(lambda x, y: lcm(x, y), l)
   
def matmult(a,b):
    zip_b = zip(*b)
    return [[sum(ele_a*ele_b for ele_a, ele_b in zip(row_a, col_b)) 
             for col_b in zip_b] for row_a in a]

def transposeMatrix(m):
    t = []
    for r in range(len(m)):
        tRow = []
        for c in range(len(m[r])):
            if c == r:
                tRow.append(m[r][c])
            else:
                tRow.append(m[c][r])
        t.append(tRow)
    return t

def getMatrixMinor(m,i,j):
    return [row[:j] + row[j+1:] for row in (m[:i]+m[i+1:])]

def getMatrixDeterminant(m):
    if len(m) == 2:
        return m[0][0]*m[1][1]-m[0][1]*m[1][0]

    determinant = 0
    for c in range(len(m)):
        determinant += ((-1)**c)*m[0][c]*getMatrixDeterminant(getMatrixMinor(m,0,c))
    return determinant

def getMatrixInverse(m):
    determinant = getMatrixDeterminant(m)

    if len(m) == 2:
        return [[m[1][1]/determinant, -1*m[0][1]/determinant],
                [-1*m[1][0]/determinant, m[0][0]/determinant]]

    cofactors = []
    for r in range(len(m)):
        cofactorRow = []
        for c in range(len(m)):
            minor = getMatrixMinor(m,r,c)
            cofactorRow.append(((-1)**(r+c)) * getMatrixDeterminant(minor))
        cofactors.append(cofactorRow)
    cofactors = transposeMatrix(cofactors)
    for r in range(len(cofactors)):
        for c in range(len(cofactors)):
            cofactors[r][c] = cofactors[r][c]/determinant
    return cofactors

def answer(m):
	if len(m) == 1:
		return [1,1]
	term = []
	nterm = []

	for ind, val in enumerate(m):
		if sum(val) == 0:
			term.append(ind)
		else:
			nterm.append(ind)
	
	if len(term) == 1:
		return [1,1]

	order = term + nterm

	limM = []
	n = 0
	for i in term:
		limM.append(m[i])
		limM[n][n] = 1
		n += 1
	
	for i in nterm:
		t, t2 = [], []
		for n in order:
			t.append(m[i][n])
		for ind, val in enumerate(t):
			t2.append(Fraction(val, sum(t) ))  
		limM.append(t2)
	
	I, R, Q = [], [], []

	for p in range(len(term),len(limM)):
		R.append(limM[p][:len(term)])
		Q.append(limM[p][len(term):])
		
	for u in range(0, len(Q)):
		t = [0] * len(Q)
		t[u] = 1
		I.append(t)

	IQ = []
	for p in range(0, len(I)):
		t = []
		for o in range(0, len(I[0])):
			t.append(I[p][o]-Q[p][o])
		IQ.append(t)

	F = getMatrixInverse(IQ)
	
	FR = matmult(F,R)
	
	alm = []
	for i in FR[0]:
		alm.append([i.numerator, i.denominator])
	

	lcm1 = lcmm([i[1] for i in alm])
	
	ans = [ (lcm1/i[1]) * i[0] for i in alm ]
	return ans + [lcm1]

def main1():
    m = [[0, 1, 0, 0, 0, 1], [4, 0, 0, 3, 2, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]
    ans = answer(m)
    print ans

if __name__ == "__main__":
    main1()

