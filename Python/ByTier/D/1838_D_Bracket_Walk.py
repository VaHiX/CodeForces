# Problem: CF 1838 D - Bracket Walk
# https://codeforces.com/contest/1838/problem/D

"""
Algorithm: Segment Tree with Range Minimum/Maximum Query
Purpose: Determine if a bracket string is walkable after each query (flip of character)
Time Complexity: O(q * log n) where q is number of queries and n is length of string
Space Complexity: O(n) for segment tree storage

The problem uses a segment tree to efficiently maintain the minimum and maximum positions
where transitions occur in the bracket string. A string is walkable if:
1. Length is even (necessary for balanced brackets)
2. There exists a valid path from start to end such that brackets are balanced at all times

The segment tree stores for each node the minimum/maximum index where a transition occurs in that range,
which helps to determine if a valid walk exists.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def update(i, x, y):
    # Update the segment tree nodes for index i with new min x and max y values
    i += l1
    mi[i], ma[i] = x, y
    i //= 2
    while i:
        mi[i] = min(mi[2 * i], mi[2 * i + 1])
        ma[i] = max(ma[2 * i], ma[2 * i + 1])
        i //= 2
    return


n, q = map(int, input().split())
s = list(input().rstrip())
# Convert characters to 1s and 0s (1 for '(', 0 for ')') and pad with 1 at start and 0 at end
s = [1] + [i & 1 for i in s] + [0]
l1 = pow(2, (n + 2).bit_length())  # Calculate next power of 2 for segment tree size
l2 = 2 * l1
inf = pow(10, 9) + 1
mi, ma = [inf] * l2, [-inf] * l2  # Initialize segment tree arrays

# Preprocess the segment tree with initial values
for i in range(1, n + 1):
    if s[i] == s[i - 1]:
        mi[i + l1] = i
    if s[i] == s[i + 1]:
        ma[i + l1] = i
# Build the segment tree from leaves to root
for i in range(l1 - 1, 0, -1):
    mi[i] = min(mi[2 * i], mi[2 * i + 1])
    ma[i] = max(ma[2 * i], ma[2 * i + 1])

ans = []
for _ in range(q):
    i = int(input())
    # Flip the character at position i (1 -> 0 or 0 -> 1)
    s[i] ^= 1
    # Update the segment tree for the affected positions
    for j in range(max(i - 1, 1), min(i + 1, n) + 1):
        x = j if s[j] == s[j - 1] else inf
        y = j if s[j] == s[j + 1] else -inf
        update(j, x, y)
    
    # Get the minimum and maximum transition indices from the root of segment tree
    u, v = mi[1], ma[1]
    # Determine if the string is walkable based on the criteria
    ans0 = (
        "YES" if not n % 2 and (u == inf or (u % 2 == (n - v - 1) % 2 == 0)) else "NO"
    )
    ans.append(ans0)

sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/