# Problem: CF 2031 D - Penchick and Desert Rabbit
# https://codeforces.com/contest/2031/problem/D

"""
D. Penchick and Desert Rabbit

Purpose:
This code solves a problem where a desert rabbit jumps between trees according to specific rules.
The goal is to compute for each starting tree the maximum height among all reachable trees.

Algorithm:
1. For each position i, we precompute the maximum height reachable by moving forward (from left to right).
2. Then, we process from right to left:
   - If the current max height is greater than the minimum encountered so far,
     then we update it based on the next node's value.
   - Keep track of the minimum value seen so far to determine valid jumps.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array and result

Input:
- Number of test cases t
- For each test case:
  - n (number of trees)
  - Array a of n integers representing tree heights

Output:
- For each test case, n integers representing maximum reachable height from each tree.
"""

import sys

input = sys.stdin.readline


def fn():
    n = int(input())
    a = list(map(int, input().split()))
    ans = a.copy()
    
    # Preprocessing: compute max height reachable going forward (left to right)
    for i, x in enumerate(ans):
        if i:
            ans[i] = max(ans[i], ans[i - 1])
    
    # Backward pass: adjust values based on valid jumps from right to left
    nextMin = a[-1]
    for i in range(n - 2, -1, -1):
        if ans[i] > nextMin:
            ans[i] = ans[i + 1]
        nextMin = min(nextMin, a[i])
    
    print(*ans)


for _ in range(int(input())):
    fn()


# https://github.com/VaHiX/codeForces/