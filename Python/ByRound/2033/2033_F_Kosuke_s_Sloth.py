# Problem: CF 2033 F - Kosuke's Sloth
# https://codeforces.com/contest/2033/problem/F

"""
F. Kosuke's Sloth

Purpose:
This code computes the index of the n-th Fibonacci number that is divisible by k.
It uses properties of Fibonacci numbers modulo k to find the cycle length and then
uses this cycle to determine the position of the n-th such number efficiently.

Algorithms/Techniques:
- Modular arithmetic with Fibonacci sequence
- Cycle detection in modular Fibonacci sequence
- Mathematical optimization to avoid generating all Fibonacci numbers

Time Complexity: O(k) per test case, where k is the modulus.
Space Complexity: O(1), constant space usage.

The solution works by:
1. Finding the cycle length of Fibonacci numbers modulo k.
2. Using this cycle to determine how many steps are needed to reach the n-th multiple of k.
3. Returning the result modulo 10^9 + 7.
"""

for _ in range(int(input())):
    n, k = map(int, input().split(" "))
    a, b, c = 0, 1 % k, 1  # Initialize Fibonacci values and step counter
    while b:  # Loop until we find the cycle (when b becomes 0)
        a, b = b, (a + b) % k  # Compute next Fibonacci number mod k
        c += 1  # Increment step counter
    print((c * n) % (10**9 + 7))  # Multiply cycle length by n and apply modulo


# https://github.com/VaHiX/codeForces/