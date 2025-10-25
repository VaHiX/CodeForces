# Problem: CF 2137 A - Collatz Conjecture
# https://codeforces.com/contest/2137/problem/A

"""
Algorithm: Bitwise Left Shift Operation
Techniques: Bit manipulation

Time Complexity: O(1)
Space Complexity: O(1)

This code computes the result of left-shifting the value of x by k bits,
which is equivalent to multiplying x by 2^k. This is a fast bitwise operation
that directly calculates the result without loops or recursion.
"""

for _ in range(int(input())):  # Read number of test cases and iterate
    k, x = map(int, input().split())  # Read k (shift amount) and x (value to shift)
    print(x << k)  # Perform left bit shift operation: x * 2^k


# https://github.com/VaHiX/codeForces/