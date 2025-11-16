# Problem: CF 1774 B - Coloring
# https://codeforces.com/contest/1774/problem/B

"""
Algorithm/Technique: 
- The problem involves placing colors on a tape such that:
  1. Each color is used exactly as many times as specified in the input.
  2. No k consecutive cells have the same color.
- Strategy:
  - For every k consecutive cells, they must all have distinct colors.
  - This means the maximum number of times any color is used cannot exceed the number of times we can place that color in non-overlapping groups of size k.
  - We compute the number of such "groups" as ceil(n/k).
  - If the maximum required frequency of a color is less than or equal to the total number of groups, it is possible.
  - If it's equal, we also check how many colors have that maximum frequency and whether it is compatible with the remaining cells.

Time Complexity: O(m), where m is the number of colors. We scan the array of colors once to find max and count.
Space Complexity: O(1), as we use only a constant amount of extra space.
"""

from math import ceil
from sys import stdin

input = lambda: stdin.readline().strip()


def solve(cells, colors, diff, times):
    # Calculate the number of full k-sized windows in the tape
    plus = cells % diff
    # Number of non-overlapping windows of size k
    seq = ceil(cells / diff)
    # Find the maximum frequency of any color and how many colors have that frequency
    max_num = 0
    max_count = 0
    for el in times:
        if max_num < el:
            max_num = el
            max_count = 1
        elif max_num == el:
            max_count += 1
    # If the maximum number of uses of any color is less than the number of windows,
    # then it's possible to distribute the colors
    if seq > max_num:
        return True
    elif seq == max_num:
        # If it's equal, we need to check if enough space exists in the overlapping regions
        return max_count <= plus or plus == 0
    return False


def main():
    ans = []
    for _ in range(int(input())):
        ans.append(
            "YES"
            if solve(*map(int, input().split()), list(map(int, input().split())))
            else "NO"
        )
    print("\n".join(ans))


main()


# https://github.com/VaHiX/CodeForces/