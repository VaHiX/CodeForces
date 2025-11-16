# Problem: CF 1120 A - Diana and Liana
# https://codeforces.com/contest/1120/problem/A

"""
A. Diana and Liana

Problem Description:
Given a sequence of m flowers, we need to cut k-length pieces (workpieces) to form n wreaths.
Each wreath must contain at least the types in sequence b with required frequencies.
We can remove some elements from the liana such that there are still at least n workpieces,
and at least one workpiece fits Diana's pattern.

Algorithms/Techniques:
- Sliding window technique with frequency counting
- Two-pointer approach to find valid subarrays
- Greedy strategy to determine which flowers to remove

Time Complexity: O(m * k)
Space Complexity: O(m)

"""

import sys
from array import array

input = lambda: sys.stdin.buffer.readline().decode().strip()
inp = lambda dtype: [dtype(x) for x in input().split()]
inp_2d = lambda dtype, n: [dtype(input()) for _ in range(n)]
inp_2ds = lambda dtype, n: [inp(dtype) for _ in range(n)]
ceil1 = lambda a, b: (a + b - 1) // b
debug = lambda *x: print(*x, file=sys.stderr)
out = []


def get_right():
    dis = set()
    for i in range(s):  # Count initial flower types needed
        cb[b[i]] += 1
        dis.add(b[i])
    for i in range(m):
        if cb[a[i]]:
            ca[a[i]] += 1
        if ca[a[i]] == cb[a[i]]:
            dis.discard(a[i])
        if not dis:  # All required types are available
            return i
    exit(print(-1))


def valid(l, r):
    divl, modl = divmod(l, k)  # Calculate how many full workpieces we can make from left side
    divr, modr = divmod(m - r - 1, k)  # Calculate how many full workpieces we can make from right side
    le, splits = r - l + 1, divl + divr + 1  # Count remaining flowers and total possible workpieces
    if splits < n:
        return 0  # Not enough workpieces to meet the requirement
    ret = array("i", list(range(1, modl + 1)) + list(range(m + 1 - modr, m + 1)))
    # Build list of positions to remove from edges (those that can be kept at the ends)
    while splits > n and divl:  # If we have more workpieces than needed, reduce from left
        splits -= 1
        divl -= 1
        ret.extend(range(modl + 1, modl + k + 1))
        modl += k
    while splits > n and divr:  # If we have more workpieces than needed, reduce from right
        splits -= 1
        divr -= 1
        modr += k
        ret.extend(range(m - modr + 1, m - modr + k + 1))
    for i in range(l, r + 1):  # Go through the window to determine which internal positions to remove
        if cb[a[i]]:
            cb[a[i]] -= 1  # If current flower type is needed, decrease count of required flowers
        elif le > k:  # If there are more flowers than needed in this region and current one isn't essential, remove it
            le -= 1
            ret.append(i + 1)  # Append position to remove (converted to 1-based indexing)
    exit(print(f"{m - n * k}\n{' '.join(map(str, ret))}"))


def adjust(l, r):
    while r < m - 1 and r - l + 1 < k:  # Adjust current right boundary to include enough elements
        r += 1
        ca[a[r]] += 1
    return r


max_ = 5 * 10**5 + 1  # Max possible flower type value (used for frequency array)
m, k, n, s = inp(int)  # Read input parameters
a, b = array("i", inp(int)), array("i", inp(int))  # Read flower sequence and schematic
ca, cb = array("i", [0] * max_), array("i", [0] * max_)  # Frequency arrays for current window and target pattern

r = adjust(0, get_right())  # Get correct rightmost index with valid set of flowers
valid(0, r)  # Check if current window is valid

for l in range(1, m - k + 1):  # Slide the window along the liana
    if cb[a[l - 1]]:  # If the leftmost element was part of required flower types
        ca[a[l - 1]] -= 1  # Decrease its count (as it will be removed from current window)
        while r < m - 1 and ca[a[l - 1]] < cb[a[l - 1]]:  # Expand the window if required element count is still less
            r += 1
            ca[a[r]] += 1
        if ca[a[l - 1]] < cb[a[l - 1]]:  # If there's not enough of a necessary type now, exit early
            break
    r = adjust(l, r)  # Adjust window based on new left boundary
    valid(l, r)  # Check validity for this window

print(-1)  # If no valid solution found within the loop, output -1


# https://github.com/VaHiX/codeForces/