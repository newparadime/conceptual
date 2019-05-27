#!/usr/bin/env python
import collections
import itertools
from collections import deque

S = "ababababababab"
n = len(S)
chunks = [S[beg:beg+2] for beg in xrange(0, len(S), 2)]
s = set(chunks)
print next(iter(s))
for l in s:
	print (l)
