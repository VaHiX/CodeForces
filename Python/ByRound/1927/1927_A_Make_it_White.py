# Problem: CF 1927 A - Make it White
# https://codeforces.com/contest/1927/problem/A

"""
Code Purpose:
This solution finds the minimum length of a continuous segment to paint white 
so that all cells in the strip become white. The approach is to identify the 
first and last black cell ('B') in the string and compute the length of the 
segment between them. This is the minimal segment that needs to be painted 
to cover all black cells.

Algorithms/Techniques:
- String traversal to find first and last 'B'
- Calculate distance between first and last 'B'

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables for computation
"""

for s in [*open(0)][2::2]:
    print(len(s.strip("W\n")))  # Remove leading/trailing 'W' and '\n', then get length


# https://github.com/VaHiX/CodeForces/