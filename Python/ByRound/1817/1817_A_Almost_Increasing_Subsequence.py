# Problem: CF 1817 A - Almost Increasing Subsequence
# https://codeforces.com/contest/1817/problem/A

"""
Task: Find the length of the longest almost-increasing subsequence for each query range.

An almost-increasing sequence avoids three consecutive elements x, y, z such that x ≥ y ≥ z.
This problem uses preprocessing and prefix sums to efficiently answer multiple queries.

Approach:
- Preprocess the array to count how many "bad" triplets exist up to each index.
- A bad triplet is a sequence where three consecutive elements are in non-increasing order.
- For each query (l, r), compute the result using prefix sum differences:
  - Total length of subarray: (r - l + 1)
  - Number of bad triplets in subarray: (prefix[r-2] - prefix[l-2]) if l > 1, else prefix[r-2]
  - Answer = total_length - bad_triplets

Time Complexity: O(n + q) preprocessing + query time
Space Complexity: O(n) for prefix array

Algorithms/Techniques:
- Preprocessing with prefix sums
- Sliding window concept
- Range query optimization
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
n, q = input().split()
n = int(n)
q = int(q)
l = [int(num) for num in input().split()]
l0 = []
c = 0
# Preprocessing to count the number of "bad triplets" up to each index
for i in range(len(l) - 2):
    if l[i] >= l[i + 1] and l[i + 1] >= l[i + 2]:
        l[i] = 0
        c = c + 1
    l0.append(c)
# Process queries
for i in range(q):
    a, b = input().split()
    a = int(a)
    b = int(b)
    # Handle different cases based on query range
    if a > 1 and b - a > 1:
        print(b - a + 1 - l0[b - 3] + l0[a - 2])
    elif a > 1 and b - a == 1:
        print("2")
    elif a > 1 and a == b:
        print("1")
    elif a == 1 and b - a > 1:
        print(b - a + 1 - l0[b - 3])
    elif a == 1 and b - a == 1:
        print("2")
    elif a == 1 and a == b:
        print("1")


# https://github.com/VaHiX/codeForces/