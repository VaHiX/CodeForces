# Problem: CF 2056 E - Nested Segments
# https://codeforces.com/contest/2056/problem/E

"""
Algorithm: Dynamic Programming with Catalan Numbers
Time Complexity: O(n log n) per test case due to sorting and processing
Space Complexity: O(n) for storing segments, stack and precomputed factorials

This solution handles the problem of finding the number of ways to add maximum 
segments to a good set of segments while keeping it good. The approach uses:
1. Sorting segments by left endpoint and right endpoint (descending)
2. Using a stack to process segments and determine valid intervals
3. Computing the number of valid ways using Catalan numbers for each interval

The key insight is that valid additions form intervals, and the number of valid 
configurations for an interval of size k is the k-th Catalan number.
"""

import sys

input = lambda: sys.stdin.readline().strip()
sys.setrecursionlimit(1000000)
N = 400005
mod = 998244353
fac = [0] * N
inv = [0] * N
p = [[0 for _ in range(3)] for _ in range(N)]


def qpow(a, b, c):
    """Fast exponentiation: compute a^b mod c"""
    ans = 1
    while b:
        if b & 1:
            ans = ans * a % c
        b >>= 1
        a = a * a % c
    return ans


def init():
    """Precompute factorials and inverse factorials for combinations"""
    fac[0] = 1
    for i in range(1, N):
        fac[i] = fac[i - 1] * i % mod
    inv[N - 1] = qpow(fac[N - 1], mod - 2, mod)
    for i in range(N - 2, 0, -1):
        inv[i] = inv[i + 1] * (i + 1) % mod


def C(x, y):
    """Compute combination C(x,y) mod mod"""
    return fac[x] * inv[y] % mod * inv[x - y] % mod


def cat(x):
    """Compute x-th Catalan number mod mod"""
    if x <= 1:
        return 1
    return C(2 * x, x) * qpow(x + 1, mod - 2, mod) % mod


def solve():
    n, m = map(int, input().split())
    ok = 0
    for i in range(1, m + 1):
        p[i][0], p[i][1] = map(int, input().split())
        p[i][2] = p[i][1] - p[i][0] + 1
        if p[i][2] == n:
            ok = 1
    stk = []
    p[0][0] = 1
    p[0][1] = n
    p[0][2] = n
    if ok == 0:
        stk.append(0)
    p[1 : m + 1] = sorted(p[1 : m + 1], key=lambda x: (x[0], -x[1]))
    for i in range(1, m + 1):
        l = p[i][0]
        r = p[i][1]
        p[i][2]  # Placeholder - we don't use this value directly, but keep it for indexing
        while stk and l >= p[stk[-1]][1]:
            stk.pop()
        if stk:
            p[stk[-1]][2] -= r - l  # Reduce size of parent interval by the size of current segment
        stk.append(i)
    ans = 1
    st = 1
    if ok == 0:
        st = 0
    for i in range(st, m + 1):
        ans = ans * cat(p[i][2] - 1) % mod  # For each interval, multiply by its Catalan number
    print(ans)
    return


def main():
    t = 1
    t = int(input())
    init()
    for i in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/