# Problem: CF 2126 E - G-C-D, Unlucky!
# https://codeforces.com/contest/2126/problem/E

"""
E. G-C-D, Unlucky!
Task: Determine if there exists an array 'a' such that given prefix GCD array 'p' and suffix GCD array 's' can be derived from it.

Algorithms/Techniques:
- Prefix and suffix GCD validation using mathematical properties of GCD
- Iterative check for consistency within arrays p and s

Time Complexity: O(n * log(max(p[i], s[i]))) per test case, where n is the size of arrays.
Space Complexity: O(1) extra space (not counting input storage).

Key Observations:
- For a valid array 'a', p[i] = gcd(a[0..i]) and s[i] = gcd(a[i..n-1])
- The last element of prefix GCD (p[-1]) must equal the first element of suffix GCD (s[0])
- Constraints on adjacent elements of p and s derived from GCD properties
"""

import sys
from math import gcd

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    p = list(map(int, input().split()))
    s = list(map(int, input().split()))
    if p[-1] != s[0]:  # Check if last prefix GCD equals first suffix GCD
        print("NO")
        continue
    flg = False
    for i in range(n - 1):  # Iterate through all but the last index
        # If GCD of current prefix and next suffix doesn't match s[0], invalid
        if gcd(p[i], s[i + 1]) != s[0] or p[i] % p[i + 1] > 0 or s[i + 1] % s[i] > 0:
            print("NO")
            break
    else:
        print("YES")  # All checks passed, valid configuration exists


# https://github.com/VaHiX/CodeForces/