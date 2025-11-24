# Problem: CF 1239 A - Ivan the Fool and the Probability Theory
# https://codeforces.com/contest/1239/problem/A

"""
A. Ivan the Fool and the Probability Theory
Algorithms/Techniques: Dynamic Programming, Pattern Recognition
Time Complexity: O(n + m)
Space Complexity: O(n + m)

The problem asks to count the number of "random" pictures of size n x m,
where each cell has at most one adjacent cell of the same color.
This constraint leads to a pattern where rows must alternate in a specific way.

The solution uses precomputed values for sequences that represent valid row patterns.
For small grids (1x1, 1xm, nx1), direct formulas are used.
For larger grids, the answer is derived from the sequence k which represents
the number of valid configurations for each row size.

The recurrence relation for k follows a Fibonacci-like pattern where:
k[i] = (k[i-1] + k[i-2]) % M
"""

M = 10**9 + 7
k = [1, 4, 6, 10]  # Precomputed base values for the sequence
for i in range(100000):  # Extend the sequence for large inputs
    k.append((k[-1] + k[-2]) % M)  # Fibonacci-like recurrence

n, m = [int(xx) for xx in input().split()]  # Read n and m from input

if n == 1 and m == 1:  # Special case for 1x1 grid
    print(2)
    quit()

if min(n, m) == 1:  # If one dimension is 1 (row or column)
    # Answer is sum of valid sequences minus 1 for each dimension
    print((k[n - 1] + k[m - 1] - 1) % M)
else:
    # For larger grids, subtract 2 instead of 1
    print((k[n - 1] + k[m - 1] - 2) % M)


# https://github.com/VaHiX/codeForces/