# Problem: CF 1743 F - Intersection and Union
# https://codeforces.com/contest/1743/problem/F

"""
Code Purpose:
This code solves a problem involving computing the sum of sizes of set operations (union, intersection, symmetric difference) over all possible combinations of operations on a collection of segments. It uses a segment tree to efficiently compute how many points are covered by each segment, and then applies dynamic programming to accumulate the result.

Algorithms/Techniques:
- Segment Tree: To manage and query overlapping intervals efficiently.
- Dynamic Programming: To compute the contribution of each segment based on previous results.
- Modular Arithmetic: To handle large numbers and prevent overflow.

Time Complexity: O(n log(max_range)) where n is the number of segments and max_range is the maximum coordinate value.
Space Complexity: O(max_range) for the segment tree storage.
"""

import sys

idx = 0


def build_tree(l, r):
    global idx, L, R, left, right, cnt
    i = idx
    idx += 1
    L.append(l)
    R.append(r)
    left.append(None)
    right.append(None)
    cnt.append(r - l + 1)

    if l < r:
        c = (l + r) // 2
        left[i] = build_tree(l, c)
        right[i] = build_tree(c + 1, r)

    return i


def update(t, l, r):
    # Function updates the segment tree by marking covered intervals
    global cnt

    if (l == L[t]) and (r == R[t]):
        # If the interval exactly matches the node interval, mark it as covered and return its count
        c = cnt[t]
        cnt[t] = 0
        return c

    if cnt[t] == 0:
        # If node has no elements, return 0
        return 0

    sb = 0
    # Update left subtree if there's overlap
    if l <= R[left[t]]:
        sb += update(left[t], l, min(r, R[left[t]]))
    # Update right subtree if there's overlap
    if r >= L[right[t]]:
        sb += update(right[t], max(l, L[right[t]]), r)

    cnt[t] -= sb
    return sb


M = 998244353

input = sys.stdin.readline
t = 1

for _test_ in range(t):

    n = int(input())
    S = []

    l0 = 300001
    r0 = -1

    for i in range(n):
        l, r = map(int, input().split())
        if l < l0:
            l0 = l
        if r > r0:
            r0 = r

        S.append([l, r])

    L = []
    R = []
    left = []
    right = []
    cnt = []
    sub_upd = []
    idx = 0

    T = build_tree(l0, r0)

    upd = [0] * n
    for i in range(n):
        j = n - i - 1
        # Process segments in reverse order, updating tree and recording covered points
        upd[j] = update(T, S[j][0], S[j][1])

    R = upd[0]
    f = 1

    for i in range(1, n):
        # Dynamic programming step to calculate contribution of each segment
        R = (2 * R) % M
        R = (R + upd[i] * 2 * f) % M
        f = (f * 3) % M

    print(R)


# https://github.com/VaHiX/CodeForces/