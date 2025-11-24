# Problem: CF 2056 D - Unique Median
# https://codeforces.com/contest/2056/problem/D

"""
Problem: Count the number of "good" subarrays in a given array.
A subarray is good if both its lower and upper medians are equal when sorted.
This is equivalent to checking that the middle elements of the sorted subarray are equal.

Algorithm:
- For each possible median value (x from 1 to 10), we process all subarrays and check
  whether they could have x as their median.
- We transform the input array into a binary array b where:
    - If a[i] > x, set b[i] = 1
    - Else if a[i] <= x, set b[i] = -1
- Using prefix sums and a counter array, we compute how many subarrays have a specific
  sum that would make them "good" for median x.
- Finally, subtract the number of non-good subarrays from total subarrays.

Time Complexity: O(11 * n) = O(n), where n is the length of the array (constant 11 due to max value 10).
Space Complexity: O(n), for storing prefix sums and counters.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = [0] * n
    res = 0
    for x in range(1, 11):  # Loop through all possible median values (1 to 10)
        for i in range(n):
            b[i] = 1 if a[i] > x else -1  # Transform array: 1 for > x, -1 otherwise
        pre = [0] * n
        sum_val = n  # Initial prefix sum shifted to avoid negative indices
        for i in range(n):
            pre[i] = sum_val
            sum_val += b[i]
        cnt = [0] * (2 * n + 1)  # Counter for prefix sums
        sum_val = n
        j = 0
        for i in range(n):
            if a[i] == x:  # When current element equals the median candidate
                while j <= i:  # Update counter for all valid prefixes ending at index i
                    cnt[pre[j]] += 1
                    j += 1
            sum_val += b[i]
            res += cnt[sum_val]  # Count matching prefix sums that form a valid subarray
    print(n * (n + 1) // 2 - res)  # Total subarrays minus bad ones gives good subarrays


# https://github.com/VaHiX/codeForces/