# Problem: CF 1695 D2 - Tree Queries (Hard Version)
# https://codeforces.com/contest/1695/problem/D2

from collections import deque

I = input


def f(x, pre):
    # Perform BFS to compute subtree information
    q = deque([(x, pre)])
    dp = [0] * (n + 1)
    R = []
    while q:
        u, p = q.popleft()
        R.append((u))
        for v in g[u]:
            if v != p:
                g[v].remove(u)  # Remove parent to avoid cycles
                q.append((v, u))
    # Post-order traversal to compute dp values
    for u in R[::-1]:
        z = c = 0
        for v in g[u]:
            z += dp[v]
            if dp[v] == 0:
                c += 1
            dp[u] = z + max(0, c - 1)
    return dp[x]


for _ in [0] * int(I()):
    n = int(I())
    g = [[] for _ in range(n + 1)]
    # Build adjacency list representation of tree
    for _ in range(n - 1):
        u, v = map(int, I().split())
        g[u].append(v)
        g[v].append(u)
    # Handle special case of single node
    if n == 1:
        z = 0
    else:
        # Find a vertex with degree >= 3 to use as root for query strategy
        for u in range(1, n + 1):
            if len(g[u]) >= 3:
                z = f(u, 0)
                break
        else:
            # All nodes have degree < 3 (tree is a path), so only 1 query needed
            z = 1
    print(z)

### Complexity Analysis

# **Time Complexity:**
# - For each test case, the algorithm constructs the adjacency list in O(n) time.
# - The `f` function performs BFS and post-order DFS on the tree, both taking O(n) time.
# - Therefore, the total time complexity per test case is O(n).
# - Since the sum of all n over test cases is bounded by 2*10^5, the total time complexity is O(n).

# **Space Complexity:**
# - The space used by the adjacency list `g` is O(n).
# - The deque `q` and list `R` can grow up to O(n) in the worst case.
# - The `dp` array uses O(n) space.
# - Therefore, the overall space complexity is O(n).

# https://github.com/VaHiX/CodeForces/