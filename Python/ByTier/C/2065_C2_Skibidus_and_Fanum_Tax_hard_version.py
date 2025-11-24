# Problem: CF 2065 C2 - Skibidus and Fanum Tax (hard version)
# https://codeforces.com/contest/2065/problem/C2

"""
C2. Skibidus and Fanum Tax (hard version)

Algorithms/Techniques:
- Greedy approach with binary search
- For each element in array 'a', we try to use the smallest valid value from sorted array 'b'
  such that the resulting value maintains non-decreasing order of the transformed array
- Uses bisect_left to efficiently find the smallest element in 'b' that satisfies constraints

Time Complexity: O((n + m) * log(m)) per test case
Space Complexity: O(m) for storing the sorted array 'b'

The algorithm processes elements of 'a' sequentially, and for each element,
it finds the best possible value from 'b' using binary search while ensuring
the transformed sequence remains non-decreasing.
"""

import sys

input = sys.stdin.readline
from bisect import bisect_left as bs

for i in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = sorted(list(map(int, input().split())))
    prv = -(1 << 64)  # Initialize previous value to negative infinity
    check = 1
    for j in range(n):
        ind = bs(b, prv + a[j])  # Find index of first element in b >= prv + a[j]
        if ind < m:  # If such element exists
            if prv <= b[ind] - a[j]:  # Check if this transformation keeps order
                if a[j] >= prv:  # If original a[j] is >= prv
                    a[j] = min(b[ind] - a[j], a[j])  # Choose smaller of the two options
                else:
                    a[j] = b[ind] - a[j]  # Use transformation directly
            elif a[j] < prv:  # If even transformation doesn't preserve order
                check = 0  # Impossible to sort
                break
        else:  # No valid element in b satisfies the constraint
            if a[j] < prv:
                check = 0  # Impossible to sort
                break
        prv = a[j]  # Update previous value for next iteration
    print("yes" if check else "no")


# https://github.com/VaHiX/codeForces/