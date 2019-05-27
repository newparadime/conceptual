#!/usr/bin/env python

from collections import deque
def CorrectPath(string): 
    def nextMove(move):
        if move == 'd': return 'u'
        if move == 'u': return 'r'
        if move == 'r': return 'l'
        if move == 'l': return None
    lst = list(string)
    
    ind = 0
    x = 0
    y = 0
    indDeq = deque()
    xDeq = deque()
    yDeq = deque()
    indDeq.append(ind)
    xDeq.append(x)
    yDeq
    while ind < len(lst):
        print ind, x, y, lst[ind]

        if lst[ind] == '?':
            xDeq.append(x)
            yDeq.append(y)
            indDeq.append(ind)
            lst[ind] = 'd'

        if lst[ind] == 'r': 
            x += 1
            ind += 1
        elif lst[ind] == 'l': 
            x -= 1
            ind += 1
        elif lst[ind] == 'd': 
            y += 1
            ind += 1
        elif lst[ind] == 'u': 
            y -= 1
            ind += 1

        if ind < len(lst):
            print ind, x, y, lst[ind]
            print

        if x > 4 or y > 4 or x < 0 or y < 0 or (ind == len(lst) and (x != 4 or y != 4)):
            ind = indDeq.pop()
            x = xDeq.pop()
            y = yDeq.pop()
            move = nextMove(lst[ind])
            while move is None:
                lst[ind] = '?'
                ind = indDeq.pop()
                x = xDeq.pop()
                y = yDeq.pop()
                move = nextMove(lst[ind])
            indDeq.append(ind)
            xDeq.append(x)
            yDeq.append(y)
            lst[ind] = move
        
    string = ''.join(lst)
    return string
    
def main1():
    print CorrectPath("r?d?drdd")
    
if __name__ == "__main__":
    main1()
