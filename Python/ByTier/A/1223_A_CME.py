# Problem: CF 1223 A - CME
# https://codeforces.com/contest/1223/problem/A

"""
Problem: CME (Correct Match Equation)
Purpose: Given n matches, determine the minimum number of additional matches to buy 
         to form a valid equation a + b = c where all values are positive integers.
         All matches in the equation must be used.

Algorithm/Techniques:
- Mathematical analysis of match count requirements for valid equations
- Pattern recognition from examples

Time Complexity: O(1) - constant time per query
Space Complexity: O(1) - constant space usage

Examples:
n=2 -> need 2 extra to make |+|=|| (3+1=4)
n=5 -> need 1 extra to make ||+|=||| (2+3=5)  
n=8 -> no extra needed for 1+3=4 or 2+2=4
n=11 -> need 1 extra to make ||+||||=|||||| (2+6=8)
"""

s = int(input())
for i in range(s):
    n = int(input())
    if n == 1:
        print(3)
    elif n == 2:
        print(2)
    elif n % 2 == 0:
        print(n % 2)  # For even n > 2, we need 0 extra matches
    elif n % 2 == 1:
        print(1)      # For odd n, we need 1 extra match


# https://github.com/VaHiX/codeForces/