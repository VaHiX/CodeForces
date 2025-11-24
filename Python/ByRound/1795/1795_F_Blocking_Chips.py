# Problem: CF 1795 F - Blocking Chips
# https://codeforces.com/contest/1795/problem/F

"""
Algorithm: Binary search on the answer with a greedy validation approach.
Time Complexity: O(n * log(n)) per testcase due to binary search and validation.
Space Complexity: O(n) for storing the tree structure and auxiliary arrays.

Techniques:
- Tree traversal using DFS to build parent relationships
- Binary search on the number of moves
- Greedy validation of whether a given number of moves is possible
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
t, output = int(input()), []


def solve() -> int:
    n = int(input())
    graph, test = [[] for _ in range(n)], False
    for j in range(n - 1):
        u, v = map(int, input().split())
        graph[u - 1].append(v - 1), graph[v - 1].append(u - 1)
    black, order, pars, k = [], [0], [0] + [-1] * (n - 1), int(input())
    for b in map(int, input().split()):
        black.append(b - 1)
    for u in order:
        for v in graph[u]:
            if pars[v] >= 0:
                continue
            pars[v] = u
            order.append(v)
    order.reverse()

    def good(cand: int, n=n) -> bool:
        need, down = [-1] * n, [0] * n
        for i, b in enumerate(black):
            need[b] = cand // k + (cand % k > i)  # Compute how many chips we need at each node
        for u in order:
            if need[u] > down[u]:
                # If we need more chips at this node than we currently have,
                # we must move from parent node, unless it's root
                if u == 0 or need[pars[u]] >= 0:
                    return False
                need[pars[u]] = need[u] - 1
            elif need[u] == -1:
                # If we don't need any chips at this node, propagate the down count to parent
                down[pars[u]] = max(down[pars[u]], down[u] + 1)
        return True

    minN, maxN = 1, n - k + 1
    while minN < maxN:
        midN = (minN + maxN) // 2
        if good(midN):
            minN = midN + 1
        else:
            maxN = midN
    return minN - 1


for _ in range(t):
    output.append(solve())
for o in output:
    print(o)


# https://github.com/VaHiX/CodeForces/