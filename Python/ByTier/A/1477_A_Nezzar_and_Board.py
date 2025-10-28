# Problem: CF 1477 A - Nezzar and Board
# https://codeforces.com/contest/1477/problem/A

"""
Problem: Nezzar and Board

Algorithm:
- The operation allowed is to select two numbers x and y and write 2x - y on the board.
- This operation can generate new numbers in arithmetic progressions.
- If we sort the initial array, the differences between consecutive elements form a set.
- The GCD of all these differences gives us the smallest step size possible in the arithmetic progression.
- A number k is reachable if and only if (k - first_element) is divisible by this GCD.

Time Complexity: O(n log n) per test case due to sorting and GCD computation.
Space Complexity: O(n) for storing the array and differences.

This approach works because:
1. The set of numbers that can be generated using the operation 2x - y is essentially an arithmetic progression.
2. If all initial numbers are congruent modulo GCD of their differences, then any number reachable will also be congruent to this value.
3. The check ensures that k lies in the same arithmetic progression as the initial array elements.

"""

import math
import sys

input = sys.stdin.readline
for ___ in range(int(input())):  # Loop through test cases
    n, k = [int(xx) for xx in input().split()]  # Read n and k
    a = [int(Ss) for Ss in input().split()]  # Read array of numbers
    a = sorted(a)  # Sort the array to process differences
    r = []
    for i in range(1, n):  # Calculate differences between consecutive elements
        r.append(a[i] - a[i - 1])
    ee = 0
    for i in range(n - 1):  # Compute GCD of all differences
        ee = math.gcd(ee, r[i])
    if (k - a[0]) % ee:  # If k is not reachable using arithmetic progression step size
        print("NO")
    else:
        print("YES")  # K can be generated


# https://github.com/VaHiX/codeForces/