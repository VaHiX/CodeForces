# Problem: CF 1914 F - Programming Competition
# https://codeforces.com/contest/1914/problem/F

"""
Algorithm: Tree-based greedy matching
Approach:
- Build a tree from the parent array where each node points to its children
- Calculate depth of each node using DFS
- Greedily form teams by matching nodes with same depth levels
- Use a greedy strategy to avoid assigning nodes that are superiors of each other

Time Complexity: O(n) per test case, since we visit each node constant times
Space Complexity: O(n) for storing tree structure and depth array
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    par = list(map(lambda x: int(x) - 1, input().split()))
    g = [[] for _ in range(n)]
    # Build adjacency list from parent information
    for u, v in enumerate(par, 1):
        g[v].append(u)
    
    d = [0] * n  # depth array
    stack = [(0, 0)]  # (node, depth)
    # Compute depths using DFS
    while stack:
        x, y = stack.pop()
        d[y] += 1  # increment count for this depth level
        for z in g[x]:
            stack.append((z, y + 1))
    
    ans = tmp = 0
    # Process from deepest level to shallowest
    for i in range(n - 1, -1, -1):
        # Calculate how many pairs can be formed between current level and previous level
        x = max(0, min(tmp, d[i] - 1))
        ans += x  # add to final answer
        d[i] -= x  # reduce count of available nodes at this level
        tmp -= x  # reduce residual nodes to match with
        ans += d[i] >> 1  # form pairs within same level
        tmp += d[i] % 2  # if odd, one node remains unmatched to match with next level
    
    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/