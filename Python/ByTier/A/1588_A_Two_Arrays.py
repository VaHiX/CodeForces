# Problem: CF 1588 A - Two Arrays
# https://codeforces.com/contest/1588/problem/A

"""
Algorithm: Two Arrays
Technique: Sorting + Greedy Check

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing arrays a and b

The problem asks whether we can transform array 'a' into array 'b' using:
1. Adding 1 to k distinct indices (0 <= k <= n)
2. Permuting the elements of array 'a' in any order

Key insight:
- We can only increase values in array 'a', not decrease them.
- After sorting both arrays, we check for each element a[i] and b[i]:
  - If a[i] > b[i], it's impossible (we can't decrease)
  - If a[i] < b[i] - 1, it's impossible (we need to increase more than allowed by the sum of increments)
  - Otherwise, we can potentially adjust via adding 1s and permuting

This greedy approach works because:
- The sum of all elements in 'a' must be less than or equal to the sum of 'b'
- Sorting allows us to make optimal matching
"""

import sys

for _ in range(int(sys.stdin.readline())):
    n = int(sys.stdin.readline())
    a = [int(i) for i in sys.stdin.readline().split()]
    b = [int(i) for i in sys.stdin.readline().split()]
    a.sort()  # Sort both arrays to apply greedy matching
    b.sort()
    for i in range(n):
        if a[i] > b[i] or a[i] < b[i] - 1:  # Check feasibility of transformation
            print("NO")
            break
    else:
        print("YES")


# https://github.com/VaHiX/codeForces/