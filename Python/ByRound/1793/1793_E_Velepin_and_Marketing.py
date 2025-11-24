# Problem: CF 1793 E - Velepin and Marketing
# https://codeforces.com/contest/1793/problem/E

"""
Algorithm: Greedy with preprocessing and binary search-like approach
Time Complexity: O(n log n) due to sorting and linear passes
Space Complexity: O(n) for storing arrays max_books and max_max_books

This solution uses a greedy approach to determine the maximum number of satisfied readers
for a given number of books k. It precomputes optimal results for all possible k values up to n,
then answers queries in O(1) time.

The key idea is to sort the array a first, then use dynamic programming to calculate
the maximum number of readers that can be satisfied for each possible number of books.
"""

import sys

input = sys.stdin.readline
n = int(input())
a = list(map(int, input().split(" ")))
a.sort()  # Sort the array to facilitate greedy selection
q = int(input())
ans = []
max_books = [-1 for _ in range(n + 1)]
max_books[0] = 0
max_max_books = [0 for _ in range(n + 1)]
for i in range(1, n + 1):
    mx = a[i - 1]
    if mx <= i:
        max_books[i] = max_max_books[i - mx] + 1
    max_max_books[i] = max(max_max_books[i - 1], max_books[i])

# Adjust max_books to represent actual number of people satisfied
for i in range(n + 1):
    if max_books[i] != -1:
        max_books[i] += n - i
    else:
        max_books[i] = n - a[i - 1] + 1

# Fill ans array with computed values
ans = [0 for _ in range(n + 1)]
mn = 0
for i in range(n, -1, -1):
    if max_books[i] >= mn:
        for j in range(mn, max_books[i] + 1):
            ans[j] = i
        mn = max_books[i] + 1

# Process queries
for _ in range(q):
    k = int(input())
    print(ans[k])


# https://github.com/VaHiX/CodeForces/