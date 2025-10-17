# Problem: CF 2120 C - Divine Tree
# https://codeforces.com/contest/2120/problem/C

"""
C. Divine Tree

Purpose:
This code constructs a rooted tree with n nodes such that the sum of divineness (d(i)) over all nodes equals m.
Divineness of a node is defined as the smallest label on the path from root to that node.
The approach uses binary search to determine the root node and then builds the tree structure accordingly.

Algorithms/Techniques:
- Binary search on the root node value
- Tree construction with specific edge assignments based on the root and remaining sum

Time Complexity: O(n log n) per test case, due to binary search over possible roots (log n) and tree construction (n)
Space Complexity: O(n), for storing the output edges

Input:
- t: number of test cases
- For each test case, n (number of nodes) and m (target sum of divineness)

Output:
- If impossible, print -1
- Otherwise, print root node followed by n-1 edges forming the tree
"""

import sys

input = lambda: sys.stdin.readline().strip()
t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    if k < n or k > (n * (n + 1) // 2):  # Early exit if impossible
        print(-1)
        continue
    lo = 0
    hi = n
    while lo + 1 < hi:
        m = lo + (hi - lo) // 2
        w = m + (m * (m - 1) // 2) + m * (n - m)  # Compute total divineness for root m
        if w >= k:
            hi = m
        else:
            lo = m
    rt = hi  # Root of the tree
    o = []
    o.append(str(rt))
    w = rt + (rt * (rt - 1) // 2) + rt * (n - rt)
    rem = w - k  # Extra divineness to adjust
    for i in range(1, n + 1):
        if i == rt:
            continue
        if i < rt:
            o.append(f"{rt} {i}")  # Connect smaller nodes directly to root
        if i > rt:
            if i - rt <= rem:
                o.append(f"{rt-1} {i}")  # Adjust connection for balance
            else:
                o.append(f"{rt} {i}")
    print("\n".join(o))


# https://github.com/VaHiX/codeForces/