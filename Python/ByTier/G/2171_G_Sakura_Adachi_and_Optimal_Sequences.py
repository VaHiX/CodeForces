# Problem: CF 2171 G - Sakura Adachi and Optimal Sequences
# https://codeforces.com/contest/2171/problem/G

"""
Algorithm: Optimal Sequence Operations for Array Transformation

This code solves the problem of finding the minimum number of operations to transform array `a` into array `b`,
where each operation can either increment an element of `a` by 1 or double all elements of `a`.

Approach:
1. For each element, compute the minimum number of doublings needed to get close to the target value.
2. Use bit operations to determine how many additions are needed at each bit level after the optimal number of doublings.
3. Count total operations (doublings + additions) and compute the number of valid sequences using combinatorics with modular arithmetic.

Time Complexity: O(n * log(max_val)) where max_val is up to 10^6, so effectively O(n)
Space Complexity: O(10^6) due to precomputed factorials and inverse factorials

The solution relies on:
- Binary representation to decompose differences
- Combinatorial counting using modular arithmetic
- Preprocessing factorials and their modular inverses for fast calculation
"""

MOD = 10**6 + 3
fact = [1] * MOD
for i in range(1, MOD):
    fact[i] = fact[i - 1] * i % MOD
anti = [1] * MOD
anti[-1] = pow(fact[-1], -1, MOD)
for i in range(MOD - 2, -1, -1):
    anti[i] = anti[i + 1] * (i + 1) % MOD

for _ in range(int(input())):
    n = int(input())
    a = [int(t) for t in input().split()]
    b = [int(t) for t in input().split()]

    md = 30
    for i in range(n):
        c = a[i]
        e = 0
        while 2 * c <= b[i]:
            c *= 2
            e += 1
        md = min(md, e)

    den = 1
    top = [0] * md
    bigs = 0
    for i in range(n):
        diff = b[i] - (a[i] << md)  # Left shift to simulate doubling `md` times
        for t in range(md):
            if (diff >> t) & 1:  # Check if t-th bit is set
                top[t] += 1
        ex = diff >> md  # Remaining value after removing `md` bits
        bigs += ex
        den = den * anti[ex] % MOD

    w = 0 if bigs >= MOD else fact[bigs] * den % MOD
    for e in top:
        w = w * fact[e] % MOD
    print(md + sum(top) + bigs, w)


# https://github.com/VaHiX/CodeForces/