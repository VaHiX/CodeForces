# Problem: CF 2121 A - Letter Home
# https://codeforces.com/contest/2121/problem/A

"""
Task: Minimum Steps to Visit All Positions

Algorithms/Techniques: Sorting, Greedy Approach

Time Complexity: O(n log n) due to sorting the array (though in this problem n <= 10, so it's effectively constant)
Space Complexity: O(1) - only using a few variables for computation

The problem involves finding the minimum number of steps to visit all given positions 
on a number line starting from position 's'. The key insight is that we need to 
find the optimal path that minimizes total steps while covering all required positions.

This solution works by:
1. Identifying the leftmost (l) and rightmost (h) points in the array
2. Computing the minimal distance from 's' to either end
3. Returning the sum of: (distance between ends) + (min distance from s to either end)
"""

t = int(input())
for i in range(t):
    n, s = map(int, input().split())  # Read number of positions and starting position
    a = list(map(int, input().split()))  # Read the array of positions
    l, h = a[0], a[-1]  # Leftmost and rightmost positions in sorted array
    r = (h - l) + min(abs(s - l), abs(s - h))  # Compute minimum steps
    print(r)


# https://github.com/VaHiX/codeForces/