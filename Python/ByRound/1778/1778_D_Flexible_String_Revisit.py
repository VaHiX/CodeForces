# Problem: CF 1778 D - Flexible String Revisit
# https://codeforces.com/contest/1778/problem/D

"""
Purpose: This code solves the problem of finding the expected number of moves to make two binary strings equal,
         where each move flips a random character in string `a`. The solution uses dynamic programming and
         mathematical expectations involving probability and combinatorics.
         
Algorithms/Techniques:
    - Dynamic Programming (DP) for calculating expected values
    - Modular arithmetic with precomputed factorials and inverse factorials
    - Recurrence relations based on the number of differing bits
    
Time Complexity: O(n), where n is the length of the strings, due to linear DP and precomputation
Space Complexity: O(n), for storing arrays E0, E1, and precomputed factorials
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]

mod = 998244353
M = (10**6) + 10
fac = [1] * M
ninv = [1] * M
finv = [1] * M
for i in range(2, M):
    fac[i] = fac[i - 1] * i % mod
    ninv[i] = (-(mod // i) * ninv[mod % i]) % mod
    finv[i] = finv[i - 1] * ninv[i] % mod


def binom(n, k):
    if n < 0 or k < 0:
        return 0
    if k > n:
        return 0
    return (fac[n] * finv[k] % mod) * finv[n - k] % mod


def solve():
    n = int(input())
    a = input()
    b = input()
    cnt = 0
    for i in range(n):
        if a[i] != b[i]:
            cnt += 1

    E0 = [0] * (n + 1)
    E1 = [0] * (n + 1)
    E1[1] = 1
    for i in range(2, n + 1):
        # Probability of reaching state with i differences
        p = n * ninv[n - i + 1] % mod
        # Compute E0[i] using recurrence relation
        E0[i] = E0[i - 1] - 1 - (i - 1) * ninv[n] % mod * E0[i - 2]
        E0[i] = E0[i] % mod * p % mod
        # Compute E1[i] using recurrence relation
        E1[i] = E1[i - 1] - (i - 1) * ninv[n] % mod * E1[i - 2]
        E1[i] = E1[i] % mod * p % mod

    # Calculate e1 using derived formula from recurrence relations
    e1 = (1 + E0[n - 1] - E0[n]) * ninv[(E1[n] - E1[n - 1]) % mod] % mod

    # Final expected value for cnt differing bits
    ans = E0[cnt] + E1[cnt] * e1
    print(ans % mod)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/