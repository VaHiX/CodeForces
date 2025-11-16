# Problem: CF 2162 F - Beautiful Intervals
# https://codeforces.com/contest/2162/problem/F

"""
Algorithm: Beautiful Intervals
Purpose: To find a permutation of integers 0 to n-1 such that the mex of all mex values of intervals is minimized.
Techniques:
- Difference array technique for counting interval overlaps
- Greedy rearrangement of elements to minimize mex of result set M

Time Complexity: O(n * m) due to constructing difference arrays and iterating through intervals.
Space Complexity: O(n) for storing difference arrays and the answer permutation.

The approach uses prefix sum technique (difference array) to count how many intervals cover each position.
Then, we try different permutations based on overlap conditions to minimize mex(M).
"""

import sys

input = sys.stdin.readline


def readInt():
    return int(input())


def readArray(type=int, container=list):
    return container(map(type, input().split()))


def readBasic():
    return readInt(), readArray()


import itertools

for t in range(readInt()):
    n, m = readArray()
    # pref[i] stores how many intervals contain position i
    pref = [0] * (n + 1)
    # two[i] stores overlap for intervals of length > 1 at position i
    two = [0] * (n + 1)
    # other[i] stores overlap information for intervals starting from i
    other = [0] * (n + 1)
    
    # Process intervals using difference array
    for _ in range(m):
        l, r = readArray()
        pref[l - 1] += 1
        pref[r] -= 1
        if l != r:
            two[l - 1] += 1
            two[r - 1] -= 1
            other[l] += 1
            other[r] -= 1
    
    # Compute prefix sums for the difference arrays
    pref = list(itertools.accumulate(pref))
    two = list(itertools.accumulate(two))
    other = list(itertools.accumulate(other))
    
    # Initialize default answer as [1,2,3,...,n-1,0]
    ans = [(i + 1) % n for i in range(n)]
    
    # Try shifting array to reduce the mex based on overlap conditions
    for i in range(n - 1):
        # If number of intervals covering position i equals total intervals passing through it
        if two[i] == pref[i]:
            ans = [(j - i + n) % n for j in range(n)]
            break
    
    # Try further shifts
    for i in range(1, n):
        if other[i] == pref[i]:
            ans = [(i - j + n) % n for j in range(n)]
            break
    
    # If all positions are covered by same number of intervals
    for i in range(n):
        if pref[i] == m:
            ans = [(j - i + n) % n for j in range(n)]
            break
    
    print(" ".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/