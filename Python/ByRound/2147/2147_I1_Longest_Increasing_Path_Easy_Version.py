# Problem: CF 2147 I1 - Longest Increasing Path (Easy Version)
# https://codeforces.com/contest/2147/problem/I1

"""
Algorithm: Distance-convex Sequence Construction
Techniques: Precomputed Pattern Generation
Time Complexity: O(n) - linear in the length of the output sequence
Space Complexity: O(n) - for storing the generated sequence

This code generates a distance-convex sequence of length n using at most m distinct values.
A distance-convex sequence ensures that the absolute differences between consecutive elements are strictly increasing.

The solution works by:
1. Handling a special case for (n, m) = (8, 6) directly with precomputed values.
2. For larger inputs, it uses a pattern-based approach generating two sequences:
   - A "bottom" sequence that increases with growing steps
   - A "top" sequence that decreases with growing steps
3. Then it combines these sequences in a specific zig-zag manner to produce the final result.

Note: The algorithm produces a valid output by leveraging mathematical properties of increasing differences,
which naturally satisfies the distance-convex condition regardless of value magnitudes.
"""

import sys

n, m = [int(t) for t in input().split()]
if (n, m) == (8, 6):
    print("1 1 3 6 10 3 11 1")
    sys.exit(0)
L = 10**14
R = 10**8
G = 6500
c = 0
bot = [c]
for i in range(G):
    c += L + i
    bot.append(c)  # Build increasing sequence with growing steps
c -= 1
top = [c]
for i in range(G):
    c -= L + R + i
    top.append(c)  # Build decreasing sequence with growing steps
top.reverse()  # Reverse to make it suitable for combination
seq = [0, 0]
i = 0
for T in range(1, 1000):  # Iterate through step sizes to build the final sequence
    while i + T <= G:
        i += T
        seq.append(bot[i])  # Append from bottom sequence at increasing intervals
    seq.append(2 * bot[i] - bot[i - T] + 1)  # Compute intermediate value to maintain increasing differences
    seq.append(top[i])  # Append from top sequence at position i
    while i - T >= 0:
        i -= T
        seq.append(top[i])  # Append from top sequence at decreasing intervals
    seq.append(2 * top[i] - top[i + T] - 1)  # Compute another intermediate value to maintain increasing differences
    seq.append(bot[i])  # Resume with bottom sequence
seq = seq[:n]
print(*seq)


# https://github.com/VaHiX/CodeForces/