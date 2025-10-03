# Contest 2022, Problem E1: Billetes MX (Easy Version)
# URL: https://codeforces.com/contest/2022/problem/E1

import io,os
from collections import deque 
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline




def main():
    m,n,k,q = map(int,input().split())

    neigh = [[] for _ in range(m+n)]
    for _ in range(k):
        i,j,num = map(int,input().split())
        i -= 1
        j = j - 1 + m
        neigh[i].append((j,num))
        neigh[j].append((i,num))

    visited = [-1]*(m+n)

#    print(neigh)

    g = 0
    queue = deque()
    for i in range(m+n):
        if visited[i] >= 0:  continue 
        visited[i] = 0
        g += 1
        queue.append(i)
        while queue:
            index = queue.popleft()
            for (nextindex, num) in neigh[index]:
                if visited[nextindex] >= 0:  
                    if visited[nextindex] != visited[index] ^ num:
                        print(0)
                        return 
                    continue
                visited[nextindex] = visited[index] ^ num
                queue.append(nextindex) 
           
#    print(visited) 
   
    M = 10**9 + 7
    ans = pow(2,30*(g-1),M)
    print(ans) 






T = int(input())
t = 1
while t <= T:
    main()
    t += 1
