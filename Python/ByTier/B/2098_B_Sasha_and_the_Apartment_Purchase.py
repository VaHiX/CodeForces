# Problem: CF 2098 B - Sasha and the Apartment Purchase
# https://codeforces.com/contest/2098/problem/B

"""
B. Sasha and the Apartment Purchase

Purpose:
This code determines the number of houses where Sasha can potentially buy an apartment based on minimizing the sum of distances to open bars after closing at most k bars.

Algorithm:
1. Sort the positions of bars.
2. For each possible house number, compute the minimum possible sum of distances (f(x)) by considering optimal selection of bars to keep open.
3. The key insight is that for a fixed set of bars, f(x) is minimized when x is the median of those bars.
4. We use sliding window technique with sorted bar positions to efficiently calculate minimal f(x) values.

Key Idea:
- If we sort bars by position, we can find optimal houses using a sliding window approach over the sorted array.
- For every valid subset of bars (allowing up to k to be closed), compute the minimum possible f(x) for that subset.
- This is done efficiently by considering all windows of size (n - k) in the sorted bar list.

Time Complexity:
O(n log n + n * k) where:
- Sorting takes O(n log n)
- Each window selection and median calculation is O(1) after sorting

Space Complexity:
O(n) for storing the array of bar positions
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    a = sorted(list(map(int, input().split())))
    med = (n - k - 1) // 2  # Compute index of median in current window
    print(a[n - med - 1] - a[med] + 1)  # This calculates the count of valid houses


# https://github.com/VaHiX/codeForces/