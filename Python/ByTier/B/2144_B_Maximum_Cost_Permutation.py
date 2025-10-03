# Problem: CF 2144 B - Maximum Cost Permutation
# https://codeforces.com/contest/2144/problem/B

"""
B. Maximum Cost Permutation
Algorithms/Techniques: Greedy, Simulation, Array Manipulation

Time Complexity: O(n) amortized over all test cases
Space Complexity: O(n)

The problem asks to find the maximum possible cost of a permutation after replacing zeros.
Cost is defined as the minimum length of a contiguous subsegment that needs to be sorted
to make the entire permutation sorted.

Approach:
1. Identify which numbers are missing from the current array (those not present in 'a').
2. Replace zeros with these missing numbers.
3. Determine the minimum segment to sort by finding the leftmost and rightmost positions 
   where the array differs from the sorted version.
4. Return the length of that segment as the cost.

"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    manq = [True] * (n + 1)  # Boolean array to track which numbers are missing
    for ai in a:
        manq[ai] = False  # Mark used numbers as false
    manq = [x for x in range(1, n + 1) if manq[x]]  # Extract the missing numbers
    if a.count(0) == 1:
        assert len(manq) == 1
        a[a.index(0)] = manq[0]  # Replace one zero with the only missing number
    l = r = None
    for i in range(n):
        if a[i] != i + 1:  # Find where array differs from sorted array (1-indexed)
            if l is None:
                l = i
            r = i
    if l is None:
        print(0)  # Already sorted
    else:
        print(r - l + 1)  # Length of the unsorted segment


# https://github.com/VaHiX/codeForces/