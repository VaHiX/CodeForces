# Problem: CF 2123 G - Modular Sorting
# https://codeforces.com/contest/2123/problem/G

"""
G. Modular Sorting

Purpose:
This code solves a problem where we have an array of integers and support for two types of queries:
1. Update an element in the array.
2. Check if the array can be made non-decreasing using operations of the form a[i] := (a[i] + k) mod m.

Key Techniques:
- Preprocessing all divisors of m to determine valid modular increments.
- Efficiently tracking changes with a difference array for updates and prefix sums for querying.

Time Complexity: O(n * d(m) + q * n * d(m)) where d(m) is the number of divisors of m.
Space Complexity: O(n + d(m))

Algorithms:
- Modular arithmetic to simulate additions in modular space.
- Difference array technique to efficiently apply updates.
- Fast divisor enumeration using sqrt decomposition.
"""

import math


def get_factors(n):
    factors = set()
    for i in range(1, int(math.isqrt(n)) + 1):
        if n % i == 0:
            factors.add(i)
            factors.add(n // i)
    return sorted(factors)


for _ in range(int(input())):
    n, m, q = map(int, input().split())
    l = list(map(int, input().split()))
    t = get_factors(m)   # Get all divisors of m
    t.pop()              # Remove m itself to avoid redundant checks (since a[i] mod m stays unchanged)
    d = []
    c = 0
    for i in range(n):
        d.append(l[i] - c)   # Difference array to store incremental changes
        c = l[i]
    g = []
    l = [0] + l            # Prefix sum array for efficient range queries
    for i in range(len(t)):
        s = 0
        for j in range(n):
            s += d[j] % t[i]   # Compute total modulo sum for each divisor
        g.append([t[i], s])    # Store divisor and its total contribution
    
    for i in range(q):
        r = list(map(int, input().split()))
        if r[0] == 1:           # Update operation
            for j in range(len(t)):
                if r[1] != n:
                    a = l[r[1]] - l[r[1] - 1]      # Previous value before update
                    b = l[r[1] + 1] - l[r[1]]      # Next value after update
                    c = r[2] - l[r[1] - 1]         # New value for current position
                    d = l[r[1] + 1] - r[2]         # New next value after update
                    g[j][1] = (
                        g[j][1] - (a % t[j]) - (b % t[j]) + (c % t[j]) + (d % t[j])
                    )
                else:
                    a = l[r[1]] - l[r[1] - 1]
                    c = r[2] - l[r[1] - 1]
                    g[j][1] = g[j][1] - (a % t[j]) + (c % t[j])
            l[r[1]] = r[2]      # Update prefix array
        else:                   # Query operation
            for j in range(len(g)):
                if g[j][0] == math.gcd(m, r[1]):  # Find the correct divisor
                    if g[j][1] >= m:
                        print("NO")
                    else:
                        print("YES")
                    break


# https://github.com/VaHiX/codeForces/