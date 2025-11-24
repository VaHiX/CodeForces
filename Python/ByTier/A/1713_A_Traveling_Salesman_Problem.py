# Problem: CF 1713 A - Traveling Salesman Problem
# https://codeforces.com/contest/1713/problem/A

"""
Algorithm: Greedy approach to minimize travel distance.
Techniques: Coordinate analysis and interval merging.

Time Complexity: O(n) per test case, where n is the number of boxes.
Space Complexity: O(n) for storing box coordinates.

The problem requires collecting all boxes starting and ending at (0,0),
and each box is on either x-axis or y-axis. The key idea is to find
the minimum path that visits all boxes and returns to origin.

We can think of the x-coordinates and y-coordinates separately.
For x-coordinates, we need to cover all values from min_x to max_x,
similarly for y-coordinates.
The optimal way is to move along x-axis to collect all x-coordinates,
then along y-axis to collect all y-coordinates, and so on.

However, a more precise idea:
- If we traverse along x-axis from leftmost to rightmost box,
  and then traverse the y-axis from bottom to top,
  the total path will be:
  distance_x = max_x - min_x
  distance_y = max_y - min_y
  But since we start at (0,0), and return to it,
  we need two trips: one for x-axis (going leftmost-rightmost)
  and one for y-axis (going bottom-top).
  Total moves = 2 * (max_x - min_x + max_y - min_y)

This is the minimized total distance.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    n = int(input())
    X = [0]  # Add origin point
    Y = [0]
    for i in range(n):
        x, y = map(int, input().split())
        X.append(x)
        Y.append(y)
    # Calculate max and min of x and y coordinates
    ans = max(X) - min(X) + max(Y) - min(Y)
    print(2 * ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/