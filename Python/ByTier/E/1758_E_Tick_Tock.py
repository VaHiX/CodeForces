# Problem: CF 1758 E - Tick, Tock
# https://codeforces.com/contest/1758/problem/E

"""
Purpose:
This code solves the "Tick, Tock" puzzle problem where we need to determine the number of ways to assign values to empty cells in a grid such that the entire grid becomes solvable. A grid is solvable if all clocks can be made to display the same time using row/column shifts.

The approach uses Union-Find (Disjoint Set Union) to group columns that must have the same relative shift. Each row contributes to a constraint that affects the column shifts. The solution leverages modular arithmetic for large exponents and efficiently counts valid assignments.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression and offset tracking
- Modular exponentiation for computing number of valid assignments
- Constraint propagation across rows

Time Complexity:
O(n * m * α(n*m)) where α is the inverse Ackermann function, which is nearly constant in practice.

Space Complexity:
O(m) for storing Union-Find structures and auxiliary arrays.
"""

import sys

input = sys.stdin.readline

MOD = 10**9 + 7


def f(x):
    # Find root of x with path compression
    r = x
    s = 0
    while r != g[r]:
        s += o[r]
        r = g[r]
    ret = r, s

    # Update offsets and parent pointers for path compression
    while x != r:
        o[x], s = s, s - o[x]
        g[x], x = r, g[x]

    return ret


(t,) = map(int, input().strip().split())

allans = []
for _ in range(t):
    n, m, h = map(int, input().strip().split())

    ans = 0
    g = list(range(m + 1))  # Union-Find parent array
    o = [0] * (m + 1)       # Offset array to store cumulative shifts
    for i in range(n):
        a = list(map(int, input().strip().split()))
        li = -1
        lx = -1
        for j, x in enumerate(a, start=1):
            if x != -1:
                if li == -1:
                    li, lx = j, x
                else:
                    # Get root and offset of current column and reference column
                    rj, oj = f(j)
                    rl, ol = f(li)
                    # Compute required shift difference based on constraint
                    op = ((x - lx) - (oj - ol)) % h
                    if rj == rl:
                        # If same group but incompatible shifts, grid is unsolvable
                        if op != 0:
                            ans = -1
                            break
                    else:
                        # Merge groups and set required offset
                        g[rj] = rl
                        o[rj] = op
        if ans == -1:
            # Skip reading remaining rows if unsolvable
            for _ in range(n - i - 1):
                input()
            break
        if li == -1:
            ans += 1  # Count empty rows
    if li == -1:
        ans -= 1  # Adjust count for row with all empty entries

    if ans == -1:
        ans = 0  # Unsolvable case
    else:
        # Process final assignment of remaining columns
        for i, x in enumerate(a, start=1):
            if x != -1:
                g[f(i)[0]] = 0  # Set parent of root to 0 for consistency
        for i in range(1, m + 1):
            if f(i)[0] == i:
                ans += 1  # Count distinct groups
        # Compute total valid configurations using modular exponentiation
        ans = pow(h, ans, MOD)
    print(ans)


# https://github.com/VaHiX/CodeForces/