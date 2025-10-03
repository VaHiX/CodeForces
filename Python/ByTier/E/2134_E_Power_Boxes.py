# Problem: CF 2134 E - Power Boxes
# https://codeforces.com/contest/2134/problem/E

"""
E. Power Boxes

Purpose:
This code solves an interactive problem where we need to determine the hidden power values (1 or 2) of n boxes placed on a number line. 
We use swap and throw queries to deduce the power values efficiently in at most ⌈3n/2⌉ queries.

Algorithm:
The algorithm uses dynamic programming with reverse iteration to estimate the "chain length" of each position.
It then uses swaps to resolve ambiguities between adjacent positions, and finally determines the last box's value through a final throw.

Time Complexity: O(n) - Each test case processes n elements with constant-time operations per element.
Space Complexity: O(n) - For storing the DP array f and result array res.

Techniques:
- Dynamic Programming (reverse iteration)
- Interactive Problem Solving
- Greedy Swap & Throw Strategy
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


prt = lambda s: print(s, flush=1)


def main():
    n = II()
    f = [0] * (n + 2)  # f[i] stores the estimated chain length starting from position i
    f[n] = 1  # Base case for the last position
    for i in range(n - 1, 0, -1):  # Iterate backwards
        if f[i + 1] == f[i + 2]:  # If both next positions are equal, we increment chain length by one
            f[i] = 1 + f[i + 1]
        else:  # Otherwise ask for the value at i through a throw query
            prt(f"throw {i}")
            f[i] = II()
    res = [0] * (n + 1)  # Result array to store power values for each box
    todo = []  # List of positions requiring further resolution due to ambiguity
    for i in range(1, n):  # For all adjacent pairs
        if f[i] == f[i + 1]:  # Same chain length means both have the same power value (both are 2)
            res[i] = 2
        elif f[i + 1] > f[i + 2]:  # If next is greater than the one after that, it's a 1
            res[i] = 1
        else:  # Otherwise this position is ambiguous and needs resolution
            todo.append(i)
    for i in todo:  # Resolve each ambiguous pair
        prt(f"swap {i}")  # Swap to move box i to the right
        prt(f"throw {i+1}")  # Throw at new position (i+1)
        a = II()
        res[i] = 1 if a == f[i + 2] + 1 else 2  # Determine based on response
    prt(f"swap {n-1}")  # Final swap to prepare for last throw
    prt(f"throw {n-1}")  # Throw at the second-to-last box
    res[n] = 1 if II() == 2 else 2  # Determine last value
    prt(f"! " + " ".join(map(str, res[1:])))


for _ in range(II()):
    main()


# https://github.com/VaHiX/codeForces/