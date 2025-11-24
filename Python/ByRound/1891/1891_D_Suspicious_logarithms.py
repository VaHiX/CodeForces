# Problem: CF 1891 D - Suspicious logarithms
# https://codeforces.com/contest/1891/problem/D

"""
Algorithm: Preprocessing + Binary Search / Range Sum Query
Time Complexity: O(61 * log(10^18) + q * log(n)) where n ~ 61*61*2 = 7322
Space Complexity: O(7322) for storing x and y arrays

The problem involves computing the sum of g(k) for k in [l, r] for multiple queries.
We define:
- f(x) = floor(log2(x)) — largest power of 2 not exceeding x
- g(x) = floor(log_{f(x)}(x)) — largest z such that (f(x))^z <= x

The key idea is to precompute ranges where g(x) is constant by analyzing how f(x) changes
and calculating for which values of x the value g(x) remains the same.

We process all possible combinations of f(x) and its logarithm base to determine
where g(x) is constant across intervals. These intervals are stored in arrays x and y,
where x contains start points of ranges and y contains the corresponding g(x) values.

Then for each query [l, r], we compute sum of g(x) in that range by using
the precomputed intervals and inclusion-exclusion principle.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
q = int(input())
mod = pow(10, 9) + 7
pow2 = [1]
for _ in range(61):
    pow2.append(2 * pow2[-1])  # Precompute powers of 2 up to 2^61

x = []
y = []

# Preprocessing stage: for each base f(x) = i, compute intervals where g(x) = c
for i in range(2, 61):  # for each possible value of f(x) from 2 to 60
    l, r = pow2[i], pow2[i + 1]  # range [2^i, 2^(i+1))
    l0, r0 = 1, i  # base i, initial exponent range [1, i)
    c = 0  # current g(x) value being considered
    
    while l0 < r:  # while the left bound of exponent is below right
        l1, r1 = max(l, l0), min(r, r0)  # intersection with [2^i, 2^(i+1))
        if l1 < r1:  # if there is an overlap
            x.append(l1)  # store start of interval
            y.append(c)  # store corresponding g(x) value
        l0 *= i  # expand lower bound of exponent by factor i
        r0 *= i  # expand upper bound of exponent by factor i
        c += 1   # increment g(x) value

ans = []

# Process queries
for _ in range(q):
    l, r = map(int, input().split())  # read query bounds
    r += 1  # extend to [l, r] inclusive
    ans0 = 0  # initialize answer for current query
    
    # Iterate through precomputed intervals
    for i in range(len(x) - 1):  # for all but last interval
        l1, r1 = max(l, x[i]), min(r, x[i + 1])  # compute intersection
        if l1 < r1:  # if there's overlap
            ans0 += (r1 - l1) % mod * y[i]  # multiply interval length by g(x) value
    
    ans0 %= mod  # take modulo to avoid overflow
    ans.append(ans0)  # store result

sys.stdout.write("\n".join(map(str, ans)))  # output results


# https://github.com/VaHiX/CodeForces/