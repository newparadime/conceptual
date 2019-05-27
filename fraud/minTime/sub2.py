#!/usr/bin/env python

import math
import os
import random
import re
import sys
from heapq import *

# Complete the minTime function below.
def minTime(M, g):
    tipd = sum(1.0/m for m in M if m > 0)
    days = g // tipd
    items = 0
    N = list()
    for dpi in M:
        mItems = days//dpi
        items += mItems
        mDays = mItems * dpi
        nextComp = mDays + dpi
        heappush(N,(nextComp,dpi))
    while items < g:
        (nextComp,dpi) = heappop(N)
        items += 1
        days = nextComp
        nextComp += dpi
        heappush(N,(nextComp,dpi))
    return int(days)
if __name__ == '__main__':
    fptr = sys.stdout

    nGoal = raw_input().split()

    n = int(nGoal[0])

    goal = int(nGoal[1])

    machines = map(long, raw_input().rstrip().split())

    ans = minTime(machines, goal)

    fptr.write(str(ans) + '\n')

    fptr.close()

