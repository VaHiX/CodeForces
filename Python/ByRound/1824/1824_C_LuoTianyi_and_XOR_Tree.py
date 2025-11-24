# Problem: CF 1824 C - LuoTianyi and XOR-Tree
# https://codeforces.com/contest/1824/problem/C

"""
Purpose: Solve the problem of making all root-to-leaf paths in a tree have XOR value of zero
with minimum number of operations (changing vertex values).

Algorithm:
- Use DFS traversal to process the tree bottom-up
- For each node, maintain a map (dictionary) of XOR values from root to current node
- When we reach a leaf node, we need to change the value to make path XOR = 0
- For internal nodes, we merge maps from children and count how many paths need to be changed
- The key insight is that when multiple paths have same XOR value, only one needs to be changed

Time Complexity: O(n) - Each node visited once, dictionary operations are O(1) amortized
Space Complexity: O(n) - For adjacency list, recursion stack, and maps

Techniques:
- DFS with stack simulation using generator
- Map merging and counting
- Path XOR manipulation
"""

import random
import sys

input = sys.stdin.readline
rd = random.randint(10**9, 2 * 10**9)

n = int(input())
a = list(map(int, input().split()))
g = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    g[u - 1].append(v - 1)
    g[v - 1].append(u - 1)

ans = 0
from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


@bootstrap
def dfs(son, fa):
    global ans
    # If this is a leaf node (not root and has only one neighbor)
    if son != 0 and len(g[son]) == 1:
        ans += 1
        yield {a[son]: 1}
    mp = {}
    mx = 0
    # Visit all children
    for x in g[son]:
        if x != fa:
            # XOR the child value with parent's value
            a[x] ^= a[son]
            # Recursively visit child
            m = yield dfs(x, son)
            # Optimize by always making mp the larger dictionary
            if len(m) > len(mp):
                mp, m = m, mp
            # Merge smaller map into larger one
            for k, v in m.items():
                mp[k] = mp.get(k, 0) + v
                mx = max(mx, mp[k])
            m.clear()

    # If we have multiple paths with same XOR value, we can reduce operations
    if mx > 1:
        ans -= mx - 1
        # Keep only the most frequent XOR value
        for k in list(mp.keys()):
            if mp[k] == mx:
                mp[k] = 1
            else:
                del mp[k]
    yield mp


m = dfs(0, -1)
# Account for the case where the root path itself has XOR = 0
ans -= 0 in m
print(ans)


# https://github.com/VaHiX/CodeForces/