# Problem: CF 2169 F - Subsequence Problem
# https://codeforces.com/contest/2169/problem/F

"""
Author: Rahul Samant
Created: 2025-11-14 21:03:41

Problem: Count the number of perfect arrays of length n containing integers from 1 to m.
A perfect array contains every beautiful subsequence as a subsequence.
Beautiful subsequence is an array where each element comes from corresponding array a_i.

Approach:
1. Enumerate all possible beautiful arrays, which are k-tuples where each element comes from array a_i.
2. Find the minimal set of positions that must be filled to accommodate all beautiful arrays as subsequences.
3. The number of valid arrays is the number of ways to complete remaining positions while satisfying the constraints.

The problem is modeled as a convolution of generating functions.
Time Complexity: O(k * n^2 * log n)
Space Complexity: O(n^2)

Algorithms/Techniques:
- NTT (Number Theoretic Transform) for fast polynomial multiplication
- Generating functions
- Inclusion-exclusion principle

"""

import os
import sys

MOD = 998244353
PRIMITIVE_ROOT = 3


DEBUG = os.path.exists("input.txt")


def debug(*args):
    if DEBUG:
        print("[DEBUG]", *args, file=sys.stderr)


try:
    input_data = iter(os.read(0, 10**7).decode().split())
except:
    input_data = iter(sys.stdin.read().split())

read = lambda: next(input_data)


def read_int():
    return int(read())


def read_ints(n=2):
    return tuple(int(read()) for _ in range(n))


def read_list(n):
    return [int(read()) for _ in range(n)]


def read_str():
    return read()


def read_strs(n):
    return [read() for _ in range(n)]


def read_matrix(n, m):
    return [read_list(m) for _ in range(n)]


def read_str_matrix(n):
    return [list(read()) for _ in range(n)]


def _mod_pow(base, exp):
    result = 1
    while exp:
        if exp & 1:
            result = result * base % MOD
        base = base * base % MOD
        exp >>= 1
    return result


def _ntt(a, invert):
    n = len(a)
    j = 0
    for i in range(1, n):
        bit = n >> 1
        while j & bit:
            j ^= bit
            bit >>= 1
        j ^= bit
        if i < j:
            a[i], a[j] = a[j], a[i]

    length = 2
    while length <= n:
        wlen = _mod_pow(PRIMITIVE_ROOT, (MOD - 1) // length)
        if invert:
            wlen = _mod_pow(wlen, MOD - 2)
        for i in range(0, n, length):
            w = 1
            half = length // 2
            for j in range(i, i + half):
                u = a[j]
                v = a[j + half] * w % MOD
                a[j] = (u + v) % MOD
                a[j + half] = (u - v + MOD) % MOD
                w = w * wlen % MOD
        length <<= 1

    if invert:
        inv_n = _mod_pow(n, MOD - 2)
        for i in range(n):
            a[i] = a[i] * inv_n % MOD


def _convolve(a, b, limit):
    if not a or not b:
        return []
    needed = min(limit + 1, len(a) + len(b) - 1)
    if needed <= 0:
        return []
    size = 1
    while size < len(a) + len(b) - 1:
        size <<= 1
    fa = a + [0] * (size - len(a))
    fb = b + [0] * (size - len(b))
    _ntt(fa, False)
    _ntt(fb, False)
    for i in range(size):
        fa[i] = fa[i] * fb[i] % MOD
    _ntt(fa, True)
    return fa[:needed]


def _negative_binomial_series(base, exponent, length, inverses):
    series = [0] * (length + 1)
    series[0] = 1
    if exponent == 0 or length == 0:
        return series
    base %= MOD
    for d in range(1, length + 1):
        series[d] = series[d - 1] * (exponent + d - 1) % MOD
        series[d] = series[d] * inverses[d] % MOD
        series[d] = series[d] * base % MOD
        if base == 0 and d >= 1:

            break
    return series


def solve():
    n = read_int()
    m = read_int()
    k = read_int()
    lengths = read_list(k)

    # Skip reading the actual arrays since we only need length counts
    for length in lengths:
        for _ in range(length):
            _ = read()

    total_length = sum(lengths)
    if total_length > n:
        print(0)
        return

    remaining = n - total_length
    if remaining < 0:
        print(0)
        return

    # cnt[r] holds number of arrays of length r
    cnt = [0] * 6
    for length in lengths:
        cnt[length] += 1

    # suf[h] is number of arrays of length >= h
    suf = [0] * 7
    for h in range(5, 0, -1):
        suf[h] = cnt[h] + suf[h + 1]

    # pref_factorial[r] = r!
    pref_factorial = [1, 1, 2, 6, 24, 120]
    multiplier = 1
    for r in range(1, 6):
        if cnt[r]:
            multiplier = multiplier * _mod_pow(pref_factorial[r], cnt[r]) % MOD

    if remaining == 0:
        print(multiplier)
        return

    # max_deg = remaining
    max_deg = remaining
    inverses = [0] * (max_deg + 1)
    if max_deg >= 1:
        inverses[1] = 1
        for i in range(2, max_deg + 1):
            inverses[i] = MOD - MOD // i * inverses[MOD % i] % MOD

    factors = []

    # First factor is (m^1)^(remaining) = m^remaining (this is to fill remaining slots with any of possible values)
    factors.append(_negative_binomial_series(m, 1, max_deg, inverses))
    
    # For each array length h, we have a factor (m-h)^suf[h] 
    # which accounts for choosing remaining elements from a specific set of h elements.
    for h in range(1, 6):
        exponent = suf[h]
        if exponent == 0:
            continue
        factors.append(_negative_binomial_series(m - h, exponent, max_deg, inverses))

    # Multiply all factors using convolution
    result = [1]
    current_limit = 0
    for series in factors:
        current_limit = min(max_deg, current_limit + len(series) - 1)
        result = _convolve(result, series, current_limit)
        if len(result) < current_limit + 1:
            result.extend([0] * (current_limit + 1 - len(result)))

    answer = multiplier * result[remaining] % MOD
    print(answer)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/