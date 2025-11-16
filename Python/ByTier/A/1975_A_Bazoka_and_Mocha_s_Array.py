# Problem: CF 1975 A - Bazoka and Mocha's Array
# https://codeforces.com/contest/1975/problem/A

"""
Problem: Determine if an array can be sorted by performing at most one rotation (split and swap prefix/suffix).

Algorithm:
- Count the number of positions where a[i] < a[i-1] in the array.
- If there is more than one such position, it's not possible to sort the array with one rotation.
- If there is exactly one such position, check if rotating at that point results in a sorted array.
- If there are zero such positions, the array is already sorted.

Time Complexity: O(n) - Single pass through the array.
Space Complexity: O(n) - Storing the array elements.

Techniques:
- Rotation check via counting inversions (local decreases)
- Direct simulation of rotation logic.
"""

import sys


def solve():
    line = sys.stdin.readline().split()
    n = int(line[0])
    line = sys.stdin.readline().split()
    a = [int(x) for x in line]
    cnt = 0
    # Count the number of decreasing transitions
    for i in range(n):
        if a[i] < a[i - 1]:
            cnt += 1
    # If there are more than one decreasing transitions, it's not sortable by one rotation
    if cnt > 1:
        print("No")
    else:
        print("Yes")


if __name__ == "__main__":
    line = sys.stdin.readline().split()
    T = int(line[0])
    for t in range(T):
        solve()


# https://github.com/VaHiX/CodeForces/