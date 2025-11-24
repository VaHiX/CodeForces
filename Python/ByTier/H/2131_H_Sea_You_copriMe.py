# Problem: CF 2131 H - Sea, You & copriMe
# https://codeforces.com/contest/2131/problem/H

"""
H. Sea, You & copriMe

Purpose:
This code finds four distinct indices (p, q, r, s) in an array such that gcd(a[p], a[q]) == 1 and gcd(a[r], a[s]) == 1.

Algorithms/Techniques Used:
- Sieve of Eratosthenes-like algorithm to precompute smallest prime factors (spf) and Mobius function values.
- For each element, compute all divisors using prime factorization.
- Use inclusion-exclusion principle via Mobius function for fast coprimality counting.
- Greedy selection of pairs with gcd = 1 based on frequency-based counting.

Time Complexity:
O(m * log(log(m)) + sum(n)) where m is the maximum value in input array and sum(n) is total elements over all test cases.

Space Complexity:
O(m + sum(n)) for storing spf, mu arrays and auxiliary data structures.

Note: The key idea is to avoid checking all pairs O(n^2), instead use optimized counting through divisors and inclusion-exclusion using Mobius function.
"""

import sys
from math import gcd

data = list(map(int, sys.stdin.buffer.read().split()))
it = iter(data)
t = next(it)
tests = []
max_m = 1
for _ in range(t):
    n = next(it)
    m = next(it)
    a = [next(it) for _ in range(n)]
    tests.append((n, m, a))
    if m > max_m:
        max_m = m

# Precompute smallest prime factor and mobius function using sieve
spf = [0] * (max_m + 1)
mu = [0] * (max_m + 1)
mu[1] = 1
primes = []
for i in range(2, max_m + 1):
    if spf[i] == 0:
        spf[i] = i
        primes.append(i)
        mu[i] = -1
    for p in primes:
        v = i * p
        if v > max_m:
            break
        spf[v] = p
        if i % p == 0:
            mu[v] = 0
            break
        else:
            mu[v] = -mu[i]

def uniq_primes(x: int):
    ps = []
    while x > 1:
        p = spf[x]
        ps.append(p)
        while x % p == 0:
            x //= p
    return ps

def sf_divs_from_primes(ps):
    res = [1]
    for p in ps:
        res += [d * p for d in res]
    return res

out_lines = []
for n, m, a in tests:
    M = max(a)
    freq = [0] * (M + 1)
    for v in a:
        freq[v] += 1
    cntDiv = [0] * (M + 1)
    for d in range(1, M + 1):
        s = 0
        step = d
        for x in range(d, M + 1, step):
            s += freq[x]
        cntDiv[d] = s
    
    pf_cache = {}
    sfdiv_cache = {}

    def sf_divs_of_val(x: int):
        if x not in sfdiv_cache:
            if x not in pf_cache:
                pf_cache[x] = uniq_primes(x)
            sfdiv_cache[x] = sf_divs_from_primes(pf_cache[x])
        return sfdiv_cache[x]

    def coprime_count_idx(i: int) -> int:
        """Number of UNUSED partners coprime to a[i]."""
        s = 0
        for d in sf_divs_of_val(a[i]):
            s += mu[d] * cntDiv[d]
        if a[i] == 1:
            s -= 1
        return s

    used = [False] * n

    def remove_idx(i: int):
        used[i] = True
        for d in sf_divs_of_val(a[i]):
            cntDiv[d] -= 1

    def find_any_pair():
        """Find any (i, j) with gcd(a[i], a[j]) == 1 among UNUSED indices."""
        for i in range(n):
            if used[i]:
                continue
            if coprime_count_idx(i) <= 0:
                continue
            ai = a[i]
            for j in range(n):
                if i != j and (not used[j]) and gcd(ai, a[j]) == 1:
                    return (i, j)
        return None

    p1 = find_any_pair()
    if p1 is None:
        out_lines.append("0")
        continue
    i0, j0 = p1
    remove_idx(i0)
    remove_idx(j0)
    p2 = find_any_pair()
    if p2 is not None:
        i, j = p1
        k, l = p2
        out_lines.append(f"{i+1} {j+1} {k+1} {l+1}")
        continue

    remaining = [k for k in range(n) if not used[k]]
    Ni = [k for k in remaining if gcd(a[i0], a[k]) == 1]
    Nj = [k for k in remaining if gcd(a[j0], a[k]) == 1]
    if not Ni or not Nj:
        out_lines.append("0")
        continue
    if len(Ni) >= 2:
        y = Nj[0]
        x = Ni[0] if Ni[0] != y else Ni[1]
        out_lines.append(f"{i0+1} {x+1} {j0+1} {y+1}")
    elif len(Nj) >= 2:
        x = Ni[0]
        y = Nj[0] if Nj[0] != x else Nj[1]
        out_lines.append(f"{i0+1} {x+1} {j0+1} {y+1}")
    else:
        if Ni[0] != Nj[0]:
            out_lines.append(f"{i0+1} {Ni[0]+1} {j0+1} {Nj[0]+1}")
        else:
            out_lines.append("0")

print("\n".join(out_lines))


# https://github.com/VaHiX/codeForces/