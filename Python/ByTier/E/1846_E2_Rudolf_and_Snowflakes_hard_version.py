# Problem: CF 1846 E2 - Rudolf and Snowflakes (hard version)
# https://codeforces.com/contest/1846/problem/E2

"""
E2. Rudolf and Snowflakes (hard version)

Purpose:
    Determine whether a snowflake with n vertices can exist based on a specific mathematical model.
    A snowflake is built recursively:
        - Start with one vertex.
        - In each step, every leaf node adds k new nodes (k > 1).
    The total number of vertices in such a snowflake follows the formula:
        n = 1 + k + k^2 + ... + k^x = (k^(x+1) - 1)/(k - 1)
    So, for a given n, we check if there exist integers k > 1 and x >= 1 such that:
        n * (k - 1) = k^(x+1) - 1

Algorithm:
    For each test case n:
        - Try all possible values of x from 2 to 63.
        - For each x, compute k as the integer part of n^(1/x).
        - Check if the formula holds: n * (k - 1) == k^(x+1) - 1.
        - Return "YES" if found, otherwise "NO".

Time Complexity: O(t * log(log(n))) where t is number of test cases and n <= 10^18.
Space Complexity: O(1) excluding input/output storage.

"""

from sys import stdin, stdout

ans = []
for _ in range(int(stdin.readline())):
    n = int(stdin.readline())
    for x in range(2, 64):  # Try exponents from 2 up to 63
        k = int(n ** (1 / x))  # Estimate base k using root
        if k < 2 or (n * (k - 1) == k ** (x + 1) - 1):
            break  # Break early if invalid or valid match found
    ans.append("YES" if k >= 2 else "NO")  # Output result based on valid k

stdout.write("\n".join(ans))


# https://github.com/VaHiX/codeForces/