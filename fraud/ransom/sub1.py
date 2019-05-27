#!/bin/python

import math
import os
import random
import re
import sys

# Complete the checkMagazine function below.
def checkMagazine(magazine, note):
    mag = set(magazine)
    for word in note:
        if word in mag:
            mag.remove(word)
        else:
            print word
            print (mag)
            print "No"
            return
    print "Yes"
        
if __name__ == '__main__':
    mn = raw_input().split()

    m = int(mn[0])

    n = int(mn[1])

    magazine = raw_input().rstrip().split()

    note = raw_input().rstrip().split()

    checkMagazine(magazine, note)

