# Problem: CF 1662 A - Organizing SWERC
# https://codeforces.com/contest/1662/problem/A

"""
A. Organizing SWERC

Purpose:
This code solves a problem where Gianni, the chief judge, needs to select a set of 10 problems 
with distinct difficulties (from 1 to 10) to form a contest. For each difficulty level, 
he selects the most beautiful (highest beauty score) available problem. If any difficulty 
level is missing, he outputs "MOREPROBLEMS".

Algorithms/Techniques:
- Greedy approach: for each difficulty, keep track of the maximum beauty score.
- Hash map to store max beauty per difficulty.

Time Complexity: O(n) per test case, where n is the number of problems.
Space Complexity: O(1) since we use a fixed-size dictionary (10 difficulties).

Input Format:
- First line: number of test cases t
- For each test case:
  - First line: number of problems n
  - Next n lines: beauty score b_i and difficulty d_i for each problem

Output Format:
- For each test case: total beauty of chosen problem set, or "MOREPROBLEMS" if not possible.
"""

import sys

input = sys.stdin.readline
M = int(1e9) + 7


def solve():
    n = int(input())  # Read number of problems
    vis = {i: -1 for i in range(1, 11)}  # Initialize difficulty -> max beauty mapping
    
    for i in range(n):
        b, d = map(int, input().split())  # Read beauty and difficulty of current problem
        vis[d] = max(vis[d], b)  # Keep the maximum beauty for each difficulty
    
    # Check if all difficulties from 1 to 10 are covered
    for x in vis.values():
        if x == -1:
            return "MOREPROBLEMS"
    
    # Return the sum of max beauties for all difficulties
    return sum(vis.values())


for _ in range(int(input())):  # Process each test case
    print(solve())


# https://github.com/VaHiX/codeForces/