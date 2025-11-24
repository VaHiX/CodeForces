# Problem: CF 1701 D - Permutation Restoration
# https://codeforces.com/contest/1701/problem/D

"""
Permutation Restoration Problem

Algorithm:
- The key insight is to use a greedy approach with a min-heap to assign values to positions.
- For each position i, we determine a valid range [a, b] where a and b are derived from the value b[i].
- These ranges are grouped by their starting point 'a' in a list of buckets.
- Then we process buckets in order from 1 to n, and for each bucket:
  - Add all intervals in that bucket to a min-heap.
  - Pop the minimum value from heap and assign it to the corresponding position in the permutation.
  
Time Complexity: O(n log n)
Space Complexity: O(n)

"""

import sys

input = sys.stdin.readline
import heapq

for _ in range(int(input())):
    n = int(input())
    w = list(map(int, input().split()))
    d = [[] for _ in range(n + 1)]
    for i in range(n):
        if w[i] == 0:
            a, b = i + 2, n   # If b[i] is 0, determine range from it
        else:
            a, b = (i + w[i] + 2) // (w[i] + 1), (i + 1) // w[i]  # Compute range based on b[i]
        d[a].append((b, i + 1))   # Store interval with its end point and original index
    e = []
    ans = [-1] * n
    for i in range(1, n + 1):
        for j in d[i]:
            heapq.heappush(e, j)   # Push intervals with same start point into heap
        ans[heapq.heappop(e)[1] - 1] = i   # Assign smallest endpoint to current position
    print(" ".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/