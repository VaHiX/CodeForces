# Problem: CF 2066 B - White Magic
# https://codeforces.com/contest/2066/problem/B

"""
B. White Magic

Algorithm/Techniques:
- Greedy approach with preprocessing of MEX values
- For each prefix, compute the MEX of the suffix
- Use a greedy strategy to build a valid magical subsequence by removing duplicates and maintaining monotonicity

Time Complexity: O(n) amortized per test case, due to the preprocessing and linear traversal.
Space Complexity: O(n) for storing arrays and sets.

The code finds the maximum length of a magical subsequence in the given sequence.
A magical sequence satisfies that for all positions i, the minimum of the prefix up to i
is greater than or equal to the MEX (minimum excluded value) of the suffix from i+1 onwards.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    n = int(input())
    a = [*map(int, input().split())]
    
    # If there are no zeros, the whole sequence is magical
    if a.count(0) == 0:
        print(n)
        return

    # Remove consecutive zeros to optimize processing
    fg = 0
    b = []
    for i in a:
        if i == 0 and fg == 1:
            continue
        if i == 0:
            b.append(i)
            fg = 1
            continue
        b.append(i)

    # Precompute MEX values from right to left
    mex = [0] * (len(b) + 1)
    vis = set()
    for i in range(len(b) - 1, -1, -1):
        vis.add(b[i])
        mex[i] = mex[i + 1]
        while mex[i] in vis:
            mex[i] += 1

    # Greedily check if the sequence can be made magical
    fg2 = 1
    mn = b[0]
    for i in range(1, len(b)):
        if mn < mex[i]:
            fg2 = 0
        mn = min(mn, b[i])
    
    # Output result: original length minus number of zeros plus additional flag
    print(n - a.count(0) + fg2)


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/codeForces/