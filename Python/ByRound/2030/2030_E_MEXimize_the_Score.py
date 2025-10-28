# Problem: CF 2030 E - MEXimize the Score
# https://codeforces.com/contest/2030/problem/E

"""
E. MEXimize the Score

Purpose:
This code computes the sum of scores over all non-empty subsequences of an array,
where each score is defined as the sum of MEX values of the multisets in a partition
of the subsequence into arbitrary number of non-empty multisets.

Algorithms/Techniques:
- Dynamic programming with inclusion-exclusion principle
- Preprocessing factorials and inverse factorials for combinatorial calculations
- Modular arithmetic with fast exponentiation and modular inverse

Time Complexity: O(n^2) per test case, where n is the size of the input array
Space Complexity: O(n) for storing precomputed values and DP arrays

"""

import sys

MOD = 998244353
MX = 2 * (10**5) + 1
p2 = [1] * (MX + 1)
for i in range(1, MX + 1):
    p2[i] = p2[i - 1] * 2 % MOD  # Precompute powers of 2 modulo MOD

fac = [0] * MX
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % MOD  # Precompute factorials modulo MOD

inv_fac = [0] * MX
inv_fac[MX - 1] = pow(fac[MX - 1], -1, MOD)  # Compute inverse factorial of last element
for i in range(MX - 1, 0, -1):
    inv_fac[i - 1] = inv_fac[i] * i % MOD  # Compute inverse factorials backwards


def C(n, k):
    """Compute combination C(n, k) modulo MOD."""
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD


def solve():
    line = sys.stdin.readline().split()
    n = int(line[0])
    line = sys.stdin.readline().split()
    cnt = [0] * n
    for x in line:
        cnt[int(x)] += 1  # Count frequency of each value in input array

    dp = [0] * (n + 1)
    dpn = [0] * (n + 1)
    ans, res, mi = 0, n, n
    dp[n] = 1  # Initial state for DP: one subset is possible at level n

    for x in range(n):
        if cnt[x] == 0:
            break  # If value x doesn't exist in input, stop processing
        res -= cnt[x]  # Decrement number of remaining elements to place
        s = sum(dp[1 : mi + 1]) % MOD  # Sum of current DP values up to minimum count
        mi = min(mi, cnt[x])  # Track the smallest count so far
        sn = p2[cnt[x]] - 1  # Calculate subset count for x (2^(cnt[x]) - 1)
        for i in range(1, mi + 1):
            # Recurrence relation: update dpn with new combinations and subtract overlaps
            dpn[i] = (dp[i] * sn + s * C(cnt[x], i) - dp[i] * C(cnt[x], i)) % MOD
            ans = (ans + i * dpn[i] * p2[res]) % MOD  # Accumulate final answer with contribution from this level
            s = (s - dp[i]) % MOD
            sn = (sn - C(cnt[x], i)) % MOD
        dp, dpn = dpn, dp  # Swap DP arrays for next iteration

    sys.stdout.write(str(ans) + "\n")


line = sys.stdin.readline().split()
T = int(line[0])
for t in range(T):
    solve()


# https://github.com/VaHiX/codeForces/