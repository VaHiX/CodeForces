# Problem: CF 2120 D - Matrix game
# https://codeforces.com/contest/2120/problem/D

"""
D. Matrix game

Purpose:
This code finds the lexicographically smallest tuple (n, m) such that for any n x m matrix filled with integers from 1 to k,
Aryan can always find a submatrix of size a x b where all elements are equal.

Algorithm:
- The solution uses combinatorics and pigeonhole principle to determine minimum required n and m.
- For a given a, b, k, we compute the minimum n and m such that it's impossible for Harshith (playing optimally)
  to avoid creating an a x b submatrix with all equal elements.
- The mathematical approach involves calculating how many distinct values are needed and using modular arithmetic.

Time Complexity: O(a * log(mod)) per test case due to modular inverse computation.
Space Complexity: O(1) - only using constant extra space.

Input:
Each test case contains three integers a, b, k (1 ≤ a, b, k ≤ 10^5)

Output:
For each test case, output two integers n and m modulo 10^9 + 7.
"""

import sys

input = lambda: sys.stdin.readline().strip()
mod = 10**9 + 7
t = int(input())
for _ in range(t):
    a, b, x = map(int, input().split())
    # Compute n using the formula derived from combinatorial bounds
    n = (a - 1) * x + 1
    m = 1
    # Compute m using factorials and modular inverse to find necessary columns
    for i in range(a):
        m = (m * (((n - i) * pow(i + 1, -1, mod)) % mod)) % mod
    # Final adjustment for the number of rows needed
    m = (m * x * (b - 1) + 1) % mod
    print(n % mod, m % mod)


# https://github.com/VaHiX/codeForces/