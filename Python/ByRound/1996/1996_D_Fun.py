# Problem: CF 1996 D - Fun
# https://codeforces.com/contest/1996/problem/D

"""
Algorithm: Triplets Counting with Optimized Enumeration
Techniques: Two-pointer style enumeration with symmetry optimization

Time Complexity: O(sqrt(n) * sqrt(n)) = O(n) per test case in worst case, but with early termination and optimizations
Space Complexity: O(1) - only using a few variables

This solution counts the number of ordered triplets (a, b, c) of positive integers such that:
1. ab + ac + bc <= n
2. a + b + c <= x

The key optimization is to iterate over 'a' and 'b' up to sqrt(n), and then derive the maximum valid 'c'
based on constraints. It uses symmetry to avoid redundant counting of triplets where a != b.
"""

import sys

input = lambda: sys.stdin.readline().strip()

t = int(input())
for _ in range(t):
    n, x = map(int, input().split())

    ans = 0
    # Iterate a from 1 to sqrt(n) for efficiency
    for a in range(1, int(n ** (0.5)) + 1):
        # Iterate b from a to sqrt(n) to maintain order and avoid duplicate pairs
        for b in range(a, int(n ** (0.5)) + 1):
            # Calculate the maximum possible value of c based on both constraints
            c = min(x - a - b, (n - a * b) // (a + b))

            # Only count if c is valid (positive and greater than or equal to b)
            if c >= b:
                # If a == b, we're dealing with symmetric cases; count as 3 permutations
                if a == b:
                    ans += 3 * (c - b) + 1
                # Otherwise, count 6 permutations (since a, b can be swapped in 2 ways, and c can have multiple values)
                else:
                    ans += 6 * (c - b) + 3

    print(ans)


# https://github.com/VaHiX/CodeForces/