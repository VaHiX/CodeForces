# Problem: CF 2070 B - Robot Program
# https://codeforces.com/contest/2070/problem/B

"""
B. Robot Program

Purpose:
This program calculates how many times a robot will enter the point 0 during the next k seconds,
given a command sequence of 'L' and 'R' moves, starting from position x.

Algorithms/Techniques:
- Prefix sum to track robot's position over time.
- Cycle detection in robot movement to optimize for large k values.
- Mathematical calculation to determine number of full cycles and remaining steps.

Time Complexity: O(n) per test case, where n is the length of the command sequence.
Space Complexity: O(n) due to prefix sum array storage.

Input:
- t: number of test cases
- For each test case:
  - n, x, k: length of sequence, starting position, time limit
  - s: command string of 'L' and 'R'

Output:
- Number of times robot enters point 0 within k seconds.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, x, k = map(int, input().split())
    s = input()
    p = [0]  # Prefix sum array to track position changes
    for j in range(n):
        p.append(p[-1] + (1 if s[j] == "R" else -1))  # Build prefix sums
    
    if not (-x in p) or k < p.index(-x):  # If robot never reaches 0 or not enough time to reach it
        print(0)
    else:
        k -= p.index(-x)  # Subtract steps needed to first reach 0
        if 0 in p[1:]:  # If there's a cycle back to 0
            ind = p[1:].index(0) + 1  # Find cycle length
            print(k // ind + 1)  # Add 1 for the initial step
        else:
            print(1)  # No cycle, robot reaches 0 once and stops


# https://github.com/VaHiX/codeForces/