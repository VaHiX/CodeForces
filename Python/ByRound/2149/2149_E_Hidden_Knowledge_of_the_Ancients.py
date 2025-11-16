# Problem: CF 2149 E - Hidden Knowledge of the Ancients
# https://codeforces.com/contest/2149/problem/E

"""
E. Hidden Knowledge of the Ancients

Purpose:
This code solves the problem of counting the number of contiguous subarrays that satisfy two conditions:
1. The subarray contains exactly k distinct elements.
2. The length of the subarray is between l and r (inclusive).

Algorithm:
The solution uses a sliding window technique with two pointers to maintain windows with at most k and at most k-1 distinct elements.
For each right pointer position, we adjust left pointers to ensure that the window has exactly k distinct values.
We then compute how many valid windows exist within a certain range based on constraints l and r.

Time Complexity: O(n) where n is the length of the input array. Each element is processed at most twice (once by each pointer).
Space Complexity: O(n) for storing the elements of the input array and hash maps to track counts.

Techniques:
- Two-pointer sliding window approach
- Hash map for counting distinct elements
"""

import sys

input = lambda: sys.stdin.readline().strip()
from collections import defaultdict

for _ in range(int(input())):
    n, k, l, r = map(int, input().split())
    nums = input().split()
    # Attach empty string to make tuple (element, "")
    for i in range(n):
        nums[i] = (nums[i], "")
    j = 0       # Left pointer for window with at most k distinct elements
    jj = 0      # Left pointer for window with at most k-1 distinct elements
    dct = defaultdict(int)   # Keeps count of elements in current window for k distinct check
    dct2 = defaultdict(int)  # Keeps count of elements in current window for k-1 distinct check
    res = 0     # Result counter
    for i in range(n):
        # Add current element to both hash maps
        dct[nums[i]] += 1
        dct2[nums[i]] += 1
        
        # Shrink window until it has at most k distinct elements
        while len(dct) > k:
            dct[nums[j]] -= 1
            if dct[nums[j]] == 0:
                del dct[nums[j]]
            j += 1
            
        # Shrink second window until it has at most k-1 distinct elements
        while len(dct2) > (k - 1):
            dct2[nums[jj]] -= 1
            if dct2[nums[jj]] == 0:
                del dct2[nums[jj]]
            jj += 1
            
        # Compute valid range of left indices for current right index i
        x = max(j, i - r + 1)   # Minimum valid left index (based on k distinct constraint)
        y = min(jj - 1, i - l + 1)  # Maximum valid left index (based on k-1 distinct constraint and length requirement)
        
        # If valid range exists, add number of such subarrays to result
        if x <= y:
            res += y - x + 1
    print(res)


# https://github.com/VaHiX/CodeForces/