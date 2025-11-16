# Problem: CF 1869 F - Flower-like Pseudotree
# https://codeforces.com/contest/1869/problem/F

"""
Code Purpose:
This code determines whether a flower-like pseudotree can be constructed given
the degrees of vertices. A flower-like pseudotree is a connected graph with
exactly one cycle and all trees in the forest formed by removing the cycle
have the same depth when rooted at the vertex on the cycle.

Algorithms/Techniques:
- Graph theory and degree sequence analysis
- Construction algorithm based on sorting vertices by degree
- Greedy edge pairing to form a valid pseudotree structure

Time Complexity:
O(n log n) per test case due to sorting operations, where n is the number of vertices.
Space Complexity:
O(n) for storing the degree array and result edges.
"""

import sys


def find_pairs(ds):
    n = len(ds)
    if sum(ds) != 2 * n:
        return None
    if 2 not in ds:
        # If no vertex has degree 2, process as a special case
        hi, lo = [], []
        for i, d in enumerate(ds):
            if d > 2:
                hi += [i]
            else:
                lo += [i]
        ans = list(zip(hi, hi[1:] + hi[:1]))
        for i in hi:
            for j in range(ds[i] - 2):
                ans += [(i, lo.pop())]
        return ans
    big = sum(v > 2 for v in ds)
    if big == 0:
        # All vertices have degree <= 2, form a cycle
        a = list(range(n))
        return list(zip(a, a[1:] + a[:1]))
    if big == 1 or (big == 2 and ds.count(2) == 1):
        # Special cases where construction is impossible
        return None
    if max(ds) == 3:
        a, b = ds.count(3), ds.count(2)
        if (a + b) % 2 == 1 and (a == 2 or a + b < 6):
            return None
    ans = []

    def add_edge(i, j):
        ans.append((i, j))
        ds[i] -= 1
        ds[j] -= 1

    # Sort vertices by degree in descending order
    ids = sorted(range(n), key=lambda i: ds[i], reverse=True)
    add_edge(ids[0], ids[1])
    add_edge(ids[1], ids[0])
    for i in range(2, n - 1, 2):
        if ds[ids[i + 1]] < 2:
            break
        add_edge(ids[i - 2], ids[i])
        add_edge(ids[i - 1], ids[i + 1])
    hot = ids[:i][::-1]
    for u in ids[i:]:
        while ds[hot[-1]] == 0:
            hot.pop()
        add_edge(u, hot[-1])
        hot += [u]
    return ans


input_func = lambda: sys.stdin.readline()
output_func = lambda *args: sys.stdout.write(" ".join(map(str, args)) + "\n")
for _ in range(int(input_func())):
    n = int(input_func())
    ans = find_pairs(list(map(int, input_func().split())))
    if not ans:
        output_func("No")
        continue
    output_func("Yes")
    for i, j in ans:
        output_func(i + 1, j + 1)


# https://github.com/VaHiX/CodeForces/