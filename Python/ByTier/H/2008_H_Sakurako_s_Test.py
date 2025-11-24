# Problem: CF 2008 H - Sakurako's Test
# https://codeforces.com/contest/2008/problem/H

"""
Algorithm: Preprocessing + Binary Search + Prefix Sum
Time Complexity: O(n * log(n) + q)
Space Complexity: O(n)

The solution uses a preprocessing step to calculate prefix sums of the array elements,
then for each query x, it computes the minimum possible median after performing
operations with value x. The key idea is that we can reduce any element >= x to
element % x, so we want to find the minimum median among all possible reductions.

The algorithm uses binary search on the possible median values, combined with prefix
sums to quickly calculate how many elements are less than or equal to a certain value
in the reduced array. The reduction process is optimized using modular arithmetic
and precomputed powers of 2 for efficient binary search.

Steps:
1. Count occurrences of each element (prefix sum construction)
2. For each possible divisor i, compute how many elements get reduced to values < i
3. For each query x, use precomputed answers for the minimum median when using x
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
t = int(input())
ans = []
pow2 = [1]
for _ in range(20):
    pow2.append(2 * pow2[-1])
for _ in range(t):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    cnt = [0] * (n + 1)
    for i in a:
        cnt[i] += 1
    for i in range(1, n + 1):
        cnt[i] += cnt[i - 1]
    m = (n + 2) >> 1
    ans1 = [0] * (n + 1)
    for i in range(2, n + 1):
        u = 0
        for j in range(i, n + 1, i):
            u += cnt[j - 1]
        ans0 = -1
        for p in pow2[::-1]:
            k = ans0 + p
            if k >= i - 1:
                continue
            v = 0
            for j in range(0, n + 1, i):
                v += cnt[n] if j + k > n else cnt[j + k]
            if v - u < m:
                ans0 = k
        ans1[i] = ans0 + 1
    ans0 = [0] * q
    for i in range(q):
        x = int(input())
        ans0[i] = ans1[x]
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/