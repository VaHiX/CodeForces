# Problem: CF 1954 D - Colored Balls
# https://codeforces.com/contest/1954/problem/D

"""
Algorithm: Dynamic Programming + Combinatorics
Time Complexity: O(n * max(a_i) + n^2)
Space Complexity: O(max(a_i))

This solution computes the sum of minimum group values for all 2^n subsets of colors.
The key insight is to use dynamic programming on the number of groups needed,
and combine it with combinatorics to count how many subsets result in each group count.
"""

import sys
from itertools import accumulate

input = lambda: sys.stdin.readline().strip()
printerr = lambda *args, **kwargs: print(
    "\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs
)
MOD = 998244353
N = 5001
(*fac,) = accumulate(range(1, N + 1), lambda p, x: p * x % MOD, initial=1)
(*invfac,) = accumulate(
    range(N, 0, -1), lambda p, x: p * x % MOD, initial=pow(fac[-1], -1, MOD)
)
invfac.reverse()


def comb(n, k):
    return fac[n] * invfac[k] * invfac[n - k] % MOD


def main():
    n = int(input())
    a = sorted(map(int, input().split()))
    if n == 1:
        print(a[0])
        return
    M = max(a)
    dp = [0] * M
    dp[0] = 1
    o = sum(x % 2 for x in a)  # Count of odd-valued a[i]
    t = sum(a) * pow(2, n - 2, MOD) % MOD  # Base contribution from all subsets
    E = pow(2, n - o, MOD)  # 2^(n - number of odd values)
    s = 0
    # Sum up combinations of choosing odd number of odd values
    for i in range(1, o + 1, 2):
        s = (s + comb(o, i) * E) % MOD
    t = (t + s * pow(2, -1, MOD)) % MOD  # Add half of that weighted sum
    m = 0
    # For each color, update DP array and accumulate total
    for x in a:
        for i in range(min(M - 1 - x, m), x - 1, -1):
            dp[i + x] = (dp[i + x] + dp[i]) % MOD
        for i in range(min(x - 1, m), -1, -1):
            if i + x < M:
                dp[i + x] = (dp[i + x] + dp[i]) % MOD
            t = (t + dp[i] * (x - (i + x + 1) // 2)) % MOD
        m = min(M - 1, m + x)
    print(t)


main()


# https://github.com/VaHiX/CodeForces/