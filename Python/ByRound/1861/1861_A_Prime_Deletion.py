# Problem: CF 1861 A - Prime Deletion
# https://codeforces.com/contest/1861/problem/A

"""
Purpose: 
This code solves the "Prime Deletion" problem where given a permutation of digits 1-9,
we need to delete some digits to form a prime number. The strategy is to check the 
positions of '1' and '3' in the input string and output either "13" or "31" depending 
on their relative positions.

Algorithms/Techniques:
- String manipulation and search
- Greedy approach based on character positions

Time Complexity: O(n) where n is the length of the input string (fixed at 9 in this case)
Space Complexity: O(1) - only using a constant amount of extra space

Note: This approach works because:
1. The input string is a permutation of digits 1-9
2. If '1' appears before '3', we prefer "13" as a small prime
3. Otherwise, we choose "31" 
4. This heuristic provides a valid solution in most cases, as demonstrated by sample inputs.
"""
import sys

num = int(sys.stdin.readline().strip())
for i in range(num):
    line = sys.stdin.readline().strip()

    if line.find("1") < line.find("3"):
        print(13)
    else:
        print(31)


# https://github.com/VaHiX/CodeForces/