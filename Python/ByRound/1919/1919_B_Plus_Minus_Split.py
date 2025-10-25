# Problem: CF 1919 B - Plus-Minus Split
# https://codeforces.com/contest/1919/problem/B

"""
Algorithm: Plus-Minus Split
Purpose: To find the minimum penalty when splitting a sequence of + and - into subarrays.
Techniques: Greedy approach based on counting + and - characters.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1), only using a few variables for computation.

The key insight is that we want to minimize the sum of penalties, where each penalty 
is the absolute sum of the subarray multiplied by its length. The optimal strategy is 
to balance the number of + and - signs as much as possible to minimize the total penalty.
"""

def solve():
    n = int(input())  # Read length of the string
    s = input()       # Read the string of '+' and '-'
    p = s.count("+")  # Count number of '+'
    c = n - p         # Count number of '-'
    print(abs(p - c)) # Output the absolute difference between counts


_T = 1
_T = int(input())  # Read number of test cases
for _ in range(_T):
    solve()


# https://github.com/VaHiX/CodeForces/