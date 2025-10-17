# Problem: CF 2140 E2 - Prime Gaming (Hard Version)
# https://codeforces.com/contest/2140/problem/E2

"""
E2. Prime Gaming (Hard Version)
Purpose:
This is a game theory problem involving combinatorial game theory and dynamic programming.
Each test case involves n piles of stones with values from 1 to m.
Players (Alice and Bob) alternate removing good-indexed piles until one remains.
Alice aims to maximize the final pile's value, Bob aims to minimize it.
The solution computes, for all valid configurations, the sum of possible final pile values.

Algorithms/Techniques:
- Game tree evaluation with memoization
- Sprague-Grundy theory or minimax
- Stirling numbers of the second kind
- Combinatorics and inclusion-exclusion principle

Time Complexity: O(n^2 * 2^n) per test case
Space Complexity: O(n * 2^n + n^2)

Input:
Each test contains multiple test cases. The first line contains the number of test cases t.
The first line of each testcase contains two integers n and m — the number of piles and the upper bound on the number of stones in a pile.
The second line of each testcase contains a single integer k — the number of indices marked as good.
The third line of each testcase contains k integers c1, c2, ..., ck — the good indices.

Output:
For each testcase, print a single integer — the sum of x over all the possible valid configurations modulo 10^9+7
"""

import sys

MOD = 10**9 + 7
innit = lambda: sys.stdin.readline().rstrip("\r\n")
t = int(innit())
MAXN = 80
MAXP = 2 * MAXN
C = [[0] * (MAXN + 1) for _ in range(MAXN + 1)]
for i in range(MAXN + 1):
    C[i][0] = C[i][i] = 1
    for j in range(1, i):
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD

S2 = [[0] * (MAXP + 1) for _ in range(MAXP + 1)]
S2[0][0] = 1
for n_ in range(1, MAXP + 1):
    for k_ in range(1, n_ + 1):
        S2[n_][k_] = (S2[n_ - 1][k_ - 1] + k_ * S2[n_ - 1][k_]) % MOD

MAXR = MAXP + 1
inv = [0] * (MAXR + 1)
inv[1] = 1
for i in range(2, MAXR + 1):
    inv[i] = MOD - MOD // i * inv[MOD % i] % MOD

baku = []
for _ in range(t):
    n, m = map(int, innit().split())
    k_good = int(innit())
    good_in = list(map(int, innit().split()))
    good = [0] * (n + 1)
    for g in good_in:
        good[g] = 1
    if m == 1:
        baku.append("1")
        continue
    A = [[] for _ in range(n + 1)]
    # Precompute good indices up to pile k
    for k in range(1, n + 1):
        Ak = []
        for i in range(1, k + 1):
            if good[i]:
                Ak.append(i)
        A[k] = Ak

    f_prev = [0, 1]
    # Build game state DP table using minimax approach
    for k in range(2, n + 1):
        size = 1 << k
        f_cur = [0] * size
        allowed = A[k]
        alice_turn = ((n - k) & 1) == 0  # Alice plays first and takes odd turn numbers
        if alice_turn:
            # If Alice's turn, she picks good pile to make child state win, else she must prevent a loss
            for mask in range(size):
                val = 0
                for i in allowed:
                    low = mask & ((1 << (i - 1)) - 1)
                    high = mask >> i
                    child = low | (high << (i - 1))
                    if f_prev[child]:
                        val = 1
                        break
                f_cur[mask] = val
        else:
            for mask in range(size):
                val = 1
                for i in allowed:
                    low = mask & ((1 << (i - 1)) - 1)
                    high = mask >> i
                    child = low | (high << (i - 1))
                    if not f_prev[child]:
                        val = 0
                        break
                f_cur[mask] = val
        f_prev = f_cur

    dp_k = [0] * (n + 1)
    # Count how many valid ending configurations have k stones
    if n == 1:
        dp_k[0] = 0 if f_prev[0] == 0 else 1
        dp_k[1] = 1 if f_prev[1] == 1 else 0
    else:
        for mask in range(1 << n):
            if f_prev[mask]:
                dp_k[mask.bit_count()] += 1

    max_r = 2 * n + 1
    fall = [1] * (max_r + 1)
    # Precompute falling factorials of m: m*(m-1)*...*(m-r+1)
    for r in range(1, max_r + 1):
        fall[r] = fall[r - 1] * (m - (r - 1)) % MOD

    P = [0] * (2 * n + 1)
    # Compute polynomial coefficients for Stirling-based combinatorics
    for p in range(0, 2 * n + 1):
        s = 0
        Sp = S2[p]
        for j in range(0, p + 1):
            s = (s + Sp[j] * (fall[j + 1] * inv[j + 1] % MOD)) % MOD
        P[p] = s

    powm = [1] * (n + 1)
    # Precompute m^e for fast power calculations
    for e in range(1, n + 1):
        powm[e] = powm[e - 1] * m % MOD

    S_k = [0] * (n + 1)
    # Apply inclusion-exclusion to compute final result with combinatorial factor
    for k in range(0, n + 1):
        tdeg = n - k
        s = 0
        for j in range(0, k + 1):
            term = C[k][j] * powm[k - j] % MOD
            if j & 1:
                term = MOD - term
            s = (s + term * P[j + tdeg]) % MOD
        S_k[k] = s

    # Final sum is total contribution of all valid k values using computed combinatorial terms
    ans = 0
    for k in range(0, n + 1):
        if dp_k[k]:
            ans = (ans + dp_k[k] * S_k[k]) % MOD
    baku.append(str(ans))

print(*baku)


# https://github.com/VaHiX/codeForces/