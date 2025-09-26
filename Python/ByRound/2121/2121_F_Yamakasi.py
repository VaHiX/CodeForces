# Problem: CF 2121 F - Yamakasi
# https://codeforces.com/contest/2121/problem/F

"""
F. Yamakasi

Purpose:
    Count the number of subsegments of an array whose sum equals 's' and maximum element equals 'x'.

Algorithm:
    - Use a prefix sum array to quickly compute subarray sums.
    - Use a sliding window technique with a hash map to track how many times each prefix sum has occurred.
    - For each new element in the prefix sum array, we check if any prior prefix sum satisfies the condition 
      that current_sum - prior_sum = s and max of subarray is x.
    - When encountering an element greater than x, reset the tracking window.

Time Complexity:
    O(n) per test case, where n is the length of the array.

Space Complexity:
    O(n) for storing prefix sums and hash map.
"""

import sys

MOD = 1e9 + 7


def input():
    return sys.stdin.readline().strip()


t = int(input())
for tcs in range(t):
    n, s, x = map(int, input().split())
    sums = [0] + list(map(int, input().split()))
    for i in range(1, n + 1):
        sums[i] = sums[i - 1] + sums[i]
    cnt = {}
    j = 0
    res = 0
    for i in range(1, n + 1):
        # If the element itself equals x, we start a new window from here
        if sums[i] - sums[i - 1] == x:
            while j < i:
                if sums[j] not in cnt:
                    cnt[sums[j]] = 0
                cnt[sums[j]] += 1
                j += 1
        # If the element is greater than x, we reset and clear the window
        if sums[i] - sums[i - 1] > x:
            j = i
            cnt.clear()
        # Check for valid subsegment ending at index i with sum s and max x
        res += cnt.get(sums[i] - s, 0)
    print(res)


# https://github.com/VaHiX/codeForces/