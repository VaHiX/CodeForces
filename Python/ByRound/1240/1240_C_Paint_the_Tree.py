# Problem: CF 1240 C - Paint the Tree
# https://codeforces.com/contest/1240/problem/C

"""
C. Paint the Tree

This problem involves finding the maximum value of a k-coloring of a tree,
where each edge is considered "saturated" if both its endpoints share at least one color.
Each vertex gets exactly k colors, and colors can be reused up to twice.

The approach uses dynamic programming on trees:
- For each node, we compute two values:
  - dp[node][0]: maximum value when we don't use the edge from parent to node
  - dp[node][1]: maximum value when we do use the edge from parent to node

Time Complexity: O(n * k * log(k)) per query, where n is number of nodes.
Space Complexity: O(n * k) for storage in DP table.

Algorithms/Techniques:
- Tree Dynamic Programming
- Greedy selection with sorting
"""

import sys

input = sys.stdin.readline


def dfs(root, n):
    par = [-1] * (n + 1)
    que = [~root, root]
    now = -1
    while que:
        crr = que.pop()
        now += 1
        if crr >= 0:
            # Traverse to children nodes
            for nxt, w in graph[crr]:
                if par[crr] == nxt:
                    continue
                par[nxt] = crr
                que.append(~nxt)
                que.append(nxt)
        else:
            # Process current node (post-order traversal)
            crr = ~crr
            if len(graph[crr]) - 1 < k:
                # If less than k children, we can take all edges optimally
                tmp = 0
                for nxt, w in graph[crr]:
                    if par[crr] == nxt:
                        continue
                    tmp += max(dp[nxt * 2 + 1] + w, dp[nxt * 2 + 0])
                dp[crr * 2 + 1] = tmp
                dp[crr * 2 + 0] = tmp
            else:
                # More than k children: need to select best k edges greedily
                ds = []
                tmp = 0
                for nxt, w in graph[crr]:
                    if par[crr] == nxt:
                        continue
                    ds.append(max(0, dp[nxt * 2 + 1] + w - dp[nxt * 2 + 0]))
                    tmp += dp[nxt * 2 + 0]
                ds.sort()
                ds = [0] + ds[::-1]
                for i in range(1, len(ds)):
                    ds[i] += ds[i - 1]
                dp[crr * 2 + 1] = ds[k - 1] + tmp
                dp[crr * 2] = (ds[k]) + tmp
            if par[crr] == -1:
                continue
    return


def sol():
    global graph, dp, k
    n, k = map(int, input().split())
    graph = [[] for i in range(n + 1)]
    for i in range(n - 1):
        u, v, w = map(int, input().split())
        graph[u].append((v, w))
        graph[v].append((u, w))
    dp = [0] * (2 * (n + 1))
    dfs(1, n)
    print(max(dp[1 * 2 + 0], dp[1 * 2 + 1]))
    return


T = int(input())
for i in range(T):
    sol()


# https://github.com/VaHiX/codeForces/