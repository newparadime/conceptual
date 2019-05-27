#!/usr/bin/env python

num=29
print list(i for i in range(num) if all(i%j for j in xrange(2, int(i**0.5)+1)) and i>1)
