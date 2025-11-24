# Problem: CF 1662 M - Bottle Arrangements
# https://codeforces.com/contest/1662/problem/M

"""
Code Purpose:
This code solves the problem of arranging red (R) and white (W) wine bottles such that 
each of the m critics can select a contiguous interval of bottles satisfying their 
requested number of red and white wines. The approach uses a greedy method:
- Determine the maximum required red and white wines across all critics.
- If the total of these maximums exceeds the number of bottles n, it's impossible.
- Otherwise, place all required red wines first followed by white wines.

Algorithms/Techniques:
- Greedy algorithm
- Linear scan for maximum values
- String construction

Time Complexity: O(m) per test case, where m is the number of critics.
Space Complexity: O(1) excluding input storage.

Note: The input is processed in a streaming fashion using iterators.
"""

from itertools import islice
from sys import stdin

lines = map(lambda line: map(int, line.split()), stdin.readlines()[1:])
for n, m in lines:
    max_r = max_w = 0
    for r, w in islice(lines, m):
        max_r, max_w = max(max_r, r), max(max_w, w)
    if max_r + max_w > n:
        print("IMPOSSIBLE")
    else:
        print(f"{'R' * max_r}{'W' * (n - max_r)}")


# https://github.com/VaHiX/CodeForces/