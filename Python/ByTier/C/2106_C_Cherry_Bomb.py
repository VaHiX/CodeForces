# Problem: CF 2106 C - Cherry Bomb
# https://codeforces.com/contest/2106/problem/C

"""
C. Cherry Bomb

Purpose:
This problem determines the number of valid arrays `b` that can be filled in such that 
arrays `a` and `b` are complementary (i.e., there exists an integer x such that a[i] + b[i] = x for all i).
Some elements in `b` are missing and marked as -1. These must be filled with values from [0, k] such that 
the resulting array is complementary to `a`.

Algorithms/Techniques:
- Complementary array check using a fixed value x = a[i] + b[i]
- For each missing element in `b`, determine if there's a valid range for it
- If the required value falls outside [0, k], then no solution exists
- Handle cases where all elements of `b` are -1 separately

Time Complexity: O(n) per test case
Space Complexity: O(1)

"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    
    # If all elements in b are missing (-1), then check if any value in [0,k] works
    if b.count(-1) == n:
        print(k - max(a) + min(a) + 1)
    else:
        f, s = 1, 0
        # Find a valid x from the known elements of b 
        for i in range(n):
            if b[i] != -1:
                s = a[i] + b[i]
        # Check all elements and see if they are consistent with x
        for i in range(n):
            if (b[i] != -1 and a[i] + b[i] != s) or (
                b[i] == -1 and not (0 <= s - a[i] <= k)
            ):
                f = 0  # Inconsistent -> no valid array b
        print(f)


# https://github.com/VaHiX/codeForces/