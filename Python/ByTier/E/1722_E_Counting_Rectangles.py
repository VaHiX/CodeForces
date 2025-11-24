# Problem: CF 1722 E - Counting Rectangles
# https://codeforces.com/contest/1722/problem/E

"""
Code Purpose:
This code solves the problem of counting rectangles that fit within specified bounds for multiple queries.
It uses a 2D prefix sum array to efficiently compute the sum of areas of rectangles satisfying both height and width constraints.

Algorithms/Techniques:
- 2D prefix sum technique for fast range sum queries
- Preprocessing rectangles into a 2D grid where each cell stores sum of areas
- For each query, iterate through valid height range and use prefix sums for width range

Time Complexity:
- Preprocessing: O(n * 1000^2) = O(n)
- Each query: O(h_b - h_s) = O(1000) = O(1)
- Overall: O(n + q * 1000) = O(n + q)

Space Complexity:
- O(1000^2) = O(10^6) = O(1) for the 2D array
"""

from sys import stdin

input = stdin.readline

for test in range(int(input())):
    n, q = map(int, input().split())
    # Initialize 2D array to store rectangle areas
    a = [[0] * (1001) for i in range(1001)]
    # Process each rectangle and add its area to the corresponding grid cell
    for i in range(n):
        h, w = map(int, input().split())
        a[h][w] += h * w
    # Build prefix sums for each row
    for i in range(1, 1001):
        for j in range(1, 1001):
            a[i][j] += a[i][j - 1]
    # Process each query
    for i in range(q):
        hw, ws, hb, wb = map(int, input().split())
        # Sum up the areas of rectangles that fit the constraints
        # For each valid height in range (hw, hb), sum areas in width range (ws, wb)
        print(sum(a[h][wb - 1] - a[h][ws] for h in range(hw + 1, hb)))


# https://github.com/VaHiX/CodeForces/