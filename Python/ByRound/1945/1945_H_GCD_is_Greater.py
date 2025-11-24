# Problem: CF 1945 H - GCD is Greater
# https://codeforces.com/contest/1945/problem/H

"""
Algorithm: GCD vs Bitwise AND Game
Approach:
- Kirill wants to maximize GCD of red numbers and minimize bitwise AND of blue numbers.
- The key insight is to check if we can find two numbers such that their GCD is greater than the AND of remaining numbers + x.
- For each pair of numbers:
  - Compute their GCD
  - Estimate the bitwise AND of the rest (using bit counting)
- Use bit manipulation and precomputed counts to efficiently check conditions.

Time Complexity: O(n * log(max(a)) + n^2 * log(max(a)))
Space Complexity: O(n * log(max(a)))
"""

import sys
from math import gcd


def pr(i, j, a, n):
    print("YES")
    print(2, a[i], a[j])
    print(n - 2, end=" ")
    for k in range(n):
        v = a[k]
        if k != i and k != j:
            print(v, end=" ")
    print()


def number_of_trailing_zeros(i):
    i = ~i & (i - 1)
    if i <= 0:
        return i & 32
    n = 1
    if i > 1 << 16:
        n += 16
        i >>= 16
    if i > 1 << 8:
        n += 8
        i >>= 8
    if i > 1 << 4:
        n += 4
        i >>= 4
    if i > 1 << 2:
        n += 2
        i >>= 2
    return n + (i >> 1)


def solve():
    n, x = map(int, input().split())
    mx, an = 0, -1
    a = [int(x) for x in input().split()]
    C = [0] * 19
    for i in range(n):
        mx = max(mx, a[i])
        an &= a[i]
        j = a[i]
        while j:
            C[number_of_trailing_zeros(j)] += 1
            j &= j - 1
    sp = [False] * n
    bitw = mx.bit_length()
    u = (1 << bitw) - 1
    for i in range(n):
        v = a[i]
        j = v ^ u
        while j:
            p = number_of_trailing_zeros(j)
            if C[p] == n - 1 or C[p] == n - 2:
                sp[i] = True
                break
            j &= j - 1
    pos = [[] for _ in range(mx + 1)]
    cnt_bit = C[:bitw]
    for i in range(n):
        v = a[i]
        if not sp[i]:
            pos[v].append(i)
            continue
        for j in range(n):
            w = a[j]
            if j == i:
                continue
            g = gcd(v, w)
            or1 = 0
            for k in range(len(cnt_bit)):
                c = cnt_bit[k]
                if c - (v >> k & 1) - (w >> k & 1) == n - 2:
                    or1 |= 1 << k
            if g > or1 + x:
                pr(i, j, a, n)
                return
    ans = []
    for i in range(an + x + 1, mx + 1):
        ans.clear()
        for j in range(i, mx + 1, i):
            ans.extend(pos[j])
            if len(ans) > 1:
                pr(ans[0], ans[1], a, n)
                return
    print("NO")


input = sys.stdin.readline
write = sys.stdout.write
for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/