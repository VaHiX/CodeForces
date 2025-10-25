# Problem: CF 2003 D1 - Turtle and a MEX Problem (Easy Version)
# https://codeforces.com/contest/2003/problem/D1

"""
Problem: Turtle and a MEX Problem (Easy Version)

Purpose:
This program computes the sum of f(i) for i from 0 to m, where f(k) is the maximum value
that can be achieved starting with x = k using mex operations on given sequences.

Approach:
1. For each sequence, we determine which numbers are missing from it (the MEX).
2. We compute a value `x` that represents the maximum possible MEX across all sequences.
3. Then, for a given `y`, we compute the sum of f(i) where i ranges from 0 to y.

Key Algorithms:
- Use set operations to find elements in each sequence.
- Compute the MEX (smallest missing non-negative integer) efficiently.
- Optimize with mathematical computation for large ranges.

Time Complexity: O(n * l), where n is number of sequences and l is average length of sequences.
Space Complexity: O(l), for storing sets of elements from sequences.
"""

import sys

t = int(sys.stdin.readline().strip())
for _ in range(t):
    n, y = map(int, sys.stdin.readline().strip().split())
    x = 0
    for i in range(n):
        s = set()
        a = [*map(int, sys.stdin.readline().strip().split())]
        m = a[0]  # Length of the sequence
        s = set(a[1:])  # Set of elements in the sequence (excluding first element)
        k = []
        for j in range(m + 2):  # Check up to m+2 to ensure we capture all relevant MEX candidates
            if j not in s:
                k.append(j)
        x = max(k[1], x)  # Take the second smallest missing number as the maximum possible MEX value
    q = x
    x = min(x, y)  # Clamp x to be no greater than y
    print((x + 1) * q + (y - x) * (y + x + 1) // 2)  # Mathematical formula for the result


# https://github.com/VaHiX/codeForces/