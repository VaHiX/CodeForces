# Problem: CF 1859 E - Maximum Monogonosity
# https://codeforces.com/contest/1859/problem/E

"""
Maximum Monogonosity

Problem Description:
Given two arrays a and b of length n, we need to find the maximum sum of costs of non-intersecting segments
whose total length equals k. The cost of a segment [l, r] is defined as |b[l] - a[r]| + |b[r] - a[l]|.

Approach:
- Dynamic Programming with optimization
- For each position i (from n down to k), we compute the maximum value for segments ending at i
- We maintain four diagonal values representing different combinations of a[i] and b[i] contributions
- For each segment length j, we evaluate four possible cost types and take maximum
- Time Complexity: O(n * k)
- Space Complexity: O(k)

Algorithms/Techniques:
- Dynamic Programming
- Segment cost optimization using precomputed diagonal values
"""

from sys import stdin, stdout

t = int(stdin.readline())

for _ in range(t):
    n, k = [int(x) for x in stdin.readline().split()]
    a = [int(x) for x in stdin.readline().split()]
    b = [int(x) for x in stdin.readline().split()]

    dp = [0] * (k + 1)
    for i in range(n, k - 1, -1):
        dp2 = [0]
        diag11 = a[i - 1] + b[i - 1]
        diag12 = a[i - 1] - b[i - 1]
        diag21 = -a[i - 1] + b[i - 1]
        diag22 = -a[i - 1] - b[i - 1]

        for j in range(1, k + 1):
            # Compute the maximum value considering four combinations of a and b
            dp2.append(
                max(
                    diag11 - b[i - j] - a[i - j], # Cost type 1
                    diag12 - b[i - j] + a[i - j], # Cost type 2
                    diag21 + b[i - j] - a[i - j], # Cost type 3
                    diag22 + b[i - j] + a[i - j], # Cost type 4
                    dp[j],  # No segment ending at position i
                )
            )
            # Update diagonal values for next iteration if valid
            if i - j > 0:
                diag11 = max(diag11, dp2[-1] + a[i - j - 1] + b[i - j - 1])
                diag12 = max(diag12, dp2[-1] + a[i - j - 1] - b[i - j - 1])
                diag21 = max(diag21, dp2[-1] - a[i - j - 1] + b[i - j - 1])
                diag22 = max(diag22, dp2[-1] - a[i - j - 1] - b[i - j - 1])

        dp = dp2

    stdout.write(str(dp[-1]) + "\n")


# https://github.com/VaHiX/CodeForces/