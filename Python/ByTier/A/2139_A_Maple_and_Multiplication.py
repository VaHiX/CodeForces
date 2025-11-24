# Problem: CF 2139 A - Maple and Multiplication
# https://codeforces.com/contest/2139/problem/A

"""
Task: Minimum Operations to Make Two Numbers Equal

Algorithm:
- Given two positive integers a and b, we want to make them equal using minimum operations.
- Each operation allows us to multiply either a or b by any positive integer x.
- The key insight is based on the Least Common Multiple (LCM):
  - If a == b, no operations are needed (0).
  - If lcm(a,b) > a, we need one operation to make a equal to lcm(a,b).
  - If lcm(a,b) > b, we need one operation to make b equal to lcm(a,b).
- Therefore, the minimum number of operations is:
  - (lcm(a,b) > a) + (lcm(a,b) > b)
  
Time Complexity: O(log(min(a,b)) * t) where log(min(a,b)) is due to LCM computation and t is number of test cases.
Space Complexity: O(1) — only constant extra space used.

Input:
- First line contains number of test cases t
- Each test case has two integers a and b

Output:
- For each test case, output the minimum number of operations required
"""

t = int(input())
from math import lcm as f  # Import LCM function from math module

for _ in range(t):
    n, m = map(int, input().split())  # Read n and m
    l = f(n, m)  # Compute LCM of n and m
    print((l > n) + (l > m))  # Count how many of n,m need to be multiplied (0 or 1 for each)


# https://github.com/VaHiX/codeForces/