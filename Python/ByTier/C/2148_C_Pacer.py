# Problem: CF 2148 C - Pacer
# https://codeforces.com/contest/2148/problem/C

"""
C. Pacer
Algorithms/Techniques: Greedy, Simulation
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves maximizing points by choosing when to move between two sides of a gym
during a series of time requirements. At each requirement, FJ must be at a specific side.
He gains one point for moving (i.e., running from one side to the other).

This is solved greedily:
- For each pair of consecutive requirements, calculate how much distance can be covered
  in the gap between the two times.
- Adjust for parity to ensure we meet the requirement correctly.
- Keep track of current position and time.

The algorithm calculates the optimal number of moves needed to satisfy all constraints
and maximizes points accordingly.
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n, m = map(int, input().split())
    ans = 0
    l = p = 0  # l: last time, p: previous side
    for _ in range(n):
        a, b = map(int, input().split())  # a: time, b: required side
        r = a - l  # r: gap between current and previous times
        if (r & 1) ^ (p != b):  # Check if parity mismatch requires adjustment
            r -= 1  # Adjust to ensure correct side at end of interval
        ans += r  # Add the number of steps we can move
        l, p = a, b  # Update last time and previous side
    print(ans + m - l)  # Add remaining steps from last requirement to final time


# https://github.com/VaHiX/codeForces/