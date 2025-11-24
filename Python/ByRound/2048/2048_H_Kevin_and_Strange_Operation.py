# Problem: CF 2048 H - Kevin and Strange Operation
# https://codeforces.com/contest/2048/problem/H

"""
H. Kevin and Strange Operation

Purpose:
This code calculates the number of distinct non-empty binary strings that can be obtained from a given binary string through a sequence of strange operations. The operation modifies the string by choosing a position p, applying max operations on all elements before p, and deleting element at position p.

Algorithms/Techniques:
- Dynamic Programming with space optimization
- Run-length encoding of the input string
- Modular arithmetic for large results

Time Complexity: O(N) per test case, where N is the length of the input string.
Space Complexity: O(N) for storing run-length encoded representation and DP array.

Input Format:
- First line contains number of test cases t (1 <= t <= 10^4)
- Each test case contains a binary string s (1 <= |s| <= 10^6)

Output Format:
- For each test case, print the number of distinct non-empty binary strings modulo 998244353
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())
mod = 998244353


def solve_slow(N, S):
    A = [int(s) for s in S] + [1]
    A = A[::-1]
    comp_A = []
    s, n = A[0], 1
    for i in range(1, len(A)):
        if A[i] == s:
            n += 1
        else:
            comp_A.append((s, n))
            s, n = A[i], 1
    comp_A.append((s, n))
    K = len(comp_A)
    dp = [[0] * (N + 1) for i in range(K + 1)]
    for i in range(K)[::-1]:
        s, n = comp_A[i]
        for j in range(N + 1):
            if s == 1:
                dp[i][j] = n + dp[i + 1][j]
            else:
                if n <= j:
                    dp[i][j] = n + dp[i + 1][j]
                else:
                    rest = n - j
                    dp[i][j] = n
                    for k in range(rest + 1):
                        if j + k <= N:
                            dp[i][j] += dp[i + 1][j + k]
    print(dp)
    return dp[0][0]


def solve_fast(N, S):
    A = [int(s) for s in S] + [1]
    A = A[::-1]
    comp_A = []
    s, n = A[0], 1
    # Run-length encoding to group consecutive characters
    for i in range(1, len(A)):
        if A[i] == s:
            n += 1
        else:
            comp_A.append((s, n))
            s, n = A[i], 1
    comp_A.append((s, n))

    # K is the number of groups in run-length encoding
    K = len(comp_A)
    # dp[j] represents contribution to number of ways for length j in current step
    dp = [0] * (N + 1)
    all_add = 0
    for i in range(K)[::-1]:
        s, n = comp_A[i]
        if s == 1:
            # If group is all 1s, add all the contribution to all_add
            all_add = all_add + n
            all_add %= mod
            continue
        # When we see a group of 0s, update dp array for values from n down to 0
        # This step accumulates contributions for lengths starting from n backwards
        dp[n] = (dp[n] + all_add) % mod
        for j in range(n)[::-1]:
            # For each j less than n, we accumulate further contributions
            dp[j] += dp[j + 1] + all_add
            dp[j] %= mod
        # Subtract all_add from dp[0...n-1] to adjust the values properly
        for j in range(n + 1):
            dp[j] -= all_add
            dp[j] %= mod
        # Add current group length contribution to all_add
        all_add = all_add + n
        all_add %= mod
    # Return final answer: dp[0] plus all_add reduced by 1 (since we added 1 before)
    return (dp[0] + all_add - 1) % mod


for _ in range(int(input())):
    S = input()
    N = len(S)
    print(solve_fast(N, S))


# https://github.com/VaHiX/codeForces/