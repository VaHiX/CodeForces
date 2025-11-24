# Problem: CF 2027 B - Stalin Sort
# https://codeforces.com/contest/2027/problem/B

"""
B. Stalin Sort
Algorithms/Techniques: Brute-force with nested loops to check all possible subarrays for vulnerability.
Time Complexity: O(n^3) where n is the size of the array (due to triple nested loops).
Space Complexity: O(1) excluding input storage.

Stalin Sort is a humorous sorting algorithm that removes elements which are out of place,
instead of properly sorting them. An array is vulnerable if it can be sorted in non-increasing
order by repeatedly applying Stalin Sort on its subarrays.

The task is to find the minimum number of elements to remove to make the array vulnerable.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    ans = n - 1  # Initialize with worst case: keep only one element
    for j in range(n):
        cnt = 0
        for k in range(j + 1, n):
            if a[k] > a[j]:
                cnt += 1
        ans = min(ans, j + cnt)
    print(ans)


# https://github.com/VaHiX/codeForces/