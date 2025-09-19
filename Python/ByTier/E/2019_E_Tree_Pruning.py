# Contest 2019, Problem E: Tree Pruning
# URL: https://codeforces.com/contest/2019/problem/E

import sys
input = sys.stdin.buffer.readline
 
for _ in range(int(input())):
    n = int(input())
    adj = [[] for _ in range(n)]
    for _ in range(n-1):
        u, v = [int(x)-1 for x in input().split()]
        adj[u].append(v)
        adj[v].append(u)
    deg = [len(adj[v])-int(v!=0) for v in range(n)]
    pre = [-1] * n
    ans = n-1
    add = 0
    Q = [0]
    while Q:
        nQ = []
        for v in Q:
            if len(adj[v])==1 and v!=0: #go up
                p = v
                add -= 1
                while pre[p]!=0 and deg[pre[p]] == 1:
                    add -= 1
                    p = pre[p]
                deg[pre[p]] -= 1
            else: #go down
                for u in adj[v]:
                    if u==pre[v]: continue
                    add += 1
                    pre[u] = v
                    nQ.append(u)
        Q = nQ
        ans = min(ans, n-1-add)
    print(ans)