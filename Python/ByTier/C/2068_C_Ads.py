# Problem: CF 2068 C - Ads
# https://codeforces.com/contest/2068/problem/C

"""
Problem: C. Ads
Purpose: Given a list of video durations and a parameter k, we want to find the minimum number of ads to watch when choosing the order of videos optimally. An ad is shown either after 3 videos or after k minutes have passed since last ad.

Algorithms/Techniques:
- Greedy approach with two pointers.
- Sorting videos to facilitate optimal pairing.

Time Complexity: O(n log n) due to sorting, where n is the number of videos.
Space Complexity: O(1) excluding input storage.

Approach:
1. Sort video durations in ascending order.
2. Use two pointers (i starting from 0, j from end) to form pairs of videos where sum >= k.
3. Count such pairs, and if any videos remain unpaired but under k minutes, pair them greedily.
4. Output minimum ads required using mathematical logic involving pairing and leftover videos.

Note: The number of ads is equal to total videos minus the number of valid pairs (or groups), adjusted for minimum count constraint.

"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    d = sorted(list(map(int, input().split())))
    if d[0] >= k:
        print(n - 1)
        continue
    i = 0
    j = n - 1
    cnt = 0
    lft = n
    flag = False
    while i < j:
        while d[i] + d[j] >= k and i < j:  # Pair videos that together meet the k-minute threshold
            j -= 1
        if i >= j:
            break
        d[i] = -1  # Mark as paired
        d[j] = -1
        cnt += 1
        i += 1
        j -= 1
        lft -= 2
        if lft <= cnt:   # Early termination if remaining videos don't help more than current count
            break
    i = 0
    if lft > cnt:
        for i in range(n):  # Handle leftover videos under k-minute threshold
            if 0 < d[i] < k:
                cnt += 1
                lft -= 1
                if lft <= cnt:
                    break
    if lft < cnt:
        print(cnt - 1)   # Minimum ads is pairs minus one if overcounted
    else:
        print(lft - 1)


# https://github.com/VaHiX/codeForces/