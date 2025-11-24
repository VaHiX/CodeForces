# Problem: CF 662 A - Gambling Nim
# https://codeforces.com/contest/662/problem/A

"""
Gambling Nim Solution

This problem involves calculating the probability that Petya wins a variant of the Nim game,
where each card contributes either its 'a' or 'b' value to the Nim pile sizes,
chosen randomly and uniformly. The game is won by the first player if the XOR of all
pile sizes is non-zero; otherwise, the second player (Vasya) wins.

The approach uses concepts from linear algebra over GF(2), where each number can be
represented as a vector in the vector space of binary vectors of length up to 60.
We determine the basis of vectors derived from XOR differences (a_i ^ b_i) and
use it to compute whether the initial state allows Petya to win.

Key Techniques:
- XOR properties for Nim games
- Gaussian elimination in GF(2) to compute the rank of XOR differences
- Probability calculation based on the linear independence of differences

Time Complexity: O(n * log(max_value))
Space Complexity: O(n)
"""

import sys

input = sys.stdin.buffer.readline

n = int(input())
goal = 0
C = []
for _ in range(n):
    a, b = [int(x) for x in input().split()]
    C.append(a ^ b)  # Store the difference (XOR) of the two card values
    goal ^= a        # XOR of all 'a' values, representing current game state

base = []
for c in C:
    # Reduce c with the current basis to find minimal representation
    for b in base:
        c = min(c, c ^ b)
    if c:  # If reduced c is non-zero, add it to the basis
        base.append(c)

# Further reduce goal with the basis to find the minimal representation
for b in base:
    goal = min(goal, goal ^ b)

# If goal is 0, the initial state is losing for Petya (Vasya wins)
# If goal is non-zero, Petya wins
if goal:
    print("1/1")
else:
    # The number of independent differences (rank of the matrix)
    m = len(base)
    # Calculate probability: (2^m - 1) / 2^m
    print(2**m - 1, "/", 2**m, sep="")


# https://github.com/VaHiX/CodeForces/