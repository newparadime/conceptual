#!/usr/bin/env python
from math import log
c = '10'
d = 12 #int(ord(c) - ord('0'))
l2 = log(d,2)
l4 = log(d,4)
a = int(l2 -1 + (1-2**l2)/(1-2) - d/10) + int(l4-1 + (1-4**l4)/(1-4)-d/100)
print (c,str(d),str(a))

