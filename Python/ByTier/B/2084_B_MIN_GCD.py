# Problem: CF 2084 B - MIN = GCD
# https://codeforces.com/contest/2084/problem/B

"""
B. MIN = GCD

Purpose:
This code determines whether a given sequence of integers can be rearranged such that 
there exists an index i (1 ≤ i < n) where the minimum of the first i elements equals 
the greatest common divisor (GCD) of the remaining elements.

Algorithm/Technique:
- Sort the array to process elements in ascending order.
- For each element after the first, check if it's divisible by the first element.
  If so, compute the GCD of all such divisible elements.
- The key insight is that if we can form a valid split, then the GCD of the suffix 
  must equal the first element (as it's the minimum of prefix and also a divisor of
  all elements in the suffix).
- Time Complexity: O(n log n + n log M), where M is the maximum value in array.
  Sorting takes O(n log n), and computing GCDs can take up to O(n log M) due to 
  Euclidean algorithm being applied multiple times.
- Space Complexity: O(1), excluding input storage.

Time Complexity: O(n log n + n log M)
Space Complexity: O(1)
"""

import sys
from math import gcd

input = lambda: sys.stdin.readline().strip()
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()  # Sort the array to analyze elements systematically
    g = 0  # Initialize GCD variable
    for x in a[1:]:  # Iterate over all elements except the first
        if x % a[0] != 0:  # Skip if current element is not divisible by first
            continue
        g = gcd(g, x)  # Compute GCD of valid elements
    if g == a[0]:  # Check if computed GCD equals the first element
        print("Yes")
    else:
        print("No")


# https://github.com/VaHiX/codeForces/