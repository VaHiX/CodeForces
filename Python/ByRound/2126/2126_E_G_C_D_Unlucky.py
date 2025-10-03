# Problem: CF 2126 E - G-C-D, Unlucky!
# https://codeforces.com/contest/2126/problem/E

"""
E. G-C-D, Unlucky!
Time Complexity: O(n) per test case, where n is the length of arrays p and s.
Space Complexity: O(1) excluding input storage.

Algorithms/Techniques:
- Prefix GCD and suffix GCD validation using properties of GCD.
- Key insight: For valid arrays p and s to represent prefix and suffix GCDs,
  the last element of p must equal the first element of s (i.e., p[-1] == s[0]).
  Additionally, for each i in range(n - 1), the following conditions must hold:
  1. gcd(p[i], s[i+1]) == s[0]
  2. p[i] is divisible by p[i+1] (i.e., p[i] % p[i+1] == 0)
  3. s[i+1] is divisible by s[i] (i.e., s[i+1] % s[i] == 0)

Approach:
- Check if the last element of prefix array p equals first element of suffix array s.
- Iterate through all intermediate indices to ensure divisibility and GCD compatibility.
"""

import sys
from math import gcd

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    p = list(map(int, input().split()))
    s = list(map(int, input().split()))
    if p[-1] != s[0]:
        print("NO")
        continue
    flg = False
    for i in range(n - 1):
        # Check if GCD of current prefix and next suffix equals the base GCD s[0]
        if gcd(p[i], s[i + 1]) != s[0]:
            print("NO")
            break
        # Check if prefix elements are divisible (to maintain valid GCD structure)
        if p[i] % p[i + 1] > 0:
            print("NO")
            break
        # Check if suffix elements are divisible (to maintain valid GCD structure)
        if s[i + 1] % s[i] > 0:
            print("NO")
            break
    else:
        print("YES")


# https://github.com/VaHiX/codeForces/