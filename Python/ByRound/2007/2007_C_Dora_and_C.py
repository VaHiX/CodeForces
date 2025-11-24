# Problem: CF 2007 C - Dora and C++
# https://codeforces.com/contest/2007/problem/C

"""
Problem: Minimize the range of an array after performing operations with constants a and b.

Algorithms/Techniques:
- Use GCD to reduce the problem to modular arithmetic.
- Sort the elements modulo d = gcd(a, b).
- Compute minimum difference between consecutive elements in sorted mod array.
- Handle wraparound case by considering (d - a[i] + a[i-1]) for adjacent elements.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the modded array
"""

import math

T = int(input())
for _ in range(T):
    n, a, b = map(int, input().split())
    d = math.gcd(a, b)  # Reduce problem to modulo d
    a = list(map(int, input().split()))
    a = [x % d for x in a]  # Convert all elements to their mod d equivalents
    a.sort()  # Sort to analyze differences efficiently
    res = a[n - 1] - a[0]  # Initial range (without wraparound)
    for i in range(1, n):
        # Check wraparound case: difference from end to start of cycle
        res = min(res, a[i - 1] + d - a[i])
    print(res)


# https://github.com/VaHiX/codeForces/