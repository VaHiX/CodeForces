# Problem: CF 1848 C - Vika and Price Tags
# https://codeforces.com/contest/1848/problem/C

"""
Algorithm: Determine if a pair of arrays becomes "dull" (all elements of array 'a' become zero after repeated operations).
Techniques: 
- Use GCD to normalize the input arrays.
- Analyze parity (odd/even) of normalized values to determine if the process leads to all zeros.
- Key insight: After normalization, the process depends on the parity of numbers in the arrays and how they evolve.

Time Complexity: O(n * log(max(a[i], b[i]))) due to GCD computations and iteration.
Space Complexity: O(n) for storing the normalized arrays and parity indicators.

Approach:
1. For each element in the arrays, compute GCD and normalize the values.
2. Determine the pattern based on parity of the normalized values.
3. If all patterns are the same, the result is "YES", otherwise "NO".
"""

import sys

input = sys.stdin.readline


INF = 1 << 63
ceil = lambda a, b: (((a) + ((b) - 1)) // (b))



def do():
    n = int(input())
    oa = list(map(int, input().split()))
    ob = list(map(int, input().split()))
    import math

    c = []
    for i in range(n):
        x = math.gcd(oa[i], ob[i])
        if x == 0:
            continue
        oa[i] = oa[i] // x
        ob[i] = ob[i] // x

        if oa[i] == 0:
            c.append("a")
            continue
        if ob[i] == 0:
            c.append("b")
            continue
        if (abs(oa[i] + ob[i]) % 2) == 0:
            c.append("c")
            continue
        if oa[i] % 2 == 0:
            c.append("a")
            continue
        if ob[i] % 2 == 0:
            c.append("b")
            continue
    if len(c) == 0:
        print("YES")
        return
    if c.count(c[0]) == len(c):
        print("YES")
    else:
        print("NO")


q = int(input())
for _ in range(q):
    do()


# https://github.com/VaHiX/CodeForces/