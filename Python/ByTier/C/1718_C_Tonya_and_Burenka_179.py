# Problem: CF 1718 C - Tonya and Burenka-179
# https://codeforces.com/contest/1718/problem/C

"""
Algorithm: Segment Tree with Lazy Propagation for Range Updates
Time Complexity: O(n * sqrt(n) + q * sqrt(n) * log(n))
Space Complexity: O(n * sqrt(n))

This solution uses a segment tree to efficiently compute the maximum usefulness 
of a program for Burenka-179 after each update. The array is divided into segments 
based on the divisors of n. For each divisor d of n, we compute the sum of elements 
at positions i, i+d, i+2*d, ... for all valid i, and then multiply by d to get the 
usefulness for a program starting at position i with step size d.

The segment tree is built on top of these precomputed values to support efficient 
updates and queries.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def prime_factorize(n):
    ans = []
    for i in range(2, int(n ** (1 / 2)) + 1):
        while True:
            if n % i:
                break
            ans.append(i)
            n //= i
        if n == 1:
            break
    if not n == 1:
        ans.append(n)
    return ans


t = int(input())
ans = []
pow2 = [1]
for _ in range(25):
    pow2.append(2 * pow2[-1])
for _ in range(t):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    p = list(set(prime_factorize(n)))
    d = [n // i for i in p]
    d.sort()
    l = len(d)
    y, z = [], [0]
    for u in d:
        z.append(u + z[-1])
        for i in range(u):
            s = 0
            for j in range(i, n, u):
                s += a[j]
            s *= u
            y.append(s)
    m = len(y).bit_length()
    pm = pow2[m]
    ma = [0] * (2 * pm)
    for i in range(len(y)):
        ma[i + pm] = y[i]
    for i in range(pm - 1, 0, -1):
        ma[i] = max(ma[2 * i], ma[2 * i + 1])
    ans0 = ma[1]
    ans.append(ans0)
    for _ in range(q):
        p, x = map(int, input().split())
        p -= 1
        if x == a[p]:
            ans0 = ma[1]
            ans.append(ans0)
            continue
        c = x - a[p]
        a[p] = x
        for i in range(l):
            j = z[i] + p % d[i]
            y[j] += d[i] * c
            ma[j + pm] = y[j]
            j = (j + pm) // 2
            while j and ma[j] ^ max(ma[2 * j], ma[2 * j + 1]):
                ma[j] = max(ma[2 * j], ma[2 * j + 1])
                j //= 2
        ans0 = ma[1]
        ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/