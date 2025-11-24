# Problem: CF 1868 A - Fill in the Matrix
# https://codeforces.com/contest/1868/problem/A

"""
Code Purpose:
This code solves the problem of filling an n x m matrix with permutations of length m such that the beauty of the matrix (defined as the MEX of column values) is maximized.

Algorithms/Techniques:
- Greedy approach with pattern construction
- Utilizes the property that MEX of a set of numbers is the smallest non-negative integer not present in the set
- Constructs rows to ensure that column MEX values are as varied as possible

Time Complexity: O(n * m) - We iterate through all rows and columns once to construct the matrix.
Space Complexity: O(n * m) - The space required to store the matrix and output.
"""

import sys

for _ in range(int(input())):
    l = sys.stdin.readline().split()
    n = int(l[0])
    m = int(l[1])
    if m == 1:
        print(0)
        for i in range(n):
            sys.stdout.write(str(0) + "\n")
        continue
    k = min(m, n + 1)  # Determine the size of the repeating pattern
    sys.stdout.write(str(k) + "\n")
    # Generate first k-1 rows using a cyclic shift pattern to maximize diversity
    for i in range(k - 1):
        sys.stdout.write(
            " ".join(
                [str((i + j) % k) for j in range(k)] + [str(j) for j in range(k, m)]
            )
            + "\n"
        )
    # Fill remaining rows with a simple permutation 0..m-1
    for i in range(k - 1, n):
        sys.stdout.write(" ".join([str(j) for j in range(m)]) + "\n")


# https://github.com/VaHiX/CodeForces/