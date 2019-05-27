#!/usr/bin/env python

from Queue import LifoQueue

def BFS(graph, src, sink, augPath):
    visited = [False] * len(graph)
    
    queue = LifoQueue()
    
    queue.put(src)
    
    visited[src] = True
    
    while not queue.empty():
        node = queue.get()
        for ind, val in enumerate(graph[node]):
            if not visited[ind] and val > 0:
                queue.put(ind)
                visited[ind] = True
                augPath[ind] = node
                
    if visited[sink]: return True
    else: return False

def answer(srcs, sinks, path):
    for node in path:
        node.insert(0,0)
        node.append(0)

    path.insert(0, [0]*len(path[0]))
    path.append([0]*len(path[0]))

    superSourceInd = 0
    superSinkInd   = len(path)-1
    
    for node in srcs:
        path[superSourceInd][node+1] = sum(path[node+1])
        
    for node in sinks:
        for elem in path:
            path[node+1][superSinkInd] += elem[node+1]
            
    residual = path[:]
    
    maxFlow = 0
    
    augPath = [-1]*len(path)
  
    while BFS(residual, superSourceInd, superSinkInd, augPath):
        augPathFlow = float('Inf')
        s = superSinkInd
        
        while s != superSourceInd:
            augPathFlow = min(augPathFlow, residual[augPath[s]][s])
            s = augPath[s]
            
        maxFlow += augPathFlow
        
        j = superSinkInd
        while j != superSourceInd:
            i = augPath[j]
            residual[i][j] -= augPathFlow
            residual[j][i] += augPathFlow
            j = augPath[j]
            
    return maxFlow
    
def main1():
    path =  [[0, 7, 0, 0], \
              [0, 0, 6, 0], \
              [0, 0, 0, 8], \
              [9, 0, 0, 0]]
              
    srcs = [0]
    sinks = [3]
    
    ans = answer(srcs, sinks, path)
    print (ans)
    
def main2():
    path = [[0, 0, 4, 6, 0, 0], \
            [0, 0, 5, 2, 0, 0], \
            [0, 0, 0, 0, 4, 4], \
            [0, 0, 0, 0, 6, 6], \
            [0, 0, 0, 0, 0, 0], \
            [0, 0, 0, 0, 0, 0]]
    
    srcs = [0, 1]
    sinks = [4 ,5]
    
    ans = answer(srcs, sinks, path)
    print (ans)
    
if __name__ == "__main__":
    main2()
