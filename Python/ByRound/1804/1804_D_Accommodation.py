# Problem: CF 1804 D - Accommodation
# https://codeforces.com/contest/1804/problem/D

""" D. Accommodation
https://codeforces.com/contest/1804/problem/D 

Algorithms/Techniques: Greedy approach to maximize and minimize occupied apartments
Time Complexity: O(n * m) where n is number of floors and m is windows per floor
Space Complexity: O(1) excluding input storage

The problem involves determining the minimum and maximum number of occupied apartments
given a grid of windows (0 = dark, 1 = bright). Each floor has fixed numbers of:
- m/4 two-bedroom apartments (2 consecutive windows)
- m/2 one-bedroom apartments (1 window)

To minimize occupied apartments:
- Pack as many two-bedroom apartments as possible into bright windows.
- Use greedy to pair consecutive bright windows for two-bedroom apartments.
- Remaining bright windows belong to one-bedroom apartments.

To maximize occupied apartments:
- Distribute bright windows among one-bedroom apartments to leave maximum pairs.
- Use greedy to minimize number of two-bedroom apartments formed from bright windows.

Both strategies are applied per floor independently.
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


def solve(N, M, grid):
    mn = mx = 0
    for row in grid:
        tot = row.count("1")  # Total number of bright windows in this floor

        # Calculate minimum occupied apartments:
        # Try to form as many two-bedroom apartments as possible
        two = i = 0
        while i < M:
            if i + 1 < M and row[i] == row[i + 1] == "1":
                two += 1
                i += 2  # Skip next window since it's part of a two-bedroom
            else:
                i += 1
        # Min occupied = total bright windows minus those we must use as pairs
        # At most M//4 two-bedroom apartments are allowed
        mn += tot - min(two, M // 4)

        # Calculate maximum occupied apartments:
        # Try to leave as many windows as possible to be single ones
        two = i = 0
        while i < M:
            # If either window in pair is dark, we can form a two-bedroom
            # (i.e., we don't count this pair towards single windows)
            if i + 1 < M and (row[i] == "0" or row[i + 1] == "0"):
                two += 1
                i += 2
            else:
                i += 1
        # Max occupied = total bright windows minus pairs that could be formed
        # So if we have 0 pairs, all are used as singles; if we have M//4 pairs,
        # then we minimize singles, maximizing total occupied
        mx += tot - (M // 4 - min(two, M // 4))

    return mn, mx


def main():
    N, M = list(map(int, input().split()))
    grid = [input().decode().strip() for _ in range(N)]
    res = solve(N, M, grid)
    print(*res)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/