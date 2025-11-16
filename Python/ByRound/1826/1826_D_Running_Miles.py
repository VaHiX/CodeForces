# Problem: CF 1826 D - Running Miles
# https://codeforces.com/contest/1826/problem/D

"""
Algorithm: Dynamic Programming + Prefix/Suffix Maximums
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

This solution uses prefix and suffix arrays to efficiently compute the maximum
beauty sum over a range. For each possible middle point (i), we calculate:
- Maximum beauty sum from left (using prefix array)
- Maximum beauty sum from right (using suffix array)
- The current beauty at index i
And combine them to get the maximum value of b[i1] + b[i2] + b[i3] - (r - l)
where i1, i2, i3 are the indices of three highest beauties in range [l, r].
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    n = int(input())
    b = list(map(int, input().split()))

    # Prefix array: ps[i] = max(b[0] + 0, b[1] + 1, ..., b[i] + i)
    # This helps in finding the maximum (beauty + position) up to index i
    ps = [0] * n
    ps[0] = b[0] + 0  # Initialize first element
    for i in range(1, n):  # Fill prefix array
        ps[i] = max(ps[i - 1], b[i] + i)

    # Suffix array: ss[i] = max(b[i] - i, b[i+1] - (i+1), ..., b[n-1] - (n-1))
    # This helps in finding the maximum (beauty - position) from index i onwards
    ss = [0] * n
    ss[n - 1] = b[n - 1] - (n - 1)  # Initialize last element
    for i in range(n - 2, -1, -1):  # Fill suffix array backwards
        ss[i] = max(ss[i + 1], b[i] - i)

    # Try each index as the middle sight in the triplet
    ans = 0
    for i in range(1, n - 1):
        # For a range [l, r] that includes index i,
        # we take max beauty from left (ps[i - 1]), current beauty (b[i]),
        # and max beauty from right (ss[i + 1])
        ans = max(ans, b[i] + ps[i - 1] + ss[i + 1])
    print(ans)


for _ in range(int(input())):
    solve_case()


# https://github.com/VaHiX/CodeForces/