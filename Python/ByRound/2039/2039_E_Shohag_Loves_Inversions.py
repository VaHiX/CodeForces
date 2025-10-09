# Problem: CF 2039 E - Shohag Loves Inversions
# https://codeforces.com/contest/2039/problem/E

"""
E. Shohag Loves Inversions

Problem Description:
Given an initial array a = [0, 1], we can repeatedly insert the number of inversions k in the current array at any position.
We are to count how many distinct arrays of length n can be formed after performing these operations.

This problem uses dynamic programming with careful tracking of the number of inversions and how inserting k affects future counts.

Approach:
- The base cases are handled directly: n=2 returns 1.
- For n > 2, we use a recurrence relation to calculate the result based on prior states.
  - `s` keeps track of cumulative sums related to inversion counts.
  - `ans` accumulates the total number of distinct arrays.

Time Complexity: O(n)
Space Complexity: O(1)

Algorithm Techniques:
- Dynamic Programming
- Modular Arithmetic
"""

import sys

input = lambda: sys.stdin.readline().strip()
p = 998244353
T = int(input())
for _ in range(T):
    n = int(input())
    ans = 0
    if n == 2:
        print(1)
    else:
        s = 1
        ans = 0
        for i in range(2, n):
            if i <= 3:
                # For small i, directly add i to answer and update sum
                ans += i
                ans %= p
                s += i
                s %= p
            else:
                # For larger i, use recurrence relation derived from pattern of inversion insertions
                ans += i + (s - i) * (i + 1)
                ans %= p
                s += (s - i + 1) * i
                s %= p
        print(ans)


# https://github.com/VaHiX/codeForces/