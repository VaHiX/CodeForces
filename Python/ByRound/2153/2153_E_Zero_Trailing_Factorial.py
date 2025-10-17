# Problem: CF 2153 E - Zero Trailing Factorial
# https://codeforces.com/contest/2153/problem/E

"""
Problem: E. Zero Trailing Factorial

This code computes the sum of f_m(x, n) over all positive integers x less than n,
where f_m(a, b) is defined as the minimum weight of the pair (a, b) with respect to k,
taken over all integers k with 2 <= k <= m.

Algorithm:
1. Precompute primes up to max_m using Sieve of Eratosthenes.
2. For each test case:
   - For each x from 1 to n-1, compute f_m(x, n)
   - This involves finding the minimal weight across all k in [2, m]
   - Weight is defined as min(v_k(x!), v_k(n!)) if they differ, else 10^100
   - v_k(x!) = min_i(v_{p_i}(x!)/e_i) where k = product(p_i^e_i) is prime factorization

Time Complexity:
- Sieve: O(M log log M) where M = max_m
- For each test case: O(n * pi(M) * log M) where pi(M) is number of primes <= M
- Total: O(T * n * pi(M) * log M) for T test cases

Space Complexity: O(M + n) for sieve and intermediate storage
"""

import sys
import threading
from collections import defaultdict


def sieve_primes(limit):
    # Sieve of Eratosthenes to find all primes up to limit
    sieve = bytearray(b"\x01") * (limit + 1)
    sieve[0:2] = b"\x00\x00"
    primes = []
    for i in range(2, limit + 1):
        if sieve[i]:
            primes.append(i)
            step = i
            start = i * i
            if start > limit:
                continue
            sieve[start : limit + 1 : step] = b"\x00" * (((limit - start) // step) + 1)
    return sieve, primes


def v_p_of_factorial(n, p):
    # Compute v_p(n!) = sum_{j=1}^infty floor(n/p^j)
    cnt = 0
    pw = p
    while pw <= n:
        cnt += n // pw
        pw *= p
    return cnt


def factorize(num, primes):
    # Factorize num using precomputed primes and return prime-power pairs
    res = []
    tmp = num
    for p in primes:
        if p * p > tmp:
            break
        if tmp % p == 0:
            c = 0
            while tmp % p == 0:
                tmp //= p
                c += 1
            res.append((p, c))
    if tmp > 1:
        res.append((tmp, 1))
    return res


def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    tests = []
    max_m = 0
    max_n = 0
    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        tests.append((n, m))
        if m > max_m:
            max_m = m
        if n > max_n:
            max_n = n
    limit = max_m
    sieve, primes = sieve_primes(limit)
    out_lines = []
    for n, m in tests:
        L = n
        ppos = L
        while ppos >= 2 and not sieve[ppos]:
            ppos -= 1
        if ppos < 2:
            out_lines.append("0")
            continue
        P = ppos
        if P >= n:
            out_lines.append("0")
            continue
        exponents = defaultdict(int)
        vpf_cache = {}
        total = 0
        for a in range(n - 1, P - 1, -1):
            num_to_add = a + 1
            fac = factorize(num_to_add, primes)
            for pr, cnt in fac:
                exponents[pr] += cnt
            best = None
            for pr, exp_in_D in exponents.items():
                if pr in vpf_cache:
                    B = vpf_cache[pr]
                else:
                    B = v_p_of_factorial(n, pr)
                    vpf_cache[pr] = B
                A = B - exp_in_D
                pe = pr
                e = 1
                while pe <= m:
                    fa = A // e
                    fb = B // e
                    if fa != fb:
                        cand = fa if fa < fb else fb
                        if best is None or cand < best:
                            best = cand
                            if best == 0:
                                break
                    e += 1
                    pe *= pr
                if best == 0:
                    break
            if best is None:
                best = 0
            total += best
        out_lines.append(str(total))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    threading.Thread(target=solve).start()


# https://github.com/VaHiX/CodeForces/