# Problem: CF 2113 B - Good Start
# https://codeforces.com/contest/2113/problem/B

"""
B. Good Start

Purpose:
This code determines whether a rectangular roof of size w x h can be completely tiled 
with identical a x b roofing sheets, given that two sheets are already placed in 
non-overlapping positions. The solution checks if the existing placement allows 
for full coverage by verifying divisibility conditions along the x and y axes.

Algorithms/Techniques:
- Mathematical analysis of tiling constraints
- Modular arithmetic for checking alignment
- Greedy approach based on coordinate differences

Time Complexity: O(1) - Constant time operations for each test case
Space Complexity: O(1) - Only a constant amount of extra space is used

Input Format:
- First line: number of test cases t
- For each test case:
  - Line 1: w, h, a, b (roof and sheet dimensions)
  - Line 2: x1, y1, x2, y2 (coordinates of two placed sheets)

Output Format:
For each test case, output "Yes" if full tiling is possible, otherwise "No".
"""

for _ in range(int(input())):
    w, h, a, b = map(int, input().split())  # Read roof dimensions and sheet dimensions
    x1, y1, x2, y2 = map(int, input().split())  # Read coordinates of two placed sheets
    
    # Check if the existing placement allows for full tiling:
    # For x-axis: if difference between x-coordinates is divisible by a (and not zero), 
    # or for y-axis: if difference between y-coordinates is divisible by b (and not zero)
    if ((x2 - x1) % a == 0 and x1 != x2) or ((y2 - y1) % b == 0 and y1 != y2):
        print("Yes")
    else:
        print("No")


# https://github.com/VaHiX/codeForces/