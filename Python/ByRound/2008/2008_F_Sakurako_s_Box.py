# Problem: CF 2008 F - Sakurako's Box
# https://codeforces.com/contest/2008/problem/F

"""
F. Sakurako's Box
Algorithm: Expected value of product of two randomly chosen elements from array
Technique: Mathematical expectation formula using sum and sum of squares
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to compute the expected value of the product of two randomly 
selected elements from an array. The expected value is computed as:
E[X*Y] = (sum of all products of pairs) / (total number of pairs)

Using algebraic manipulation:
- Total pairs = n*(n-1)/2
- Sum of all products = (sum of elements)^2 - sum of squares of elements) / 2
- Final result = (sum of all products) * 2 / (n*(n-1)) mod p

This is simplified to:
((s^2 - t) * pow(n*(n-1), -1, p)) % p
where s = sum of elements and t = sum of squares.
"""

import sys

input = sys.stdin.buffer.readline
p = 10**9 + 7
for _ in range(int(input())):
    n = int(input())
    s = t = 0
    for x in map(int, input().split()):  # Read and accumulate sum and sum of squares
        s += x
        t += x * x
    print(((s % p) ** 2 - t) * pow(n * (n - 1), p - 2, p) % p)  # Compute final result in modular arithmetic


# https://github.com/VaHiX/codeForces/