# Problem: CF 2104 E - Unpleasant Strings
# https://codeforces.com/contest/2104/problem/E

"""
E. Unpleasant Strings

Purpose:
This code solves the problem of determining the minimum number of allowed letters to append to a query string so that it stops being a subsequence of the given input string s.

Algorithms/Techniques:
- Dynamic Programming with backward traversal
- Preprocessing character positions for efficient lookup
- Binary search via bisect_right for fast querying

Time Complexity: O(n + k*(n + q*m*log(m))) where n = length of s, q = number of queries, m = average query length.
Space Complexity: O(n + k*n) for storing positions and DP array.

"""
from sys import stdin

input = lambda: stdin.readline().rstrip("\r\n")
from bisect import bisect_right

n, k = map(int, input().split())
s = input()
pos = [[] for _ in range(k)]  # Preprocess positions of each character
for i, x in enumerate(s, start=1):
    pos[ord(x) - ord("a")] += (i,)  # Store indices where each letter appears

last = [n + 1] * k  # Track the last occurrence index of each character
f = [0] * (n + 1)   # DP array storing min suffix length to make string unpleasant

# Backward DP computation
for i in range(n, -1, -1):
    best = n + 1
    ind = 0
    for j in last:
        if j > n:
            ind = 1
            break
        if f[j] < best:
            best = f[j]
    else:
        ind = best + 1
    f[i] = ind
    if i > 0:
        last[ord(s[i - 1]) - ord("a")] = i  # Update last seen index of current char

# Process queries
for _ in range(int(input())):
    p = 0  # Current position in original string
    for x in input():
        a = pos[ord(x) - ord("a")]  # Get all positions where character x appears
        j = bisect_right(a, p)      # Find first position > p
        if j == len(a):             # If no such position exists, we're done
            p = n + 1
            break
        p = a[j]                    # Move to that position
    print(0 if p > n else f[p])     # Output the minimum number of letters needed


# https://github.com/VaHiX/codeForces/