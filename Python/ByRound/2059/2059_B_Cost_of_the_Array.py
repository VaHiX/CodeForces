# Problem: CF 2059 B - Cost of the Array
# https://codeforces.com/contest/2059/problem/B

"""
B. Cost of the Array
Algorithm: Greedy + Observation
Time Complexity: O(n) for each test case
Space Complexity: O(n) for storing the array

The problem asks to split an array into k subarrays and compute the cost of a derived array b.
Key insight:
- Subarrays at even indices (2, 4, ..., k) are concatenated into b.
- A zero is appended to b.
- Cost is the smallest index where b[i] != i.

Approach:
1. If n == k: Each element forms its own subarray; even-indexed elements form b.
   - Then check b[i] == i for all valid indices.
   - Return first mismatched index (1-based).
2. If n != k: 
   - If there are fewer than (n - k + 1) occurrences of '1' in the range a[1:n-k+2], 
     we can achieve cost = 1 by splitting appropriately.
   - Else, we must have cost = 2 because even with optimal strategy,
     b is mostly 1s, so cost = 2 (b[2] != 2).
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    if n == k:
        # Each element is its own subarray; even-indexed elements are part of b
        b = [a[j] for j in range(1, n, 2)] + [0]
        for j in range(n // 2 + 1):
            if b[j] != j + 1:
                print(j + 1)
                break
    else:
        # If there are fewer than (n - k + 1) numbers equal to 1,
        # it's possible to make cost = 1.
        if a[1 : n - k + 2].count(1) != n - k + 1:
            print(1)
        else:
            # Otherwise, we must have cost = 2
            print(2)


# https://github.com/VaHiX/codeForces/