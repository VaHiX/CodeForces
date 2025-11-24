# Problem: CF 1954 F - Unique Strings
# https://codeforces.com/contest/1954/problem/F

"""
Algorithm: Computes the number of unique binary strings of length n with c 1s at the start
           and at most k 0s replaced with 1s, considering cyclic equivalence.

Approach: 
- Uses Burnside's lemma combined with inclusion-exclusion principle.
- Applies Euler's totient function to count distinct necklaces under rotation.
- For each divisor d of n, computes valid configurations of 1s and 0s that are
  distinct under cyclic shifts.
- Utilizes modular arithmetic and precomputed factorials and inverses for combinatorics.

Time Complexity: O(n * sqrt(n) + n * log(mod))
Space Complexity: O(n)

Techniques:
- Sieve of Euler for computing phi function
- Modular inverse using extended Euclidean algorithm
- Precomputed factorials and inverse factorials for combinations
- Inclusion-exclusion principle for counting valid rotations
"""

def solve(n, c, k, mod=10**9 + 7):
    """
    Compute the answer for given n, c, k according to the modified algorithm.
    Returns the result as an integer.
    """
    inv2 = (mod + 1) // 2
    f = [False] * (n + 1)
    phi = [0] * (n + 1)
    phi[1] = 1
    primes = []
    for i in range(2, n + 1):
        if not f[i]:
            phi[i] = i - 1
            primes.append(i)
        for p in primes:
            if i * p > n:
                break
            f[i * p] = True
            if i % p == 0:
                phi[i * p] = phi[i] * p
                break
            phi[i * p] = phi[i] * (p - 1)
    inv = [0] * (n + 1)
    inv[1] = 1
    for i in range(2, n + 1):
        inv[i] = mod - (mod // i) * inv[mod % i] % mod
    fac = [1] * (n + 1)
    ifac = [1] * (n + 1)
    for i in range(1, n + 1):
        fac[i] = fac[i - 1] * i % mod
        ifac[i] = ifac[i - 1] * inv[i] % mod

    def C(n_, k_):
        if n_ < k_ or k_ < 0:
            return 0
        return fac[n_] * ifac[k_] % mod * ifac[n_ - k_] % mod

    ans = 0
    for i in range(1, n + 1):
        if n % i:
            continue
        l, r = i - 1, i - 2
        sum_ = 0
        val = 1 if (c + k == n) else 0
        lim = min((c + k) // (n // i), i - 1)
        x, a = 1, i - c
        while x <= a and x <= i - c:
            for p in range(a + c, a - 1, -1):
                sum_ = (sum_ - C(p - x, l - 1) + C(p - x, r)) * inv2 % mod
            L = max(0, i - x - lim)
            R = i - x - c
            while l != L:
                l -= 1
                sum_ = (sum_ + C(a - x, l)) % mod
            while r != R:
                sum_ = (sum_ - C(a - x, r)) % mod
                r -= 1
            sign = 1 if (x & 1) else -1
            term = (C(a, x) + C(a - 1, x - 1) * c) % mod
            val = (val + sign * term * sum_) % mod
            x += 1
            a -= c
        ans = (ans + val * phi[n // i]) % mod
    ans = ans * ifac[n] % mod * fac[n - 1] % mod
    return (ans + mod) % mod


if __name__ == "__main__":
    import sys

    data = sys.stdin.readline().split()
    if len(data) >= 3:
        n, c, k = map(int, data[:3])
        print(solve(n, c, k))
    else:
        n, c, k = map(int, input().split())
        print(solve(n, c, k))


# https://github.com/VaHiX/CodeForces/