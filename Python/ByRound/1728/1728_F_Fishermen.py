# Problem: CF 1728 F - Fishermen
# https://codeforces.com/contest/1728/problem/F

"""
Algorithm: Hungarian Algorithm with Greedy Matching
Time Complexity: O(n^3)
Space Complexity: O(n^2)

This solution uses a greedy approach combined with bipartite matching to find the minimum sum
of fish sizes. It constructs a graph where edges represent valid transitions between fish sizes
and uses a greedy matching strategy to minimize the total sum.
"""

import sys

input = sys.stdin.readline

n = int(input())
a = list(map(int, input().split(" ")))

# Generate all multiples of each fish size up to n
val = []

for i in range(n):
    for j in range(1, n + 1):
        val.append([a[i] * j, i])

# Sort by the multiples
val.sort(key=lambda x: x[0])

# Remove duplicates and group indices
valUnique = [val[0][0]]
edge = [[val[0][1]]]

for i in range(1, n * n):
    if valUnique[-1] == val[i][0]:
        edge[-1].append(val[i][1])
    else:
        valUnique.append(val[i][0])
        edge.append([val[i][1]])

# Initialize matching variables
vis = [False for _ in range(n)]
match = [-1 for _ in range(n)]


# Depth-first search for maximum matching
def dfs(u):
    for v in edge[u]:
        if not vis[v]:
            vis[v] = True
            if match[v] == -1 or dfs(match[v]):
                match[v] = u
                return True
    return False


matchNum = 0
ans = 0
i = 0

# Greedily assign matches to minimize total sum
while matchNum < n:
    if dfs(i):
        matchNum += 1
        ans += valUnique[i]
        for j in range(n):
            vis[j] = False
    i += 1

print(ans)


# https://github.com/VaHiX/CodeForces/