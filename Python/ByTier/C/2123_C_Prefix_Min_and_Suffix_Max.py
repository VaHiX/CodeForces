# Problem: CF 2123 C - Prefix Min and Suffix Max
# https://codeforces.com/contest/2123/problem/C

"""
C. Prefix Min and Suffix Max
Algorithms/Techniques: Prefix minimum, suffix maximum, greedy approach

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

For each element in the array, we determine if it's possible to reduce the entire array to just that element using operations:
- Replace a prefix with its minimum value
- Replace a suffix with its maximum value

The key insight is:
1. An element can be the final remaining element only if it is either:
   - The minimum in some prefix (from left)
   - The maximum in some suffix (from right)

2. For each position i, we check:
   - If a[i] is the minimum in any prefix ending at or before i
   - If a[i] is the maximum in any suffix starting at or after i

This can be done efficiently by precomputing:
- Prefix minimums from left to right
- Suffix maximums from right to left

The solution uses two passes:
1. Left-to-right pass to mark elements that could be the final element due to being a prefix minimum
2. Right-to-left pass to mark elements that could be the final element due to being a suffix maximum
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    ans = ["0"] * n
    ans[0] = "1"  # First element can always be the answer (prefix of size 1)
    ans[-1] = "1"  # Last element can always be the answer (suffix of size 1)
    
    mi = a[0]  # Initialize minimum from left
    for i in range(1, n):
        if a[i] < mi:
            ans[i] = "1"
            mi = a[i]
    
    ma = a[-1]  # Initialize maximum from right
    for i in range(n - 2, -1, -1):
        if a[i] > ma:
            ans[i] = "1"
            ma = a[i]
    
    print("".join(ans))


# https://github.com/VaHiX/codeForces/