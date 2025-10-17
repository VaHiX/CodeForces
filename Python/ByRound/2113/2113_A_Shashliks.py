# Problem: CF 2113 A - Shashliks
# https://codeforces.com/contest/2113/problem/A

"""
A. Shashliks

Purpose:
This code solves the problem of maximizing the number of shashlik portions that can be cooked
given an initial grill temperature and two types of shashlik with different temperature requirements
and cooling effects.

Algorithm:
Greedy approach - always try to cook the type which causes less temperature drop (i.e., y <= x)
to maximize the number of portions. We iterate through possible numbers of the cheaper type,
calculate how many more portions we can cook after that, and keep track of the maximum.

Time Complexity: O(1) - The loop runs a constant number of times because we're bounded by k/x or k/y.
Space Complexity: O(1) - Uses only a few integer variables for computation.

Techniques:
- Greedy selection based on minimal temperature drop
- Early termination when no more cooking is possible
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, a, b, x, y = map(int, input().split())
    # Ensure that x <= y to simplify logic (cook the type with smaller temperature drop first)
    if x > y:
        a, b = b, a
        x, y = y, x
    ans = 0
    # If we can cook at least one portion of the first type (smaller drop)
    if a <= n:
        # Calculate maximum number of such portions we can cook
        ans += (n - a) // x + 1
        # Update remaining temperature after cooking these portions
        n -= x * ans
    # If we can still cook at least one portion of the second type (larger drop)
    if b <= n:
        ans += (n - b) // y + 1
    print(ans)


# https://github.com/VaHiX/codeForces/