# Problem: CF 1977 A - Little Nikita
# https://codeforces.com/contest/1977/problem/A

"""
Code Purpose:
This program determines whether it's possible for Nikita to build a tower with exactly m cubes
after performing exactly n moves, where each move consists of either adding or removing one cube.
The solution is based on the observation that:
- If n < m, it's impossible because we cannot remove more cubes than we have added.
- If n >= m, the difference (n - m) must be even for it to be possible, since we can only add
  or remove one cube at a time, so any excess cubes must be balanced by an even number of
  additions and removals.

Algorithms/Techniques:
- Simple mathematical check based on parity and comparison of n and m.
- Greedy approach: we assume we add cubes first, and if we end up with more than m,
  we remove the excess. The number of removals must be even for it to work.

Time Complexity: O(1) - Constant time for each test case.
Space Complexity: O(1) - Constant space used, regardless of input size.
"""

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    if n < m:
        print("No")  # Not enough moves to reach m cubes
    elif (n - m) % 2 == 0:
        print("Yes")  # Even difference allows for balanced additions and removals
    else:
        print("No")  # Odd difference makes it impossible to balance


# https://github.com/VaHiX/CodeForces/