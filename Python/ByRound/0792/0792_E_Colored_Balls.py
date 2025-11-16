# Problem: CF 792 E - Colored Balls
# https://codeforces.com/contest/792/problem/E

"""
Algorithm: Minimize the number of sets to divide colored balls such that:
- Each set contains only balls of one color.
- The difference in size between any two sets is at most 1.
- All balls must be placed in sets.

Approach:
1. For each color, we have `a_i` balls of that color.
2. We are trying to find the optimal set size `sz` such that:
   - All balls of a color can be distributed into sets of size `sz` or `sz+1`.
   - The number of sets needed for all colors is minimized.
3. Try different possible values of `sz` (from the square root of the minimum number of balls).
   - For each such `sz`, check if that `sz` works (i.e., all `a_i` can be split into groups of size `sz` or `sz+1`).
4. The number of sets required for a color `a_i` is `ceil(a_i / (sz + 1))`.

Time Complexity: O(sqrt(min(a_i)) * n)
Space Complexity: O(1)

This solution optimizes by checking divisors of the minimum number of balls and related values.
"""

import math

n = int(input())
s = input().split(" ")
for i in range(len(s)):
    s[i] = int(s[i])
m = min(s)  # Find the minimum number of balls of any color


def try_sz(x):
    # Check if x is a viable set size (all a_i can be distributed into sets of size x or x+1)
    for thing in s:
        if thing % x > math.floor(thing / x):
            return False
    return True


good = False
sz = 0
# Try divisors and related values around sqrt(m) for potential set size
for i in range(1, math.ceil(m**0.5) + 1):
    if try_sz(math.floor(m / i)):
        good = True
        sz = math.floor(m / i)
        break
    if m % i == 0:
        if try_sz(math.floor(m / i) - 1):
            good = True
            sz = math.floor(m / i) - 1
            break

ans = 0
# Compute total number of sets needed for all colors
for thing in s:
    ans += math.ceil(thing / (sz + 1))
print(str(ans))


# https://github.com/VaHiX/CodeForces/