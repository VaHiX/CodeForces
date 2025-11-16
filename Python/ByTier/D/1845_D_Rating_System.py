# Problem: CF 1845 D - Rating System
# https://codeforces.com/contest/1845/problem/D

"""
Algorithm: Rating System
Purpose: Determine the optimal value of k such that the final rating is maximized.
Techniques:
- Prefix sum calculation to track cumulative ratings
- Reverse iteration to find the minimum prefix sum and maximum difference
- Binary search or direct computation of optimal k based on prefix sums

Time Complexity: O(n) per test case, where n is the number of matches
Space Complexity: O(n) for storing prefix sums
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def evaluate(minimum, arr):
    # Simulates the rating change process with a fixed k (minimum)
    flag = False
    accu = 0
    for num in arr:
        if accu >= minimum:
            flag = True
        if flag:
            # If the current rating is at least k, and decreasing would go below k, set to k
            if accu + num < minimum:
                accu = minimum
            else:
                accu += num
        else:
            # Before reaching k, allow normal changes
            accu += num
    return accu


def main(t):
    n = int(input())
    arr = list(map(int, input().split()))

    # Precompute prefix sums: accu[i] = sum of elements from index 0 to i-1
    accu = [0] * (n + 1)
    for i in range(n):
        accu[i] = accu[i - 1] + arr[i]
    accu = [0] + accu  # Shift to make 0-indexed correctly

    ans = 0
    maxdiff = 0
    minimum = float("inf")
    
    # Traverse from right to left to find the minimum prefix sum (minimum rating reached)
    # and track maximum difference that could occur (to determine optimal k)
    for i in range(n, -1, -1):
        minimum = min(minimum, accu[i])
        if accu[i] - minimum > maxdiff:
            maxdiff = accu[i] - minimum
            ans = accu[i]

    print(ans)


T = int(input())
t = 1
while t <= T:
    main(t)
    t += 1


# https://github.com/VaHiX/CodeForces/