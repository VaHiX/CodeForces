# Problem: CF 2115 E - Gellyfish and Mayflower
# https://codeforces.com/contest/2115/problem/E

"""
E. Gellyfish and Mayflower

The problem involves finding the maximum sum of card powers that can be achieved given a directed acyclic graph with vertices representing traders, where each trader has cost c[i] and power w[i]. We are to answer queries about maximizing total card power when starting at a certain vertex `p` with `r` coins.

Approach:
1. Build reverse graph for topological processing.
2. Use dynamic programming over time (coin count) to compute possible max power up to MAXT = MC * MC where MC is maximum cost.
3. For queries that are small enough, return precomputed results.
4. For large queries, use cyclic optimization:
   - Use topological sort based on w[i]/c[i] ratio.
   - Process vertices in this order and compute cycles.
   - Handle infinite gains in cycles when possible.

Time Complexity: O(n^2 * MAXT + q * n)
Space Complexity: O(n * MAXT + n * C) where C is cycle length

Algorithms/Techniques:
- Dynamic Programming with bounded time
- Topological sorting and cycle detection
- Optimization using cycle behavior for large queries
"""
import sys

input = sys.stdin.readline
n, m = map(int, input().split())
c = [0] * n
w = [0] * n
for i in range(n):
    c[i], w[i] = map(int, input().split())
rev = [[] for i in range(n)]
for k in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    rev[b].append(a)
MC = max(c)
MAXT = MC * MC
small = [[0] * n]
for t in range(1, MAXT + 1):
    prev = small[t - 1]
    cur = prev[:]
    for i in range(n):
        if t >= c[i]:
            val = small[t - c[i]][i] + w[i]
            if val > cur[i]:
                cur[i] = val
        for j in rev[i]:
            if cur[j] > cur[i]:
                cur[i] = cur[j]
    small.append(cur)
q = int(input())
queries = [tuple(map(int, input().split())) for _ in range(q)]
for i in range(q):
    p, r = queries[i]
    queries[i] = (p - 1, r)
answer = [-1] * q
for i, (p, r) in enumerate(queries):
    if r <= MAXT:
        answer[i] = small[r][p]
order = list(range(n))
order.sort(key=lambda i: w[i] / c[i])
valid = [False] * n
for best in order:
    valid[best] = True
    if not valid[0]:
        continue
    C = c[best]
    W = w[best]
    cycs = [None] * n
    cycs[0] = [-(10**18)] * C
    cycs[0][0] = 0
    for i in range(n):
        if not valid[i]:
            continue
        for j in rev[i]:
            if i > best and j < best:
                continue
            if cycs[j] is None:
                continue
            if cycs[i] is None:
                cycs[i] = cycs[j][:]
            else:
                for t in range(C):
                    if cycs[j][t] > cycs[i][t]:
                        cycs[i][t] = cycs[j][t]
        if cycs[i] is None:
            continue
        vis = [0] * C
        for start in range(C):
            cur0 = start
            while vis[cur0] < 2:
                vis[cur0] += 1
                nxt = cur0 + c[i]
                blocks = nxt // C
                rem = nxt % C
                cand = cycs[i][cur0] + w[i] - blocks * W
                if cand > cycs[i][rem]:
                    cycs[i][rem] = cand
                cur0 = rem
        for t in range(1, C):
            if cycs[i][t - 1] > cycs[i][t]:
                cycs[i][t] = cycs[i][t - 1]
    for idx, (p, r) in enumerate(queries):
        if p < best:
            continue
        tbl = cycs[p]
        if tbl is None:
            continue
        if r < MC * C:
            continue
        full = r // C
        rem = r % C
        cand = tbl[rem] + full * W
        if cand > answer[idx]:
            answer[idx] = cand
print(*answer)


# https://github.com/VaHiX/codeForces/