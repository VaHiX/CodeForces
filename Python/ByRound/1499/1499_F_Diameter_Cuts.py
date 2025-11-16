# Problem: CF 1499 F - Diameter Cuts
# https://codeforces.com/contest/1499/problem/F

"""
Algorithm: Tree Dynamic Programming with diameter constraint
Time Complexity: O(n^2)
Space Complexity: O(n^2)

This solution uses dynamic programming on trees to count the number of valid edge sets.
For each node, we maintain a dp array where dp[v][d] represents the number of ways to 
remove edges in the subtree rooted at v such that the resulting tree has diameter <= d.

The algorithm works by:
1. Performing a DFS to build the tree structure
2. For each edge, we propagate information from children to parent
3. For each node, we combine results from its children considering the diameter constraint
4. The final answer is the sum of all valid configurations in the root's dp array
"""

mod = 998244353
n, k = map(int, input().split())
edge = [[] for i in range(n)]
for _ in range(n - 1):
    a, b = map(lambda x: int(x) - 1, input().split())
    edge[a].append(b)
    edge[b].append(a)

# dp[v][d] = number of ways to remove edges in subtree rooted at v with diameter <= d
dp = [[1] for i in range(n)]

size = [1] * n
todo = [(0, 0, -1)]
while todo:
    t, v, p = todo.pop()
    if t == 0:
        # First visit: schedule children for processing
        for u in edge[v]:
            if u != p:
                todo.append((1, u, v))
                todo.append((0, u, v))
    else:
        # Second visit: compute dp for node v and combine with parent p
        # Create new dp array for parent p with combined information from v
        ndp = [0] * (max(size[p], size[v] + 1))
        for d1 in range(size[p]):
            for d2 in range(size[v]):
                # If combining two trees results in diameter <= k
                if d1 + d2 + 1 <= k:
                    ndp[max(d1, d2 + 1)] += dp[p][d1] * dp[v][d2]
                # Always add the case where we don't connect the trees
                ndp[d1] += dp[p][d1] * dp[v][d2]
        dp[p] = [i % mod for i in ndp]
        size[p] = max(size[p], size[v] + 1)

# Sum all valid configurations for the root
print(sum(dp[0]) % mod)


# https://github.com/VaHiX/CodeForces/