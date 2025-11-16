# Problem: CF 1833 F - Ira and Flamenco
# https://codeforces.com/contest/1833/problem/F

"""
Code Purpose:
This code solves the problem of counting the number of "magnificent dances" that can be formed from a list of student levels.
A magnificent dance requires:
1. Exactly m students.
2. All student levels must be distinct.
3. The absolute difference between any two student levels must be strictly less than m.

Approach:
- Sort the levels and group identical levels together.
- Use combinatorics to count valid selections of m distinct levels within a range of size m-1.
- Precompute prefix products of counts for fast modular inverse calculation.
- For each valid window of m consecutive distinct levels, compute the number of ways to choose one student from each level.

Time Complexity: O(n log n) per test case due to sorting and processing steps.
Space Complexity: O(n) for storing grouped levels and prefix products.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()

MOD = 10**9 + 7


def solve_case():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort()

    # Group consecutive identical elements and count them
    aa, cnt = [a[0]], [1]
    for i in range(1, n):
        if a[i] == a[i - 1]:
            cnt[-1] += 1
        else:
            aa += [a[i]]
            cnt += [1]
    n = len(aa)

    # Precompute prefix product of counts (used for combinations)
    pp = [1] * (n + 1)
    for i in range(n):
        pp[i + 1] = (pp[i] * cnt[i]) % MOD

    ans = 0
    # Check all possible windows of m consecutive distinct levels
    for i in range(n + 1 - m):
        # Check if the range size is exactly m-1 (i.e., levels are consecutive)
        if aa[i + m - 1] == aa[i] + m - 1:
            # Calculate combinations using prefix products
            # pp[i+m] gives total ways to select from current window
            # pp[i] gives ways to select from before current window
            # We use modular inverse to divide pp[i+m] by pp[i]
            ans = (ans + pp[i + m] * pow(pp[i], -1, MOD)) % MOD
    print(ans)


for _ in range(int(input())):
    solve_case()


# https://github.com/VaHiX/CodeForces/