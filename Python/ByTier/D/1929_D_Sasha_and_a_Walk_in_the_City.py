# Problem: CF 1929 D - Sasha and a Walk in the City
# https://codeforces.com/contest/1929/problem/D

"""
Algorithm: Tree Dynamic Programming
Purpose: Count the number of "good" sets of intersections in a tree such that no simple path contains more than 2 dangerous intersections.

Time Complexity: O(n) per test case, where n is the number of nodes.
Space Complexity: O(n) for storing the tree and DP arrays.

The solution uses a centroid decomposition-like approach to compute for each node the number of valid subsets
that can be formed in its subtree, ensuring that no path in the subtree has more than 2 dangerous nodes.
"""

def solve():
    n = int(input())
    g = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        g[u].append(v)
        g[v].append(u)
    mod = 998244353
    ans = 1  # Start with 1 because we count the empty set (which is always good)
    dp = [0] * (n + 1)
    stk, lis = [], []
    stk.append((1, 0))  # (node, parent)
    lis.append((1, 0))
    while stk:
        u, f = stk.pop()
        for v in g[u]:
            if v == f:
                continue
            stk.append((v, u))
            lis.append((v, u))
    while lis:
        u, f = lis.pop()  # Process in reverse order to ensure children are processed before parent
        res = 1  # Initialize result for current node
        for v in g[u]:
            if v == f:
                continue
            res = (res * (dp[v] + 1)) % mod  # Multiply by (dp[v] + 1) to include all valid subsets from subtree
        dp[u] = res  # Store number of valid sets rooted at u
        ans = (ans + res) % mod  # Add to final answer
    print(ans)


T = int(input())
for _ in range(T):
    solve()


# https://github.com/VaHiX/CodeForces/