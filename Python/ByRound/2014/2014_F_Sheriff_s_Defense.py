# Contest 2014, Problem F: Sheriff's Defense
# URL: https://codeforces.com/contest/2014/problem/F

import sys
input = sys.stdin.read
data = input().split()
idx = 0

t = int(data[idx])
idx += 1
for _ in range(t):
    n, c = int(data[idx]), int(data[idx+1])
    idx +=2
    a = list(map(int, data[idx:idx+n]))
    idx +=n
    adj = [[] for _ in range(n+1)]
    for _ in range(n-1):
        u = int(data[idx])
        v = int(data[idx+1])
        idx +=2
        adj[u].append(v)
        adj[v].append(u)
    
    dp0 = [0] * (n+1)
    dp1 = [0] * (n+1)
    stack = [(1, 0, False)]
    
    while stack:
        node, parent, visited = stack.pop()
        if not visited:
            stack.append((node, parent, True))
            for neighbor in reversed(adj[node]):
                if neighbor != parent:
                    stack.append((neighbor, node, False))
        else:
            sum_dp0 = 0
            sum_dp1 = 0
            for child in adj[node]:
                if child != parent:
                    sum_dp0 += max(dp0[child], dp1[child])
                    option = max(dp0[child], dp1[child] - 2 * c)
                    sum_dp1 += option
            dp0[node] = sum_dp0
            dp1[node] = a[node-1] + sum_dp1
    
    print(max(dp0[1], dp1[1]))