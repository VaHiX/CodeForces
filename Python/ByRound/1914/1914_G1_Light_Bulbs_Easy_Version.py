# Problem: CF 1914 G1 - Light Bulbs (Easy Version)
# https://codeforces.com/contest/1914/problem/G1

"""
Algorithm: Light Bulbs (Easy Version)

This problem involves determining the minimum number of initially lit bulbs to turn on such that all bulbs can be lit using two allowed operations:
1. Turn on a bulb of a color if exactly one bulb of that color is already on.
2. Turn on a bulb between two bulbs of the same color if both are on and the second bulb is between them.

Approach:
- Identify segments of bulbs where no bulb of a given color appears beyond the current segment.
- For each such segment, compute how many initial bulbs must be lit from this segment (at least one per pair of bulbs that can be activated together).
- Multiply the number of such minimal sets across all segments to get the total count.
- Time complexity: O(n^2) per test case in worst case, but with constraints on sum of n^2 being <= 10^6, it's efficient.
- Space complexity: O(n) for storing indices and boundaries.

The algorithm processes the color positions and identifies segments, then calculates the number of valid sets for each segment using a greedy strategy.
"""

import sys
from itertools import pairwise

input = sys.stdin.readline
MOD = 10**9 + 7


def read_array(factory):
    return [factory(num) for num in input().strip().split()]


def print_array(arr):
    print(" ".join(map(str, arr)))


def solve(n, c):
    # right_match[color] stores the last index of that color
    right_match = (n + 1) * [-1]
    for i, color in enumerate(c):
        right_match[color] = i

    # Find segment boundaries: where a new segment starts (no more bulbs of previous color appear)
    right_boundaries = [0]
    maxi = 0
    for i in range(len(c)):
        if i > maxi:
            right_boundaries.append(i)

        color = c[i]
        maxi = max(maxi, right_match[color])
    right_boundaries.append(2 * n)

    # Count total number of sets of minimum size
    num_sets = 1
    for l, r in pairwise(right_boundaries):
        # Set of colors that can be activated in this segment
        reaches = set()
        reaches.add(c[l])
        l += 1
        while l <= r - 1:
            maxi = l
            for p in range(l, r):
                if p > maxi:
                    l = p
                    break

                if c[p] in reaches:
                    # If we found a color already reachable, activate this bulb
                    reaches.add(c[l])
                    l += 1
                    break

                color = c[p]
                # Extend the maximum index reachable
                maxi = max(maxi, right_match[color])

                if maxi == r - 1:
                    # If we've reached end, this bulb can be activated
                    reaches.add(c[l])
                    l += 1
                    break

        # Each segment's contribution: 2 * number of independent pairs
        ans = len(reaches) * 2
        num_sets = (num_sets * ans) % 998244353

    # First result: number of segments, second result: number of sets
    return [len(right_boundaries) - 1, num_sets]


if __name__ == "__main__":
    t = int(input())

    for _ in range(t):
        n = int(input())
        c = read_array(int)
        ans = solve(n, c)
        print_array(ans)


# https://github.com/VaHiX/CodeForces/