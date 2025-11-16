# Problem: CF 1854 A2 - Dual (Hard Version)
# https://codeforces.com/contest/1854/problem/A2

"""
Algorithm/Techniques: Greedy approach with careful handling of positive and negative numbers.
Time Complexity: O(n log n) due to sorting operations.
Space Complexity: O(n) for storing positive and negative elements.

This code attempts to make an array non-decreasing in at most 31 operations by:
1. Separating positive and negative numbers into lists.
2. Using special cases based on the distribution of positive and negative values.
3. Applying operations like adding elements to each other in a specific order to make the array sorted.
"""

import sys

input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))

    neg = []
    pos = []
    for i in range(1, n + 1):
        if a[i - 1] > 0:
            pos.append((a[i - 1], i))
        elif a[i - 1] < 0:
            neg.append((a[i - 1], i))
    neg.sort()
    pos.sort()

    ans = []

    if not neg and not pos:
        pass
    elif not pos or (neg and -neg[0][0] >= pos[-1][0]):
        # Case where the largest positive is not too small compared to the smallest negative
        # Add all positive values to the smallest negative value (which is the most negative)
        if len(pos) <= 12:
            for _, i in pos:
                ans.append((i, neg[0][1]))

            for i in range(n, 1, -1):
                ans.append((i - 1, i))
        else:
            # If there are many positive numbers, add some to self then use the strategy
            ans.extend([(pos[0][1], pos[0][1])] * 5)
            for _, i in neg:
                ans.append((i, pos[0][1]))

            for i in range(1, n):
                ans.append((i + 1, i))
    else:
        # Case where negative values dominate
        if len(neg) <= 12:
            # Add all negative values to the largest positive value
            for _, i in neg:
                ans.append((i, pos[-1][1]))

            for i in range(1, n):
                ans.append((i + 1, i))
        else:
            # If there are many negative values, add some to self then use the strategy
            ans.extend([(neg[0][1], neg[0][1])] * 5)
            for _, i in pos:
                ans.append((i, neg[0][1]))

            for i in range(n, 1, -1):
                ans.append((i - 1, i))

    print(len(ans))
    for op in ans:
        print(*op)


# https://github.com/VaHiX/CodeForces/