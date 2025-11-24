# Problem: CF 2147 A - Shortest Increasing Path
# https://codeforces.com/contest/2147/problem/A

"""
Code Purpose:
This code solves a problem where we need to find the minimum number of steps to reach a point (x, y) 
in a 2D grid starting from (0, 0). The movement follows specific rules:
- First step is along x-axis, then y-axis, then x-axis, and so on (alternating).
- Each step must be strictly greater than the previous one.
- We can only move in positive directions.

Algorithms/Techniques:
Greedy approach with conditional logic based on the values of x and y.

Time Complexity: O(1) per test case - constant time operations for each input.
Space Complexity: O(1) - only using a fixed amount of extra space regardless of input size.

Input:
- Number of test cases t (1 ≤ t ≤ 10^4)
- For each test case: x and y (1 ≤ x, y ≤ 10^9)

Output:
- Minimum number of steps to reach (x, y), or -1 if impossible.
"""

t = int(input())
for _ in range(t):
    x, y = map(int, input().split())  # Read x and y coordinates
    
    if x < y:  # If x is smaller than y, we can directly go to y with one step
        print(2)
    elif y == 1:  # If y is 1, after moving x steps along x-axis, 
                  # next move must be at least 2 along y-axis, but we are only going to 1.
        print(-1)
    elif x >= y + 2:  # If x is significantly larger than y 
                      # we can reach in 3 steps (x, then y, then some more)
        print(3)
    else:  # Otherwise check if it reaches exactly or close to x,y with valid path
        print(-1)


# https://github.com/VaHiX/CodeForces/