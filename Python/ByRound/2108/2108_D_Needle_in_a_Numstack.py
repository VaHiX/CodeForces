# Problem: CF 2108 D - Needle in a Numstack
# https://codeforces.com/contest/2108/problem/D

"""
D. Needle in a Numstack

Problem Description:
We are given two arrays A and B, each with at least k elements, where all elements are in range [1,k].
Each array has the property that any k consecutive elements are distinct.
These arrays are concatenated into one array C of length n.
We must determine the lengths of A and B by querying elements of C,
using at most 250 queries per test case.

Approach:
- Utilize the constraint that no k consecutive elements in either array are equal.
- Query specific indices to identify where the "breakpoint" between arrays A and B is.
- If n = 2k, we directly return [k,k].
- Otherwise, we perform a series of queries in the first and last k elements to detect patterns.
- Use binary search or linear probing to identify the start index of array B.

Time Complexity: O(n/k * log(n/k) + k), where n/k is due to queries and the logarithmic factor from binary search.
Space Complexity: O(k) for storing temporary arrays and indices used in processing.

Algorithms/Techniques:
- Binary Search
- Interactive Problem Solving
"""

from sys import stdin

input = stdin.readline
inp = lambda: list(map(int, input().split()))


def ask(x):
    print("?", x, flush=True)
    return int(input())


def answer():
    if (2 * k) == n:
        return [k, k]
    perm = []
    for i in range(k):
        perm.append(ask(i + 1))
    perm_end = []
    for i in range(k):
        perm_end.append(ask(n - k + i + 1))
    d_point = n - k
    low, high = n - k, k
    for delta in range(k):
        ind = (n // k) * k + delta
        rightind = (k - 1) - (n - ind - 1) % k
        if perm[delta] == perm_end[rightind]:
            continue
        point = n - k
        l, h = 0, (n - delta - 1) // k
        while l <= h:
            mid = (l + h) // 2
            p = mid * k + delta
            value = ask(p + 1)
            leftind = p % k
            if value == perm[leftind]:
                l = mid + 1
            else:
                point = p
                h = mid - 1
        d_point = min(d_point, point)
        break
    for i in range(max(k, d_point - k), d_point):
        if ask(i + 1) != perm[i % k]:
            d_point = i
            break
    if d_point > k:
        value = ask(d_point + 1)
        for i in range(k):
            rightind = (k - 1) - (n - (d_point - 1) - 1) % k
            if value == perm[i] and perm_end[rightind] == ask(d_point):
                return [-1]
    return [d_point, n - d_point]


for T in range(int(input())):
    n, k = inp()
    print("!", *answer(), flush=True)


# https://github.com/VaHiX/codeForces/