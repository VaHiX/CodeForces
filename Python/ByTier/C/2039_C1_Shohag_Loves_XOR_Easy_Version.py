# Problem: CF 2039 C1 - Shohag Loves XOR (Easy Version)
# https://codeforces.com/contest/2039/problem/C1

"""
Algorithm: Brute Force with Optimization
Time Complexity: O(x * log(m)) per test case in worst case, but often much faster due to early breaks
Space Complexity: O(1)

This solution iterates through all possible values of `i` from 1 to x-1. For each `i`, it computes `y = x ^ i` and checks if `y` is within the range [1, m]. If so, it verifies whether the XOR result (x ^ y) is a divisor of either x or y (or both). This approach relies on the fact that for a given i, the corresponding y is uniquely determined by the XOR operation.

The key insight is that since y = x ^ i, we have x ^ y = x ^ (x ^ i) = i. So the check becomes: if i divides x or y, then it's valid.
"""

for _ in range(int(input())):
    x, m = map(int, input().split())
    t = 0
    for i in range(1, x):  # Loop from 1 to x-1
        y = x ^ i  # Compute y such that x ^ y = i
        if y > m:  # Skip if y exceeds m
            continue
        # Check if x ^ y (which equals i) divides either x or y
        if y % (x ^ y) == 0 or x % (x ^ y) == 0:
            t += 1
    print(t)


# https://github.com/VaHiX/CodeForces/