# Problem: CF 2056 A - Shape Perimeter
# https://codeforces.com/contest/2056/problem/A

"""
Task: Calculate the perimeter of a colored shape formed by pressing an m×m square stamp multiple times on paper.

The stamp is moved according to a sequence of (x_i, y_i) steps and leaves a colored square at each position.
The shape formed is a connected region, and we need to compute its perimeter.

Algorithm:
- Start with the initial stamp at (0, 0), contributing 4*m to the perimeter.
- For each movement operation:
  - Add 2*a + 2*b to the total perimeter for each step.
- This method computes the total perimeter by summing all external edges exposed due to overlapping or movement.

Time Complexity: O(n) per test case
Space Complexity: O(1)

"""

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())  # Read number of operations and stamp size
    s = 4 * m  # Start with perimeter of the first square
    input()  # Skip blank line (if any)
    for i in range(n - 1):  # Process all steps except the first one
        a, b = map(int, input().split())  # Get movement values
        s += 2 * a + 2 * b  # Add contribution to perimeter from this step
    print(s)  # Output the total perimeter


# https://github.com/VaHiX/codeForces/