# Problem: CF 2155 D - Batteries
# https://codeforces.com/contest/2155/problem/D

import sys


def g():
    s = sys.stdin.readline()
    while s and s.strip() == "":
        s = sys.stdin.readline()
    return s.strip() if s else None


t = int(g())
for _ in range(t):
    n = int(g())
    gs = []
    i = 1
    while i <= n:
        gs.append([i])  # Initially each battery is in its own group
        i += 1
    f = 0  # Flag to indicate if a working pair is found
    while len(gs) > 1 and f == 0:
        i1 = -1  # Index of the smallest group
        i2 = -1  # Index of the second smallest group
        i = 0
        while i < len(gs):
            if i1 == -1 or len(gs[i]) < len(gs[i1]):
                i2 = i1
                i1 = i
            elif i2 == -1 or len(gs[i]) < len(gs[i2]):
                i2 = i
            i += 1
        a = gs[i1]
        b = gs[i2]
        # Remove the two groups from the list
        if i1 > i2:
            gs.pop(i1)  # Remove larger index first to avoid shifting
            gs.pop(i2)
        else:
            gs.pop(i2)
            gs.pop(i1)
        # Try all pairs of batteries in groups a and b until one works or we run out of tries
        i = 0
        while i < len(a) and f == 0:
            j = 0
            while j < len(b) and f == 0:
                print(a[i], b[j]) # Query two batteries
                sys.stdout.flush()
                r = g()
                if r is None:
                    sys.exit(0)
                x = int(r)
                if x == -1:
                    sys.exit(0)
                if x == 1: # Found a working pair
                    f = 1
                    break
                j += 1
            i += 1
        if f == 0:
            # If no working pair found in this round, merge the groups and continue
            k = 0
            while k < len(b):
                a.append(b[k])
                k += 1
            gs.append(a)
    if f == 0:
        pass

# Flowerbox:
"""
Problem: Find a working pair of batteries among n batteries, where at least 2 work.
Approach: Union-find like algorithm with grouping strategy.
- Initially each battery is in a group of size 1.
- At each step, merge the two smallest groups by testing all pairs between them.
- If any pair works, we're done.
- Otherwise, we merge the groups and continue.

Time Complexity: O(n^2) in worst case due to nested loops and merging.
Space Complexity: O(n^2) for storing groups and their contents during merging.
"""


# https://github.com/VaHiX/CodeForces/