# Problem: CF 1610 I - Mashtali vs AtCoder
# https://codeforces.com/contest/1610/problem/I

"""
Algorithm: Tree Game with Sprague-Grundy Theorem
Approach:
- This problem uses the Sprague-Grundy theorem to determine the winner of a game played on a tree.
- We compute the Grundy number (nimber) for each node by considering the subtree rooted at that node.
- A node's Grundy number is the XOR of the Grundy numbers of its children plus 1.
- Then we process the pinning of vertices from 1 to n, adjusting the game state using the Grundy numbers.
- The final result is determined by checking whether the overall Grundy number is zero (second player wins) or non-zero (first player wins).

Time Complexity: O(N)
Space Complexity: O(N)
"""

import sys

input = sys.stdin.buffer.readline

N = int(input())
T = [[] for i in range(N)]
for i in range(1, N):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    T[u].append(v)
    T[v].append(u)

stk = [(1, 0)]
par = [-1] * N
dp = [0] * N

while stk:
    t, u = stk.pop()
    if t == 1:
        stk.append((2, u))
        for v in T[u]:
            if v == par[u]:
                continue
            par[v] = u
            stk.append((1, v))
    else:
        for v in T[u]:
            if v == par[u]:
                continue
            dp[u] ^= dp[v] + 1

vis = [False] * N
vis[0] = True
ans = dp[0]
res = []

for i in range(N):
    u = i
    while not vis[u]:
        ans ^= (dp[u] + 1) ^ dp[u] ^ 1  # Adjust Grundy number for the current pinned vertex
        vis[u] = True
        u = par[u]
    res.append("2" if ans == 0 else "1")  # Determine winner based on final Grundy number
print("%s" % "".join(res))


# https://github.com/VaHiX/CodeForces/