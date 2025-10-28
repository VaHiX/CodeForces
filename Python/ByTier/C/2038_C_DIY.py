# Problem: CF 2038 C - DIY
# https://codeforces.com/contest/2038/problem/C

"""
C. DIY

Purpose:
This code solves a problem where we are given a list of integers and need to find 8 elements that form the corners of a rectangle with sides parallel to coordinate axes, maximizing the area. 
The approach is to:
1. Count frequency of each number.
2. For numbers appearing at least twice, consider them as potential x or y coordinates for rectangle sides.
3. Try to form a rectangle using two distinct x-coordinates (each appearing at least twice) and two distinct y-coordinates (each appearing at least twice).
4. Output the result if a valid rectangle exists.

Algorithms/Techniques:
- Frequency counting
- Sorting for grouped elements
- Greedy selection of coordinates

Time Complexity:
O(n log n) per test case due to sorting; overall complexity is O(sum_n * log(sum_n)) over all test cases.

Space Complexity:
O(n) for storing input and temporary arrays.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    w = sorted(map(int, input().split())) + [10**10]  # Add sentinel to simplify loop logic
    c = 0
    d = []
    for i in range(n):
        c += 1
        if w[i] != w[i + 1]:  # When sequence changes, process the current element
            for a in range(c // 2):  # Take half (rounded down) of occurrences as valid points
                d.append(w[i])
            c = 0
    if len(d) > 3:  # Need at least 4 unique elements to make a rectangle (2 x-coords and 2 y-coords)
        print("YES")
        print(d[0], d[1], d[0], d[-1], d[-2], d[1], d[-2], d[-1])  # Output four corners
    else:
        print("NO")


# https://github.com/VaHiX/codeForces/