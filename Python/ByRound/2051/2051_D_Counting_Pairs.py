# Problem: CF 2051 D - Counting Pairs
# https://codeforces.com/contest/2051/problem/D

"""
D. Counting Pairs

Purpose:
This code counts the number of "interesting" pairs (i, j) where removing elements at positions i and j 
from the array results in a remaining sum that is between x and y inclusive.

Algorithm:
- For each element a[i], we compute the valid range of second elements a[j] such that:
  x <= total_sum - a[i] - a[j] <= y
  => (total_sum - y) <= a[i] + a[j] <= (total_sum - x)
- We use a two-pointer technique after sorting the array to efficiently count valid pairs.

Time Complexity: O(n log n) per test case due to sorting and linear traversal with two pointers
Space Complexity: O(1) excluding input storage

Input Format:
- First line: number of test cases t
- For each test case:
  - First line: n, x, y
  - Second line: n integers a[0] to a[n-1]

Output Format:
- For each test case: number of valid pairs (i, j) such that i < j and the remaining sum is in [x, y]
"""

for _ in range(int(input())):
    n, x, y = map(int, input().split())
    a = sorted(map(int, input().split()))
    res, l, r, s = 0, 0, 0, sum(a)  # s is total sum, l and r are pointers for two-pointer technique
    for i in range(n - 1, -1, -1):  # iterate from largest element to smallest
        # Move l forward while a[l] + a[i] < (s - y) -> means too small to satisfy lower bound
        while l < n and a[l] + a[i] < s - y:
            l += 1
        # Move r forward while a[r] + a[i] <= (s - x) -> upper bound for valid pairs
        while r < n and a[r] + a[i] <= s - x:
            r += 1
        # Count of valid j's for current i: min(r, i) - min(l, i)
        # This ensures j is in range [l, r) and j < i (because we're iterating backwards)
        res += min(r, i) - min(l, i)
    print(res)


# https://github.com/VaHiX/codeForces/