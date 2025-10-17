# Problem: CF 2019 F - Max Plus Min Plus Size
# https://codeforces.com/contest/2019/problem/F

"""
F. Max Plus Min Plus Size

Purpose:
This code solves a dynamic programming problem where we need to select non-adjacent elements from an array such that 
the sum of (max element, min element, and count) of selected elements is maximized.

Approach:
The solution uses a Union-Find (Disjoint Set Union) data structure combined with a greedy strategy. 
We process elements in decreasing order of value and merge adjacent valid segments to maintain connectivity,
tracking how many "even" segments exist (where even_max or odd_max properties are active).
This avoids recomputing from scratch for each new selection.

Algorithms:
- Union-Find (Disjoint Set Union) with path compression
- Sorting elements in decreasing order
- Greedy merging of adjacent valid segments

Time Complexity: O(n log n)
Space Complexity: O(n)

"""

import sys
from operator import itemgetter

input = sys.stdin.readline
rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))


def solve():
    n, a = rn(), rl()
    # Sort elements by value in descending order along with their indices
    b = sorted([(a[i], i) for i in range(n)], key=itemgetter(0), reverse=True)
    max_val = b[0][0]  # Maximum value in the array
    fa, node = list(range(n)), [None] * n  # Union-Find parent array and node info storage
    get_size = lambda node: node[3] - node[2] + 1  # Calculate size of a segment (node info)
    contain_even_count, current_cnt, res = 0, 0, 0  # Counters for tracking results

    def contain_even(node):
        # Check if a node contains 'even' segments based on max even/odd flags
        even_max, odd_max, l, r, _ = node
        return (even_max and ~(l & r) & 1) or (odd_max and (l | r) & 1)

    def find(x):
        # Find root with path compression
        if fa[x] != x:
            fa[x] = find(fa[x])
            return fa[x]
        else:
            return x

    def merge(x, y):
        nonlocal contain_even_count, current_cnt
        fx, fy = find(x), find(y)
        if fx == fy:
            return
        # Ensure fx is the smaller group to optimize merging
        if node[fx][4] > node[fy][4]:
            fx, fy = fy, fx
        fa[fx] = fy  # Merge smaller group into larger one
        node_fx, node_fy = node[fx], node[fy]
        even_max_fx, odd_max_fx, l_fx, r_fx, res_fx = node_fx
        even_max_fy, odd_max_fy, l_fy, r_fy, res_fy = node_fy
        # Update merged node properties
        node[fy] = (
            even_max_fx or even_max_fy,
            odd_max_fx or odd_max_fy,
            min(l_fx, l_fy),
            max(r_fx, r_fy),
            (max(r_fx, r_fy) - min(l_fx, l_fy) + 2) >> 1,
        )
        # Update even count and total current count
        contain_even_count += (
            contain_even(node[fy]) - contain_even(node_fx) - contain_even(node_fy)
        )
        current_cnt += node[fy][4] - res_fx - res_fy

    for v, i in b:
        if v == max_val:
            # Initialize node for maximum value with special even property
            node[i] = (~i & 1, i & 1, i, i, 1)
            contain_even_count += 1
        else:
            # Initialize node for other values
            node[i] = (False, False, i, i, 1)
        current_cnt += 1  # Count the inclusion of this element
        # Try to merge with left neighbor if valid
        if i > 0 and a[i - 1] >= v and node[i - 1]:
            merge(i - 1, i)
        # Try to merge with right neighbor if valid
        if i < n - 1 and a[i + 1] >= v and node[i + 1]:
            merge(i, i + 1)
        # Update global result
        res = max(res, current_cnt + v + max_val - (contain_even_count == 0))
    print(res)


[solve() for _ in range(rn())]


# https://github.com/VaHiX/codeForces/