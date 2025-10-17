# Problem: CF 2065 E - Skibidus and Rizz
# https://codeforces.com/contest/2065/problem/E

"""
E. Skibidus and Rizz

Purpose:
Construct a binary string of length n + m with exactly n 0's and m 1's such that the maximum 
balance-value among all substrings is exactly k. The balance-value of a substring is defined as 
max(count_0 - count_1, count_1 - count_0).

Algorithm:
- For a valid string to exist, k must be within bounds: abs(n - m) <= k <= max(n, m).
- We build the string by placing alternating blocks of 0's and 1's in a way that ensures
  a maximum balance exactly k.
- If n >= m: place k 0's first, then alternate between 0 and 1 for remaining positions.
- If m > n: place k 1's first, then alternate between 1 and 0 for remaining positions.

Time Complexity: O(n + m) per test case
Space Complexity: O(n + m) for the result string
"""

import sys

input = lambda: sys.stdin.readline().strip()


def printl(l):
    print("".join(str(y) for y in l))


def rl():
    return map(int, input().split())


for _ in range(int(input())):
    n, m, k = rl()
    # Check if it's possible to form a valid string with balance k
    if k < abs(n - m) or k > max(m, n):
        print(-1)
        continue
    # Build the binary string based on which of n or m is larger
    if n >= m:
        # Start with k 0's, then alternate between 0 and 1 for remaining positions,
        # with leftover 1's at the end
        a = k * [0] + (n - k) * [1, 0] + (m - n + k) * [1]
    else:
        # Start with k 1's, then alternate between 1 and 0 for remaining positions,
        # with leftover 0's at the end
        a = k * [1] + (m - k) * [0, 1] + (n - m + k) * [0]
    print("".join(str(i) for i in a))


# https://github.com/VaHiX/codeForces/