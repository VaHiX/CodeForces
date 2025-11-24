# Problem: CF 2036 E - Reverse the Rivers
# https://codeforces.com/contest/2036/problem/E

"""
E. Reverse the Rivers

Purpose:
This code solves a problem where n countries each have k regions, and water flows through channels from one country to the next according to bitwise OR operations. For each query with several requirements about region values, it finds the smallest country index that satisfies all conditions.

Algorithms/Techniques:
- Preprocessing: Build prefix OR arrays for each region
- Binary Search: Use bisect_left and bisect_right to efficiently find valid ranges
- Query Processing: For each query, narrow down valid countries based on constraints

Time Complexity:
- Preprocessing: O(n * k)
- Per query: O(m * log(n)) where m is number of requirements
- Overall: O(n * k + sum(m))

Space Complexity:
- O(n * k) for storing prefix OR arrays and input data

Input/Output:
- Input contains n countries with k regions each, followed by q queries.
- Each query has m requirements (region, operator, value).
- Output is the smallest country number satisfying all requirements, or -1 if none.
"""

import sys
from bisect import bisect_left, bisect_right

input = sys.stdin.readline
n, k, q = map(int, input().split())
A = [list(map(int, input().split())) for _ in range(n)]
P = [[0] * (n + 1) for _ in range(k)]
for i in range(n):
    for j in range(k):
        P[j][i + 1] = P[j][i] | A[i][j]
res = []
for _ in range(q):
    m = int(input())
    L = 1
    R = n + 1
    for _ in range(m):
        r, o, c = input().split()
        r = int(r) - 1  # Convert to 0-based indexing
        c = int(c)
        if o == "<":
            j = bisect_left(P[r], c)  # Find leftmost index where P[r][j] >= c
            R = min(R, j)             # Narrow upper bound
        else:
            j = bisect_right(P[r], c) # Find rightmost index where P[r][j] <= c
            L = max(L, j)             # Narrow lower bound
    ans = L
    if L >= R:
        ans = -1
    res.append(ans)
print("\n".join(map(str, res)))


# https://github.com/VaHiX/codeForces/