# Problem: CF 2020 C - Bitwise Balancing
# https://codeforces.com/contest/2020/problem/C

"""
Bitwise Balancing Problem

Algorithm:
The problem requires finding a value 'a' such that (a|b) - (a&c) = d.
We use a mathematical insight: if we fix the bits of 'a' where 'b' has 1s,
we can determine the remaining bits by solving the equation bitwise.

Key Insight:
Let's consider a bit position:
- If b[i] == 1, then a[i] can be either 0 or 1.
- The expression becomes: (a[i] | b[i]) - (a[i] & c[i]) = d[i]
- Since b[i] = 1, the left side becomes: (a[i] | 1) - (a[i] & c[i]) = 1 - (a[i] & c[i]) if a[i] = 0,
  or (1) - (c[i]) if a[i] = 1.

By trying a = b ^ d, we are essentially setting a such that:
- a & b = 0 (if b[i] = 1, then a[i] = 0) 
- Then we check whether it satisfies the condition.
This works because we are using XOR to determine possible bits.

Time Complexity: O(1) per test case, since we only perform fixed-bit operations.
Space Complexity: O(1), as we use only a constant amount of extra space.
"""

import sys

input = lambda: sys.stdin.readline().strip()
for _ in range(int(input())):
    b, c, d = map(int, input().split())
    a = b ^ d
    if (a | b) - (a & c) == d:
        print(a)
    else:
        print(-1)

# https://github.com/VaHiX/CodeForces/