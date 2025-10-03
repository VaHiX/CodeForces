# Problem: CF 2082 D - Balancing
# https://codeforces.com/contest/2082/problem/D

"""
Problem: Balancing

Purpose:
This code solves the problem of making an array strictly increasing with minimum operations.
Each operation allows replacing a contiguous subarray with any values preserving the relative order constraints.

Algorithms/Techniques:
- Greedy approach to count "blocks" of non-increasing elements.
- Use two pointers to identify segments that need modification.
- Check if modifying a segment can reduce total operations by optimizing boundary conditions.

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing the input array.

Input Format:
- First line contains number of test cases t.
- Each test case consists of:
  - Line 1: integer n (length of array)
  - Line 2: n space-separated integers representing the array elements

Output Format:
- For each test case, output a single integer: minimum operations needed to make array strictly increasing
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    l1 = list(map(int, input().split()))
    cnt = 0
    # Count number of positions where current element is greater than or equal to next one
    for i in range(n - 1):
        if l1[i] >= l1[i + 1]:
            cnt += 1
    # Minimum operations needed based on blocks of non-increasing sequences
    ans = (cnt + 1) // 2
    if ans == 0:
        print(ans)
        continue
    l = -1
    r = -1
    # Find the first position where a[i] >= a[i+1]
    for i in range(n - 1):
        if l1[i] >= l1[i + 1]:
            l = i
            break
    # Find the last position where a[i-1] >= a[i]
    for i in range(n - 1, 0, -1):
        if l1[i - 1] >= l1[i]:
            r = i
            break
    # Optimization: check if increasing the segment's boundary reduces operations
    if l1[r] - l1[l] < r - l and cnt % 2 == 0:
        ans += 1
    print(ans)


# https://github.com/VaHiX/codeForces/