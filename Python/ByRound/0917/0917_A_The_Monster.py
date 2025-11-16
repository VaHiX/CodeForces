# Problem: CF 917 A - The Monster
# https://codeforces.com/contest/917/problem/A

"""
Algorithm: Dynamic Programming with Prefix Balance
Techniques: 
- Brute-force over all substrings
- Maintain balance of parentheses and count of question marks
- Adjust balance when encountering invalid closing bracket
Time Complexity: O(n^2) where n is the length of string s
Space Complexity: O(1) - only using a few variables for computation

The solution checks for each substring whether it can be made into a valid 
bracket sequence by replacing '?' with '(' or ')'. For each such valid 
substring, we increment the answer counter.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
lii = lambda: list(map(int, input().split()))

s = input()
n = len(s)
ans = 0
for i in range(n):
    left, mark = 0, 0
    for j in range(i, n):
        if s[j] == "(":
            left += 1
        elif s[j] == ")":
            left -= 1
        else:
            left -= 1  # Treat '?' as ')'
            mark += 1
        if left < 0:
            # If balance goes negative, we must have at least one '?'
            # to convert to '(' to fix it
            if mark == 0:
                break  # No '?' left to fix, invalid substring
            mark -= 1  # Use one '?' as '('
            left += 2  # Balance increased by 2 (from -1 to +1)
        if left == 0:
            ans += 1  # Found a valid bracket sequence

print(ans)


# https://github.com/VaHiX/CodeForces/