# Problem: CF 2067 E - White Magic
# https://codeforces.com/contest/2067/problem/E

"""
E. White Magic

Purpose:
This code finds the maximum possible length of a magical subsequence from a given sequence of non-negative integers.
A magical sequence satisfies the condition that for all prefixes, the minimum element is greater than or equal to the mex (minimum excluded value) of the suffix.

Algorithms/Techniques:
- Greedy approach with set-based MEX computation
- Reverse iteration through array to compute MEX efficiently

Time Complexity: O(n) per test case, where n is the length of input array.
Space Complexity: O(n) for storing elements in a set.

Input Format:
- First line contains number of test cases t.
- For each test case:
  - First line contains n (length of sequence)
  - Second line contains n integers (the sequence)

Output Format:
- For each test case, output the maximum possible length of a magical subsequence.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s = set()
    x = a.index(0) if 0 in a else -1  # Position of first zero, or -1 if no zero
    mex = 0
    for j in range(n - 1, -1, -1):  # Iterate from end to start
        if a[j] < mex:  # If current element is less than current mex, reset mex to 0 and break
            mex = 0
            break
        if a[j] or j == x:  # Add element to set if it's non-zero or it's the first zero
            s.add(a[j])
            while mex in s:  # Compute next mex by checking what's missing from the set
                mex += 1
    print(n - a.count(0) + int(mex != 0))  # Output result based on count of zeros and whether mex was updated


# https://github.com/VaHiX/codeForces/