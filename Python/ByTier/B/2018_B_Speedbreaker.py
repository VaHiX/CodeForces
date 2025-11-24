# Problem: CF 2018 B - Speedbreaker
# https://codeforces.com/contest/2018/problem/B

"""
B. Speedbreaker
Algorithm: Greedy + Two Pointers
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves finding how many starting cities allow conquering all cities within given deadlines.
We model this as a constraint satisfaction problem where each city must be conquered by its deadline,
and we can only move to adjacent unvisited cities.

Approach:
1. For each city, store the first (mn) and last (mx) time it needs to be conquered.
2. Use two pointers (lo, hi) to track valid range of times when we can begin conquering.
3. For each city:
   - If it wasn't conquered at all, skip.
   - Compute a required window size for this city.
   - Adjust constraint boundaries (lo, hi) based on this city's constraints.
   - If any inconsistency arises (window becomes invalid), output 0.
4. Return max(hi - lo + 1, 0) as the final count of valid starting positions.

This solution efficiently determines valid starting points by maintaining a sliding window of acceptable times
based on each city's deadline and its position in the sequence.
"""

import sys

input = lambda: sys.stdin.readline().strip()
printerr = lambda *args, **kwargs: print(
    "\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs
)


def main():
    n = int(input())
    (*a,) = map(int, input().split())
    mn = [-1] * n  # First time each city must be conquered
    mx = [-1] * n  # Last time each city must be conquered
    for i, x in enumerate(a):
        x -= 1  # Convert to 0-based index
        if mn[x] == -1:
            mn[x] = i  # Record first occurrence
        mx[x] = i  # Record last occurrence
    lo = 0  # Lower bound of valid starting time
    hi = n - 1  # Upper bound of valid starting time
    l = n  # Leftmost position that is conquered
    r = -1  # Rightmost position that is conquered
    for i, (x, y) in enumerate(zip(mn, mx)):
        if x == -1:
            continue  # Skip unused cities
        d = i - (y - x)  # Compute required delay for this city
        l = min(l, x)
        r = max(r, y)
        if d < 0 or i < r - l:  # Check for inconsistency
            print(0)
            return
        lo = max(lo, x - d)  # Update lower bound of valid range
        hi = min(hi, y + d)  # Update upper bound of valid range
    print(max(hi - lo + 1, 0))  # Output number of valid starting positions


tcs = int(input())
for tc in range(tcs):
    main()


# https://github.com/VaHiX/codeForces/