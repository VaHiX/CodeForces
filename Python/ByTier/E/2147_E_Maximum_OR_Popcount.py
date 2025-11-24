# Problem: CF 2147 E - Maximum OR Popcount
# https://codeforces.com/contest/2147/problem/E

"""
E. Maximum OR Popcount
Purpose:
    Given an array of non-negative integers and multiple queries, each query allows
    performing at most 'b_i' operations (incrementing elements by 1). The goal is
    to maximize the number of bits equal to 1 in the bitwise OR of all numbers.
Algorithms:
    - For each bit position from high to low, calculate how much cost is needed to set that bit
      in the OR result. Greedily decide how many operations can be spent to gain set bits.
    - Use prefix/suffix techniques combined with bit manipulation and binary search principles.
Time Complexity: O(n * 32 + q * 32) where n is array size and q is number of queries
Space Complexity: O(1) excluding input storage and output arrays
"""

import sys
from bisect import bisect_right
from random import getrandbits

rand1 = getrandbits(32)
rand2 = getrandbits(32)
if rand1 == rand2:
    rand2 = 2**32 // rand2


class Wrap(int):
    def __init__(self, x):
        int.__init__(x)

    def __hash__(self):
        return super(Wrap, self).__hash__() ^ rand1 ^ rand2


def inp():
    return sys.stdin.readline().strip()


def inin(x=1):
    if not x:
        return not x
    if x == 1:
        return int(inp())
    else:
        return map(int, inp().split())


def intarr():
    return list(inin(2))


def chrarr():
    return list(inp().split())


def lines(m):
    lines = [""] * m
    for i in range(m):
        lines[i] = list(inp().split())
    return lines


def intlines(m):
    lines = [0] * m
    for i in range(m):
        lines[i] = intarr()
    return lines


def pr(*a, sep=" ", end="\n", **d):
    h = list(d.keys())
    print(*a, *h, sep=sep, end=end)


def no(*a):
    pr("NO", *a)


def yes(*a):
    pr("YES", *a)


def No(*a):
    pr("No", *a)


def Yes(*a):
    pr("Yes", *a)


def ali(*a):
    pr("Alice", *a)


def bob(*a):
    pr("Bob", *a)


def pas(*a):
    pr("PASS", *a)


def pref(x):
    y = x.copy()
    for i in range(1, len(x)):
        y[i] += y[i - 1]
    return y


def suff(x):
    return pref(x[::-1])[::-1]


def binexp(a, b, res=1, mod=0):
    while b:
        if b & 1:
            res *= a
        a *= a
        b >>= 1
        if mod:
            a %= mod
            res %= mod
    return res


def test(t):
    while t:
        solve(t)
        t -= 1


def solve(t):
    n, q = inin(2)
    A = intarr()
    b = [inin() for _ in range(q)]
    res = [0] * 32
    corr = [0] * (32)
    z = 0
    for x in A:
        z |= x
    bit = 1 << 32
    cnt = 0
    for i in range(32, 0, -1):
        if z & bit:
            cnt += 1
        corr[i - 1] = cnt
        bit //= 2
    # Precompute the cost to set each bit level
    for i in range(32):
        a = A.copy()
        bit = 1 << i
        ans = 0
        for j in range(i, -1, -1):
            m = bit
            # Find minimum number of increments to get current power of two
            for x in a:
                m = max(min(bit - (x & (bit * 2 - 1)), m), 0)
            ans += m
            # Apply the increment to the first element matching required condition
            for k, x in enumerate(a):
                if bit - (x & (2 * bit - 1)) == m:
                    a[k] += m
                    break
            bit //= 2
        res[i] = ans
    # Binary search on prefix sums to find the best answer for each query
    for x in b:
        z = bisect_right(res, x)
        pr(z + corr[z])


test(inin(1))


# https://github.com/VaHiX/CodeForces/