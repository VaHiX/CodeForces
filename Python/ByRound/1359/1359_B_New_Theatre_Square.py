# Problem: CF 1359 B - New Theatre Square
# https://codeforces.com/contest/1359/problem/B

"""
B. New Theatre Square

Algorithms/Techniques:
Greedy approach with dynamic programming concept for each row.
For each row, we process from left to right and decide whether to use a 1x1 tile or a 1x2 tile based on which is cheaper.
We count the number of '.' characters and consecutive ".." patterns in each row.
For each group of consecutive white squares, we greedily determine if using 1x2 tiles is more beneficial than 1x1 tiles.

Time Complexity: O(n * m) where n is the number of rows and m is the number of columns.
Space Complexity: O(1) as we only use a constant amount of extra space per test case.

Input:
- t: number of test cases
- For each test case:
  - n, m, x, y: dimensions of grid and costs of tiles
  - n lines of m characters representing the grid ('.' for white, '*' for black)

Output:
- Minimum total cost to cover all white squares using 1x1 or 1x2 tiles.
"""

for _ in range(int(input())):  # Process each test case
    n, m, x, y = map(int, input().split())  # Read grid dimensions and tile costs
    p = 0  # Initialize total cost
    for i in range(n):  # Iterate over each row
        s = input()  # Read the current row as a string
        a = s.count(".")  # Count total white squares in this row
        b = s.count("..")  # Count consecutive pairs of white squares
        # For each row, compute minimum cost to cover all white squares:
        # Option 1: Use only 1x1 tiles (a * x)
        # Option 2: Use as many 1x2 tiles as possible (b * y) + remaining 1x1 tiles ((a - 2*b) * x)
        p += min(a * x, b * y + (a - 2 * b) * x)
    print(p)  # Print the total minimum cost for this test case


# https://github.com/VaHiX/codeForces/