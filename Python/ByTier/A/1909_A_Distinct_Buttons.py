# Problem: CF 1909 A - Distinct Buttons
# https://codeforces.com/contest/1909/problem/A

"""
Code Purpose:
This code determines whether it's possible to visit all special points on a 2D grid using at most 3 distinct movement buttons (U, D, R, L).
The algorithm analyzes the distribution of points across quadrants to decide if all points can be reached without pressing all 4 buttons.

Algorithms/Techniques:
- Quadrant classification: For each point, classify it based on x and y coordinates being positive, negative, or zero.
- Counting logic: Maintain counters for points in each of the four quadrants (and axes).
- Decision logic: If points exist in all four quadrants, it's impossible to visit them with only 3 buttons, hence return "NO".

Time Complexity: O(n) where n is the number of special points.
Space Complexity: O(1) as only a fixed number of variables are used (counters for quadrants).
"""

import sys

input = sys.stdin.readline


def main():
    t = int(input())  # Read number of test cases
    for _ in range(t):
        n = int(input())  # Read number of special points
        x_pos = x_neg = y_pos = y_neg = 0  # Counters for quadrants
        for _ in range(n):
            x, y = map(int, input().split())  # Read point coordinates
            if x < 0:
                x_neg += 1  # Point is in left side (negative x)
            elif x > 0:
                x_pos += 1  # Point is in right side (positive x)
            if y < 0:
                y_neg += 1  # Point is in bottom side (negative y)
            elif y > 0:
                y_pos += 1  # Point is in top side (positive y)
        # If all quadrants have at least one point, we need all 4 buttons
        if x_pos and x_neg and y_pos and y_neg:
            print("NO")
        else:
            print("YES")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/