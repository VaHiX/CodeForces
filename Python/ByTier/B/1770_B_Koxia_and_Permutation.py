# Problem: CF 1770 B - Koxia and Permutation
# https://codeforces.com/contest/1770/problem/B

"""
Algorithm: Construct a permutation that minimizes the maximum value of 
           max(p[i], ..., p[i+k-1]) + min(p[i], ..., p[i+k-1]) over all valid i.

Approach:
- The key insight is to interleave large and small numbers to minimize 
  the range of each sliding window of size k.
- We construct the permutation by alternating between the largest 
  available number and the smallest, placing them in a specific order.

Time Complexity: O(n)
Space Complexity: O(1) (excluding output space)

This method works by:
1. For even n: pair numbers from both ends (n, 1), (n-1, 2), etc.
2. For odd n: do the same but place the middle number at the end.

The idea is to ensure that in any window of size k, the difference 
between max and min elements is minimized.
"""

for _ in range(int(input())):
    n, k = map(int, input().split())
    for i in range(n // 2):
        print(n - i, i + 1, end=" ")
    if n % 2:
        print(n // 2 + 1)
    else:
        print()


# https://github.com/VaHiX/CodeForces/