# Problem: CF 2140 D - A Cruel Segment's Thesis
# https://codeforces.com/contest/2140/problem/D

"""
D. A Cruel Segment's Thesis

Purpose:
This problem involves selecting pairs of segments to merge into a new segment such that the sum of all marked segment lengths is maximized.

Approach:
- Each operation merges two unmarked segments [li, ri] and [lj, rj] into a new segment [xk, yk] where li <= xk <= ri and lj <= yk <= rj.
- The optimal merging strategy uses greedy sorting: sort segments by sum (li + ri) in ascending order.
- For even n, the maximum score is calculated directly from the sum of all R values minus the sum of selected L values and their corresponding R values.
- For odd n, a more complex optimization is required using a loop over possible pivot points to compute maximum gain.

Algorithms/Techniques:
- Sorting
- Greedy approach
- Two-pointer or enumeration for optimal pivot

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing input and sorted indices
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    L, R = [], []
    cur = 0
    for i in range(n):
        l, r = map(int, input().split())
        L.append(l)
        R.append(r)
        cur += r  # Initially, we consider all segments as being marked (sum of right ends)
    
    # Sort indices by the sum of left and right endpoints
    slr = sorted(range(n), key=lambda i: L[i] + R[i])
    
    # Subtract the smallest (L[i] + R[i]) terms for the first half (n//2 elements)
    for i in slr[: n >> 1]:  # n >> 1 is equivalent to n // 2
        cur -= L[i] + R[i]
    
    if n % 2 == 0:
        # If even number of segments, we can pair all optimally
        print(cur + sum(R) - sum(L))
        continue
    
    ans = 0
    # For odd case: compute the maximum possible gain by choosing a pivot segment
    for i in slr[: n >> 1]:  # First half (as before)
        a = R[i] + L[slr[n >> 1]] + R[slr[n >> 1]]  # Cost of taking i and pivot
        b = L[i] + R[i]  # Value we lose by removing segment i
        ans = max(ans, cur - a + b)
    
    for i in slr[n >> 1 :]:  # Second half (including pivot)
        a = R[i]  # Cost of taking this segment (only right end contributes)
        ans = max(ans, cur - a)  # Maximize the result
    
    print(ans + sum(R) - sum(L))


# https://github.com/VaHiX/codeForces/