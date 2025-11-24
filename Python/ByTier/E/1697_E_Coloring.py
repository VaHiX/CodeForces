# Problem: CF 1697 E - Coloring
# https://codeforces.com/contest/1697/problem/E

"""
Algorithm: 
This solution uses a graph-based approach to partition points into groups based on their pairwise Manhattan distances.
It identifies connected components in a graph where an edge exists between two points if their Manhattan distance equals the minimum distance from one of them.
The key idea is that points with equal minimum distances form cliques, and these are grouped accordingly.
Then, for each group size (1, 2, 3, 4), we calculate the number of valid colorings using combinatorics and inclusion-exclusion principles.
Time Complexity: O(n^2)
Space Complexity: O(n^2)
"""

input = __import__("sys").stdin.readline

MOD = 998244353

# Precompute factorials and inverse factorials for combinations
fact = [1]
invfact = [1]

for i in range(1, 101):
    fact.append(fact[-1] * i % MOD)
    invfact.append(pow(fact[-1], MOD - 2, MOD))


# Function to compute combination C(n, k)
def C(n, k):
    if k < 0 or k > n:
        return 0
    return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD


# Function to compute permutation P(n, k)
def P(n, k):
    if k < 0 or k > n:
        return 0
    return fact[n] * invfact[n - k] % MOD


n = int(input())
coords = []
for _ in range(n):
    x, y = map(int, input().split())
    coords.append((x, y))

# Initialize minimum distances for each point
min_dist = [10**9] * n
dist = [[-1] * n for _ in range(n)]

# Compute Manhattan distances between all pairs of points
for u in range(n):
    for v in range(n):
        dist[u][v] = abs(coords[u][0] - coords[v][0]) + abs(coords[u][1] - coords[v][1])
        if u != v:
            min_dist[u] = min(min_dist[u], dist[u][v])

cnt = [0, 0, 0, 0, 0]  # Count of groups of sizes 1, 2, 3, 4
vis = [False] * n

# Process points in order of increasing minimum distances
for u in sorted(range(n), key=lambda x: min_dist[x]):
    if vis[u]:
        continue

    vis[u] = True
    seen = [False] * n
    seen[u] = True
    ptr = 0
    found = [u]
    # BFS to find all points at minimum distance
    while ptr < len(found):
        v = found[ptr]
        ptr += 1
        for w in range(n):
            if not seen[w] and dist[v][w] == min_dist[v]:
                seen[w] = True
                found.append(w)

    # Check if all points in the connected component form a clique
    ok = all(
        dist[found[i]][found[j]] == min_dist[u]
        for i in range(len(found))
        for j in range(i + 1, len(found))
    )
    if len(found) == 1 or not ok:
        cnt[1] += 1
    else:
        # If they form a clique of size 2, 3, or 4, increase count
        cnt[len(found)] += 1
        for u in found:
            vis[u] = True


ans = 0
# Enumerate all valid combinations of group sizes
for two in range(cnt[2] + 1):
    for three in range(cnt[3] + 1):
        for four in range(cnt[4] + 1):
            # Calculate total number of colorings using permutations and combinations
            ans += (
                P(n, n - two - 2 * three - 3 * four)
                * C(cnt[2], two)
                % MOD
                * C(cnt[3], three)
                % MOD
                * C(cnt[4], four)
                % MOD
            )
            if ans >= MOD:
                ans -= MOD

print(ans)


# https://github.com/VaHiX/CodeForces/