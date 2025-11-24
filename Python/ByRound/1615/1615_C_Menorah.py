# Problem: CF 1615 C - Menorah
# https://codeforces.com/contest/1615/problem/C

"""
Problem: Menorah
Algorithm: Greedy with Bit Manipulation
Time Complexity: O(n) per test case
Space Complexity: O(1)

We are given two binary strings a and b representing initial and target candle states.
Each operation selects a lit candle, which toggles all candles except the selected one.
We determine the minimum operations to transform a into b or return -1 if impossible.

Key observations:
1. When we perform an operation on a lit candle i:
   - Candle i stays lit
   - All other candles flip their state
2. The number of operations needed corresponds to how many positions differ between a and b,
   but depends on the parity of lit candles in initial and target states.

The solution checks:
- If total lit candles in a equals lit candles in b: we can solve with c1 operations
- If total lit candles in a equals n - (lit candles in b) + 1: we can solve with n - c1 operations
"""

import sys

input = sys.stdin.readline
T = int(input())
for i in range(T):
    n = int(input())
    a = input()
    b = input()
    c1 = 0
    c2 = a.count("1")  # Count of lit candles in initial state
    c3 = b.count("1")  # Count of lit candles in target state
    for i in range(n):
        if a[i] != b[i]:  # Count mismatched positions
            c1 += 1
    m1, m2 = sys.maxsize, sys.maxsize
    if c2 == c3:
        m1 = c1  # If same number of lit candles, minimum operations is c1
    if c2 == n - c3 + 1:
        m2 = n - c1  # If the relation holds, operations needed is n - c1
    if m1 == m2 == sys.maxsize:
        print(-1)  # Impossible to transform
    else:
        print(min(m1, m2))  # Return minimum operations


# https://github.com/VaHiX/CodeForces/