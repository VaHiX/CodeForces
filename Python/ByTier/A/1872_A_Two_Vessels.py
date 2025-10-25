# Problem: CF 1872 A - Two Vessels
# https://codeforces.com/contest/1872/problem/A

"""
Code Purpose:
This code solves the problem of finding the minimum number of moves to make the water levels in two vessels equal, 
using a cup with fixed capacity. The approach is mathematical: 
- Calculate the absolute difference between the two vessel amounts.
- Determine how many moves are needed by dividing the difference by twice the cup capacity, 
  rounding up to cover any remainder.

Algorithms/Techniques:
- Mathematical calculation using ceiling division
- Modular arithmetic to determine if an extra move is needed

Time Complexity: O(1) - constant time operation
Space Complexity: O(1) - only using a fixed amount of extra space
"""

for _ in range(int(input())):
    a, b, c = map(int, input().split())  # Read the initial amounts in vessels and cup capacity
    itog = (abs(a - b) // (2 * c)) + 1 * (abs(a - b) % (2 * c) != 0)  # Calculate minimum moves
    print(itog)  # Output the result


# https://github.com/VaHiX/CodeForces/