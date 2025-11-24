# Problem: CF 2156 E - Best Time to Buy and Sell Stock
# https://codeforces.com/contest/2156/problem/E

"""
Algorithm: Binary Search on Answer + Graph Construction
Time Complexity: O(n log(max_val - min_val)) where max_val and min_val are the max and min elements in array.
Space Complexity: O(n) for storing the graph and auxiliary arrays.

Approach:
- We binary search on the answer (the beauty value).
- For a given beauty value 'd', we construct a graph where an edge exists between indices i and j if a[j] - a[i] >= d.
- We then check if there exists a valid configuration of locked elements such that the final array has beauty >= d.
- This involves checking the degrees of nodes in the constructed graph to determine if a valid selection of locked elements exists.

"""
import sys
from math import inf

input = sys.stdin.readline

rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))


def solve():

    n, a = rn(), list(enumerate(rl()))

    def check(d):

        # Initialize graph and degree array
        g = [[] for _ in range(n)]
        deg = [0] * n

        # Function to add edges for min case (left to right)
        def add_edges(a, func, uni, dist):
            val = uni
            for i, x in a:
                p, q, r = val
                for w, idx in val:
                    if dist(x, w) >= d:
                        g[i].append(idx)
                        deg[i] += 1
                # Update val based on the function
                val = func(val, ((x, i), p, q), (p, (x, i), q), (p, q, (x, i)))

        # Process from left to right for min differences
        add_edges(a, min, ((inf, -1), (inf, -1), (inf, -1)), lambda x, y: x - y)
        
        # Process from right to left for max differences
        add_edges(
            a[::-1], max, ((-inf, -1), (-inf, -1), (-inf, -1)), lambda x, y: y - x
        )

        # Find vertices with degree >= 3
        super_vertex = [i for i in range(n) if deg[i] >= 3]
        if len(super_vertex) > 1:
            return True
        if len(super_vertex) == 1:
            v = super_vertex[0]
            for i in range(v):
                deg[i] -= a[v][1] - a[i][1] >= d
            for i in range(v + 1, n):
                deg[i] -= a[i][1] - a[v][1] >= d
            deg[v] = 0
            return not all(deg[i] <= 1 for i in range(n))

        # Find vertices with degree 2
        two_deg_vertex = [i for i in range(n) if deg[i] == 2]
        two_deg_cnt = len(two_deg_vertex)
        if two_deg_cnt == 0:
            return False

        for u in two_deg_vertex:
            if [deg[v] for v in g[u]].count(2) == two_deg_cnt - 1:
                return False
        return True

    # Binary search on the beauty value
    left, right = -1 << 30, 1 << 30
    while left < right:
        mid = ((left + right) >> 1) + 1
        if check(mid):
            left = mid
        else:
            right = mid - 1

    print(left)


[solve() for _ in range(rn())]


# https://github.com/VaHiX/CodeForces/