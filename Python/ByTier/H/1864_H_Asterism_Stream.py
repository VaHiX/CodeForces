# Problem: CF 1864 H - Asterism Stream
# https://codeforces.com/contest/1864/problem/H

"""
Problem: Asterism Stream
Algorithms/Techniques: Dynamic Programming, Modular Arithmetic, Binary Exponentiation
Time Complexity: O(log^2 n) per test case
Space Complexity: O(log n)

This code computes the expected number of operations to reach a value >= n,
where each operation either increments x by 1 or multiplies x by 2 with equal probability.
The solution uses a recurrence relation with dynamic programming and modular arithmetic to compute
the answer modulo 998244353.
"""

import sys

MOD = 998244353
I2 = (MOD + 1) // 2  # Modular inverse of 2


def power(x: int, n: int) -> int:
    # Fast exponentiation with modular arithmetic
    result = 1
    x %= MOD
    while n > 0:
        if n & 1:
            result = (result * x) % MOD
        x = (x * x) % MOD
        n >>= 1
    return result


def solve():
    n = int(input())
    # Edge case: if n <= 1, no moves needed
    if n <= 1:
        return 0
    
    f = [0] * 1000  # Dynamic programming array for storing values

    l, r = n, 2 * n - 2  # Initialize range for computation
    k, ans = 0, 0  # k tracks depth, ans accumulates partial results

    # Main loop to compute the expected value using dynamic programming
    while l > 1:
        r = l - 1  # Update right bound
        l = (l + 1) // 2  # Update left bound by halving
        d = 0

        # Iterate backwards to compute updated values
        for i in range(k, 0, -1):
            t_val = power(2, (1 << i) - 1)  # 2^(2^i - 1)
            inv = power(t_val - 1, MOD - 2)  # Modular inverse
            it = (f[i - 1] * inv) % MOD
            it = (it * I2) % MOD
            f[i] = MOD - it  # Store negative value to avoid negative mod
            d = (d + it * power(t_val, r + 1)) % MOD

        k += 1  # Increment level
        # Compute f[0] using accumulated values and previous ans
        f[0] = (d + power(I2, r + 1) * ((ans + MOD - 2 * k) % MOD)) % MOD
        ans = 2 * k  # Update ans for next iteration

        # Accumulate values from previous levels
        for i in range(k):
            power_val = power(power(2, 1 << i), l)
            ans = (ans + f[i] * power_val) % MOD

    return ans


def main():
    input_func = sys.stdin.readline
    t = int(input_func())
    for _ in range(t):
        print(solve())


if __name__ == "__main__":
    input = sys.stdin.readline
    main()


# https://github.com/VaHiX/CodeForces/