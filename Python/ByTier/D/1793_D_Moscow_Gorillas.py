# Problem: CF 1793 D - Moscow Gorillas
# https://codeforces.com/contest/1793/problem/D

""" D. Moscow Gorillas
https://codeforces.com/contest/1793/problem/D

Algorithms/Techniques: 
    - Preprocessing positions of elements in both permutations
    - Two-pointer technique with careful tracking of MEX boundaries
    - Efficient calculation of valid subarrays using geometric properties

Time Complexity: O(N)
Space Complexity: O(N)

The problem asks to count pairs of indices (l, r) where the MEX of subarrays p[l:r+1] and q[l:r+1] are equal.
The key insight is to track the positions of all elements 1 to N in both arrays, then consider how MEX changes as we expand the window.
We process MEX values in order and maintain the current range [l, r] that contains all elements up to the current MEX.
When a new element enters this range we update the count using geometric formula for valid subarrays.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
output = sys.stdout.write


def debug(*args):
    if os.environ.get("debug") in [None, "0"]:
        return
    from inspect import currentframe, getframeinfo
    from re import search

    frame = currentframe().f_back
    s = getframeinfo(frame).code_context[0]
    r = search(r"\((.*)\)", s).group(1)
    vnames = r.split(", ")
    var_and_vals = [f"{var }={val }" for var, val in zip(vnames, args)]
    prefix = f"{currentframe ().f_back .f_lineno :02d}: "
    print(f'{prefix }{", ".join (var_and_vals )}')


INF = float("inf")


def solve(N, P, Q):
    # posp[i] = position of element i in permutation p
    # posq[i] = position of element i in permutation q
    posp, posq = [-1] * (N + 1), [-1] * (N + 1)
    for i, (p, q) in enumerate(zip(P, Q)):
        posp[p] = posq[q] = i

    # Initialize with position of element 1
    p, q = posp[1], posq[1]
    l, r = min(p, q), max(p, q)
    # Count subarrays where MEX = 1
    # Left part: [0, l], middle: [l+1, r-1], right part: [r+1, N-1]
    res = l * (l + 1) // 2 + (N - r - 1) * (N - r) // 2 + (r - l - 1) * (r - l) // 2

    # Process MEX from 2 to N
    for mex in range(2, N + 1):
        p, q = posp[mex], posq[mex]
        # If current element is outside our window [l, r]
        if not (l <= p <= r or l <= q <= r):
            # Calculate how many left extensions can we have
            nl = l + 1
            if p < l:
                nl = min(nl, l - p)
            if q < l:
                nl = min(nl, l - q)
            # Calculate how many right extensions can we have
            nr = N - r
            if p > r:
                nr = min(nr, p - r)
            if q > r:
                nr = min(nr, q - r)
            # Add valid combinations
            res += nl * nr
        # Update the window
        l, r = min(l, p, q), max(r, p, q)

    # Add 1 for the special case when the full array is considered once
    return res + 1


def main():
    N = int(input())
    P = list(map(int, input().split()))
    Q = list(map(int, input().split()))
    res = solve(N, P, Q)
    print(res)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/