# Problem: CF 1893 A - Anonymous Informant
# https://codeforces.com/contest/1893/problem/A

"""
Algorithm: Anonymous Informant
Purpose: Determine if a given array b can be obtained from some initial array a through k cyclic left shifts,
         where each shift is determined by choosing a fixed point x (a[x] == x) and shifting left by x positions.

Techniques:
- Simulation with modulo arithmetic
- Early termination when invalid condition is detected

Time Complexity: O(n * min(n, k)) per test case
Space Complexity: O(n) for storing the array b

This solution simulates the reverse process of applying operations to retrieve the original array,
and checks whether the resulting state is valid.
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n, k = map(int, input().split())
    b = list(map(int, input().split()))
    j = n - 1  # Start from the last index of the array b
    for i in range(min(n, k)):  # Iterate up to min(n, k) times to avoid unnecessary work
        if b[j] <= n:  # Check if b[j] is a valid index (within bounds)
            j = (j - b[j]) % n  # Simulate reverse operation: move back by b[j] positions with wrap-around
        else:
            print("No")  # Invalid shift value, break and output "No"
            break
    else:
        print("Yes")  # If loop didn't break, all operations were valid


# https://github.com/VaHiX/codeForces/