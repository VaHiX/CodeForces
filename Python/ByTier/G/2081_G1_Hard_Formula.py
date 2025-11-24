# Problem: CF 2081 G1 - Hard Formula
# https://codeforces.com/contest/2081/problem/G1

import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def factorization(n):
    res = []
    for p in prime:
        if n % p == 0:
            while n % p == 0:
                n //= p
            res.append(p)
    if n != 1:
        res.append(n)
    return res


def euler_phi(n):
    res = n
    for x in range(2, n + 1):
        if x**2 > n:
            break
        if n % x == 0:
            res = res // x * (x - 1)
            while n % x == 0:
                n //= x
    if n != 1:
        res = res // n * (n - 1)
    return res


def ind(b, n):
    res = 0
    while n % b == 0:
        res += 1
        n //= b
    return res


def isPrimeMR(n):
    if n == 1:
        return 0
    d = n - 1
    d = d // (d & -d)
    L = [2, 3, 5, 7, 11, 13, 17]
    if n in L:
        return 1
    for a in L:
        t = d
        y = pow(a, t, n)
        if y == 1:
            continue
        while y != n - 1:
            y = (y * y) % n
            if y == 1 or t == n - 1:
                return 0
            t <<= 1
    return 1


def findFactorRho(n):
    from math import gcd

    m = 1 << n.bit_length() // 8
    for c in range(1, 99):
        f = lambda x: (x * x + c) % n
        y, r, q, g = 2, 1, 1, 1
        while g == 1:
            x = y
            for i in range(r):
                y = f(y)
            k = 0
            while k < r and g == 1:
                ys = y
                for i in range(min(m, r - k)):
                    y = f(y)
                    q = q * abs(x - y) % n
                g = gcd(q, n)
                k += m
            r <<= 1
        if g == n:
            g = 1
            while g == 1:
                ys = f(ys)
                g = gcd(abs(x - ys), n)
        if g < n:
            if isPrimeMR(g):
                return g
            elif isPrimeMR(n // g):
                return n // g
            return findFactorRho(g)


def primeFactor(n):
    i = 2
    ret = {}
    rhoFlg = 0
    while i * i <= n:
        k = 0
        while n % i == 0:
            n //= i
            k += 1
        if k:
            ret[i] = k
        i += 1 + i % 2
        if i == 101 and n >= 2**20:
            while n > 1:
                if isPrimeMR(n):
                    ret[n], n = 1, 1
                else:
                    rhoFlg = 1
                    j = findFactorRho(n)
                    k = 0
                    while n % j == 0:
                        n //= j
                        k += 1
                    ret[j] = k

    if n > 1:
        ret[n] = 1
    if rhoFlg:
        ret = {x: ret[x] for x in sorted(ret)}
    return ret


def eratosthenes(n):
    res = [0 for i in range(n + 1)]
    prime = set([])
    for i in range(2, n + 1):
        if not res[i]:
            prime.add(i)
            for j in range(1, n // i + 1):
                res[i * j] = 1
    return prime


def solve(N):
    mod = 2**32 - 1

    if N <= 100:
        return brute(N)

    n = int(N**0.5)

    # Precompute prefix sums and counts for small numbers and large numbers
    small_cnt = [0] + [i - 1 for i in range(1, n + 1)]
    large_cnt = [0] + [N // i - 1 for i in range(1, n + 1)]
    small_sum = [0] + [(i * (i + 1) // 2 - 1) & mod for i in range(1, n + 1)]
    large_sum = [0] + [
        (((N // i) * (N // i + 1)) // 2 - 1) & mod for i in range(1, n + 1)
    ]

    prime = sorted(eratosthenes(n))
    # Process each prime to update counts and sums
    for idx, p in enumerate(prime):
        for i in range(1, n + 1):
            if p * p > N // i:
                break

            if i * p <= n:
                # Update large count and sum using sieve-like approach
                large_cnt[i] = (
                    large_cnt[i]
                    - large_cnt[i * p]
                    + small_cnt[min(N // (i * p), p - 1)]
                )
                large_cnt[i] &= mod
                large_sum[i] = (
                    large_sum[i]
                    - (large_sum[i * p] - small_sum[min(N // (i * p), p - 1)]) * p
                )
                large_sum[i] &= mod
            else:
                # Similar update for the case when i * p > n
                large_cnt[i] = (
                    large_cnt[i]
                    - small_cnt[N // (i * p)]
                    + small_cnt[min(N // (i * p), p - 1)]
                )
                large_cnt[i] &= mod
                large_sum[i] = (
                    large_sum[i]
                    - (small_sum[N // (i * p)] - small_sum[min(N // (i * p), p - 1)])
                    * p
                )
                large_sum[i] &= mod

        # Process the prefix from large to small
        for i in range(1, n + 1)[::-1]:
            if p * p > i:
                break

            small_cnt[i] = (
                small_cnt[i] - small_cnt[i // p] + small_cnt[min(i // p, p - 1)]
            )
            small_cnt[i] &= mod
            small_sum[i] = (
                small_sum[i] - (small_sum[i // p] - small_sum[min(i // p, p - 1)]) * p
            )
            small_cnt[i] &= mod

    # Helper function to compute F(n) for different ranges
    def F(n):
        if n * n <= N:
            return large_sum[n] - large_cnt[n]
        else:
            return small_sum[N // n] - small_cnt[N // n]

    # Use deque for breadth-first traversal of possible divisors
    deq = [(1, -1, 1, 1, 1)]
    res = 0

    while deq:
        n, pid, tmp_phi, a, b = deq.pop()

        if pid == -1:
            # Base case: process initial values
            res += F(1)
            for k in range(2, 100):
                L, R = 1, min(k * b // (k * b - a), N // n)

                if L < R:
                    res += small_sum[R] - small_cnt[R]
                    res &= mod
                else:
                    break

            for pid in range(len(prime)):
                p = prime[pid]
                if p * p <= N:
                    deq.append((p, pid, p - 1, p, p - 1))
                else:
                    break
            continue

        p = prime[pid]

        assert n * p <= N

        # Accumulate results using the formula
        res += (a // b) * tmp_phi * p
        res &= mod
        res += (a // b) * tmp_phi * (F(n) - (small_sum[p] - small_cnt[p]))
        res &= mod

        k = a // b + 1
        while True:

            L, R = p, min(k * b // (k * b - a), N // n)

            if L < R:
                res += tmp_phi * (
                    (small_sum[R] - small_cnt[R]) - (small_sum[p] - small_cnt[p])
                )
                res &= mod
                k += 1
            else:
                break

        # Continue traversal with updated state
        if n * p * p <= N:
            deq.append((n * p, pid, tmp_phi * p, a, b))

        for nxt_pid in range(pid + 1, len(prime)):
            q = prime[nxt_pid]
            if n * q * q <= N:
                deq.append((n * q, nxt_pid, tmp_phi * (q - 1), a * q, b * (q - 1)))
            else:
                break

    # Final calculation
    ans = N * (N + 1) // 2 - 1 - res

    return ans & (2**32 - 1)


def brute(n):
    res = 0
    for k in range(1, n + 1):
        res += k % euler_phi(k)
    return res % (2**32 - 1)


N = int(input())
print(solve(N))


# https://github.com/VaHiX/CodeForces/