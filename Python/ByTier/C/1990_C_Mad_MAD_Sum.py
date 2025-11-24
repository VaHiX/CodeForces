# Problem: CF 1990 C - Mad MAD Sum
# https://codeforces.com/contest/1990/problem/C

"""
Algorithm: Mad MAD Sum
Approach:
- For each step of the process, compute the MAD (Maximum Appearing Duplicate) for prefixes of the array.
- The MAD is the largest value that appears at least twice in the prefix.
- Modify the array in-place by replacing each element with the MAD of the prefix up to that point.
- Accumulate the sum of all elements at each step.

Time Complexity: O(n^2) in worst case due to nested operations in doit() function.
Space Complexity: O(n) for the auxiliary boolean array 'c' used in doit().

The algorithm simulates the process step-by-step, updating the array and accumulating the sum at each iteration.
"""

import sys

input = sys.stdin.readline


def doit(a, n):
    # Boolean array to track which numbers have been seen
    c = [False] * (n + 1)
    maxu = 0  # Tracks the maximum duplicate number seen so far
    for i in range(n):
        # If the number was already seen, update maxu
        if c[a[i]]:
            maxu = max(maxu, a[i])
        # Mark the number as seen
        c[a[i]] = True
        # Set current element to the maximum duplicate seen so far
        a[i] = maxu
    return a


def solv():
    n = int(input())
    a = list(map(int, input().split()))
    # Initial sum of array elements
    ans = sum(a)
    # Apply one step of transformation
    a = doit(a, n)
    # Add sum after transformation
    ans += sum(a)
    # Apply another step of transformation
    a = doit(a, n)
    # For remaining elements, add weighted sum based on position
    for i in range(n):
        ans += (n - i) * a[i]
    print(ans)


tt = int(input())
for _ in range(tt):
    solv()


# https://github.com/VaHiX/CodeForces/