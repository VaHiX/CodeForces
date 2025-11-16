# Problem: CF 2084 D - Arcology On Permafrost
# https://codeforces.com/contest/2084/problem/D

"""
D. Arcology On Permafrost

Algorithms/Techniques:
- Greedy approach with mathematical optimization to determine the maximum possible mex after at most m operations.
- The idea is to find an optimal period `max_` such that repeating a sequence of length `max_` allows us to control the mex effectively.
- Time Complexity: O(n) per test case (linear in input size due to loop and print operations)
- Space Complexity: O(1) excluding input/output storage

The approach:
1. Compute maximum valid period `max_` based on constraints.
2. Construct a sequence by repeating values from 0 to max_-1 modulo max_.
"""

t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    max_ = 0
    # Find maximum possible period that satisfies condition
    for i in range(k, n):
        if n // i >= m + 1:  # Check if we can split into more than m+1 parts with length i
            max_ = i
    max_ = max(k, max_)  # Ensure it's at least k
    # Generate and print sequence of length n using period max_
    for i in range(n):
        print(i % max_, end=" ")
    print()


# https://github.com/VaHiX/codeForces/