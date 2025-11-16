# Problem: CF 1909 E - Multiple Lamps
# https://codeforces.com/contest/1909/problem/E

"""
Code Purpose:
This code solves the "Multiple Lamps" problem, where we need to press buttons to toggle lamps such that at most ⌊n/5⌋ lamps are on.
Each button toggles all lamps whose index is a multiple of that button's index.
There are constraints on button pressings: if you press button u, you must also press button v.
The approach uses precomputed combinations of button presses for small n (up to 19) and checks against constraints.

Algorithms/Techniques:
- Precomputation of all valid button combinations for small n (1-19)
- Bit manipulation for tracking lamp states and button presses
- Constraint checking using inclusion of required buttons
- Brute-force search over precomputed combinations

Time Complexity: O(1) average-case for each query (precomputation + lookup)
Space Complexity: O(1) (precomputed data is fixed size)
"""

import sys

input = sys.stdin.readline


def how(p):
    """
    Precompute all possible lamp states for a given set of pressed buttons.
    Uses bit manipulation to simulate lamp toggling.
    """
    state = 0
    switch = 0
    for i in range(1, 20):
        if (i in p) != bool(state & (1 << i)):
            switch |= 1 << i
            for j in range(i, 20, i):
                state ^= 1 << j
    for i in range(5, 20):
        if max(p) <= i and len([x for x in p if x <= i]) <= i // 5:
            poss[i].add(switch & ((1 << (i + 1)) - 1))


# Precompute possible button combinations for different values of n (5 to 19)
poss = {i: set() for i in range(5, 20)}

for i in range(1, 20):
    how((i,))
    for j in range(i + 1, 20):
        how((i, j))
        for k in range(j + 1, 20):
            how((i, j, k))

for _ in range(int(input())):
    n, m = map(int, input().split())

    # Handle special cases
    if n >= 20 or n == 15:
        print(n)
        print(" ".join(str(x + 1) for x in range(n)))
        for _ in range(m):
            input()
    elif n < 5:
        print(-1)
        for _ in range(m):
            input()
    else:
        # Initialize children array to track required button constraints
        children = [0] * (n + 1)
        for _ in range(m):
            i, j = [int(x) for x in input().split()]
            children[i] |= 1 << j

        # Check each precomputed combination for validity
        for switch in poss[n]:
            # For each pressed button in the combination, verify constraints
            for i in range(1, n + 1):
                if switch & (1 << i):
                    if children[i] & switch != children[i]:
                        break
            else:
                # If all constraints are satisfied, output the solution
                print(bin(switch).count("1"))
                print(" ".join(str(x) for x in range(1, n + 1) if switch & (1 << x)))
                break
        else:
            # If no valid combination found, output -1
            print(-1)


# https://github.com/VaHiX/CodeForces/