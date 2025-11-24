# Problem: CF 1999 F - Expected Median
# https://codeforces.com/contest/1999/problem/F

"""
F. Expected Median

Purpose:
This code computes the sum of medians over all subsequences of a given binary array of fixed odd length k.
The algorithm uses combinatorics to efficiently determine how many times each value (0 or 1) appears as the median in valid subsequences.

Techniques:
- Precomputed factorials for fast combination calculation using modular inverse
- Modular arithmetic to handle large numbers
- Iterative counting based on number of 1s and 0s in subsequence

Time Complexity: O(N + T * k)
Space Complexity: O(N)

N = 2 * 10^5 (precomputed factorial array size)
T = number of test cases
k = length of subsequences (odd)
"""

import sys

input = sys.stdin.readline
M = 10**9 + 7
N = 2 * 10**5
d = [1]
for i in range(1, N + 1):
    d.append(d[-1] * i % M)  # Precompute factorials modulo M


def comb(k, n):
    return d[n] * pow((d[k] * d[n - k]), -1, M) % M  # Compute combination C(n, k) mod M using modular inverse


for _ in range(int(input())):
    n, k = map(int, input().split())
    w = input()
    a = w.count("1")  # Count of 1s in the array
    b = n - a         # Count of 0s in the array
    c = 0
    x = (k + 1) // 2  # Minimum number of 1s required to be median (since k is odd)
    for i in range(x, min(a, k) + 1):  # For each valid count of 1s in subsequence
        j = k - i  # Corresponding count of 0s needed
        if j <= b:
            c += comb(i, a) * comb(j, b)  # Add number of ways to choose such subsequence
    print(c % M)  # Output result modulo M


# https://github.com/VaHiX/codeForces/