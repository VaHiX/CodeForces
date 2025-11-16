# Problem: CF 1747 E - List Generation
# https://codeforces.com/contest/1747/problem/E

"""
Algorithm: Dynamic Programming with Combinatorics and Modular Arithmetic

This problem is about counting the sum of lengths of all "good" pairs of arrays (a, b) such that:
- Both arrays have the same length k >= 2
- a[0] = 0, a[k-1] = n
- b[0] = 0, b[k-1] = m
- Each element in arrays is non-decreasing
- The sum a[i] + b[i] is unique for each step (a[i] + b[i] != a[i-1] + b[i-1])

Approach:
- Use dynamic programming and combinatorics
- For fixed k, the number of valid pairs of length k is related to Catalan numbers
- The recurrence relation involves:
    - binomial coefficients (C_n^x and C_m^x)
    - Powers of 2
    - Modular inverse for division
- Time complexity: O(max(n,m)) per test case
- Space complexity: O(max(n,m))

"""

MOD = 10**9 + 7


def modulo(up_to):
    """Compute modular inverses up to 'up_to' using extended Euclidean algorithm."""
    inv = [0] * (up_to + 1)
    if up_to >= 1:
        inv[1] = 1
    for i in range(2, up_to + 1):
        inv[i] = MOD - (MOD // i) * inv[MOD % i] % MOD
    return inv


def solve():
    t = int(input())
    tests = []
    maxk = 0
    for _ in range(t):
        n, m = map(int, input().split())
        tests.append((n, m))
        k = min(n, m)
        if k > maxk:
            maxk = k
    inv = modulo(maxk + 1)
    inv2 = (MOD + 1) // 2  # Modular inverse of 2 mod MOD
    for n, m in tests:
        k = min(n, m)

        Cn = 1  # Binomial coefficient C(n, x)
        Cm = 1  # Binomial coefficient C(m, x)
        pow2 = pow(2, n + m - 1, MOD)  # 2^(n+m-1) mod MOD
        ans = 0
        for x in range(0, k + 1):
            term = (Cn * Cm) % MOD  # product of two binomials
            t_val = n + m - x
            f_t0 = pow2 * ((t_val + 3) % MOD) % MOD  # Precomputed term
            f_t0 = f_t0 * inv2 % MOD  # divide by 2 using modular inverse
            add = (f_t0 + pow2 * (x % MOD)) % MOD  # Final term to add
            ans = (ans + term * add) % MOD  # accumulate result
            if x < k:
                # Update binomial coefficients for next iteration
                denom_inv = inv[x + 1]
                Cn = (Cn * (n - x)) % MOD
                Cn = (Cn * denom_inv) % MOD
                Cm = (Cm * (m - x)) % MOD
                Cm = (Cm * denom_inv) % MOD
                pow2 = pow2 * inv2 % MOD  # Update power of 2
        print(ans)


solve()


# https://github.com/VaHiX/CodeForces/