# Problem: CF 1778 C - Flexible String
# https://codeforces.com/contest/1778/problem/C

"""
Algorithm: Flexible String
Purpose: Maximize the number of matching substrings (a[l,r] == b[l,r]) by replacing at most k distinct characters in string a.
Approach:
1. Precompute the initial number of matching pairs without any operations.
2. Identify all characters in string a that differ from string b at the same positions.
3. If k is greater than or equal to the number of differing characters, we can make all characters match, so return total pairs.
4. Otherwise, try all combinations of k differing characters to replace and calculate the maximum matching pairs.

Time Complexity: O(2^d * n) where d is the number of differing characters and n is the length of the string.
Space Complexity: O(d + n) for storing differing characters and auxiliary space for combinations.
"""

import sys

input = sys.stdin.readline
I = lambda: list(map(int, input().split()))
from itertools import combinations as cb


def calc(a, b, pos):
    # Calculate the number of matching pairs for substrings when some characters are replaced
    an = 0
    le = 0
    for i in range(len(a)):
        if a[i] == b[i] or (a[i] in pos):
            le += 1
        else:
            le = 0
        an += le
    return an


(t,) = I()
for _ in range(t):
    n, k = I()
    a = input().strip()
    b = input().strip()
    an = calc(a, b, "")  # Calculate initial matches
    dist = set()
    # Find all characters in 'a' which differ from 'b' at the same positions
    for i in range(n):
        if a[i] != b[i]:
            dist.add(a[i])
    # If k is sufficient to replace all differing characters
    if k >= len(dist):
        an = n * (n + 1) // 2  # All possible pairs
    else:
        # Try all combinations of k characters to replace
        for i in cb(dist, k):
            an = max(an, calc(a, b, "".join(i)))  # Update maximum with current combination
            if an == n * (n + 1) // 2:  # Early termination if we got all pairs
                break
    print(an)


# https://github.com/VaHiX/CodeForces/