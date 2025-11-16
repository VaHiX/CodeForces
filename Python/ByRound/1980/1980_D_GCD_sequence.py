# Problem: CF 1980 D - GCD-sequence
# https://codeforces.com/contest/1980/problem/D

"""
Algorithm/Technique:
- The problem requires us to determine if removing exactly one element from an array can make its GCD-sequence non-decreasing.
- First, we compute the initial GCD-sequence of adjacent elements.
- If the sequence is already non-decreasing, we output "YES".
- Otherwise, we identify positions where the sequence decreases and try removing elements near those positions to see if it becomes non-decreasing.
- The approach involves checking if removing one element can fix all decrease points.

Time Complexity: O(n^2) in worst case due to multiple checks of potential removals, but in practice with optimizations, it performs well.
Space Complexity: O(n) for storing arrays and intermediate sequences.
"""

import sys

input = sys.stdin.readline

from math import gcd


def calc(ix):
    # If index is out of bounds, return False
    if 0 <= ix < len(A):
        pass
    else:
        return False
    B = []
    # Build new GCD sequence after removing element at index ix
    for i in range(n - 1):
        if ix == i:
            continue  # Skip the element to be removed
        if i == ix - 1:  # Special handling for consecutive elements
            if i + 2 < len(A):
                B.append(gcd(A[i], A[i + 2]))
            else:
                pass
        else:
            B.append(gcd(A[i], A[i + 1]))

    # Check if new sequence is sorted
    if B == sorted(B):
        return True
    else:
        return False


t = int(input())
for tests in range(t):
    n = int(input())
    A = list(map(int, input().split()))

    # Compute initial GCD sequence
    B = []
    for i in range(n - 1):
        B.append(gcd(A[i], A[i + 1]))

    # If sequence is already non-decreasing
    if sorted(B) == B:
        print("YES")
        continue

    # Find positions where sequence decreases
    LIST = []
    for i in range(len(B) - 1):
        if B[i] > B[i + 1]:
            LIST.append(i)

    # If too many decrease points, impossible to fix with one removal
    if len(LIST) >= 5:
        print("NO")
        continue

    # Expand list of candidates to try removing
    LIST2 = []
    for l in LIST:
        LIST2.append(l - 1)
        LIST2.append(l)
        LIST2.append(l + 1)
        LIST2.append(l + 2)

    # Remove duplicates
    LIST2 = set(LIST2)

    flag = 0
    # Try removing each candidate element
    for l in LIST2:
        if calc(l) == True:
            flag = 1
            break

    if flag == 1:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/