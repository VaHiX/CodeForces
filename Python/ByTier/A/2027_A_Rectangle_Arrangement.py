# Problem: CF 2027 A - Rectangle Arrangement
# https://codeforces.com/contest/2027/problem/A

"""
Problem: Minimum Perimeter of Black Regions After Stamping

Algorithms/Techniques:
- Greedy approach: To minimize the total perimeter of connected black regions,
  we want to maximize the overlap between stamps.
- For each test case, we find the maximum width and height among all stamps.
- The optimal arrangement is to place all stamps such that they align along
  one dimension (e.g., all aligned vertically or horizontally).
- The resulting shape will be a rectangle with dimensions (max_width x max_height),
  and its perimeter is 2 * (max_width + max_height).

Time Complexity: O(n) per test case, where n is the number of stamps.
Space Complexity: O(1), only using constant extra space.

Input:
- Number of test cases t
- For each test case:
    - Number of stamps n
    - Width and height of each stamp

Output:
- Minimum sum of perimeters of connected black regions
"""

for _ in range(int(input())):  # Process each test case
    ma1 = 0  # Track maximum width across all stamps
    ma2 = 0  # Track maximum height across all stamps
    for i in range(int(input())):  # For each stamp
        a, b = map(int, input().split())  # Read stamp dimensions
        ma1 = max(ma1, a)  # Update max width
        ma2 = max(ma2, b)  # Update max height
    print(2 * (ma1 + ma2))  # Output the minimal perimeter


# https://github.com/VaHiX/codeForces/