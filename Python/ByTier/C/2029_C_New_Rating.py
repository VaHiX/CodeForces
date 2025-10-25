# Problem: CF 2029 C - New Rating
# https://codeforces.com/contest/2029/problem/C

"""
C. New Rating
Algorithm: Dynamic Programming with State Tracking
Time Complexity: O(n) per test case
Space Complexity: O(1)

This problem involves finding the maximum possible rating after skipping 
a contiguous subarray of contests. The key insight is to track three states:
- x: current rating
- y: maximum rating seen so far (before considering current contest)
- z: maximum rating if we skip one contest ending at previous index

The state transitions are based on how the rating changes when a new contest 
is processed, and which contest is skipped.
"""

import sys

input = lambda: sys.stdin.readline().strip()
printerr = lambda *args, **kwargs: print(
    "\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs
)


def f(x, v):
    # Helper function to update rating based on contest value
    return x + (v > x) - (v < x)


def main():
    n = int(input())
    (*a,) = map(int, input().split())
    x, y, z = 0, -n, -n  # Initialize states
    for v in a:
        # Update states using the helper function and max operations
        x, y, z = f(x, v), max(x, y), max(f(z, v), f(y, v))
    print(max(y, z))


tcs = int(input())
for tc in range(tcs):
    main()


# https://github.com/VaHiX/codeForces/