#!/usr/bin/env python
from fractions import Fraction
def answer(P):
    D = [P[i+1]-P[i] for i in range(len(P)-1)]
    r_n = 0
    m = 1
    for d in D:
        r_n += d*m
        m *= -1

    if len(P) > 3:
        if len(P) % 2 == 0:
            m = 3
        else: m = 2
    else: m = 1
    r_n /= m
    d_n = 0
    m = 1
    for d in reversed(D):
        d_n += d*m
        m *= -1
    r_0 = (r_n - d_n)*m
    if r_0 < 0: return [-1,-1]
    R = Fraction(r_0)
    next_r = r_0
    for d in D:
        next_r = d - next_r
        if next_r <= 0: return [-1,-1]
    return [R.numerator,R.denominator]
print(ans[0],ans[1])
