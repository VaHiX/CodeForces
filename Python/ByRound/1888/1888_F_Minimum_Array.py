# Problem: CF 1888 F - Minimum Array
# https://codeforces.com/contest/1888/problem/F

"""
Algorithm: Difference Array + Prefix Sum
Approach:
1. Use a difference array technique to efficiently apply range updates.
2. For each operation, we update the difference array to reflect the changes.
3. Identify the earliest point where a negative value occurs in the prefix sum of the difference array, which indicates the earliest opportunity to make a lexicographically smaller array.
4. Compute the final array by applying prefix sum on the difference array and adding original array elements.

Time Complexity: O(q * log q + n)
Space Complexity: O(n + q)

The key idea is to use a difference array to represent range updates, and use a min-heap to track the indices that have active changes. When we detect a negative prefix sum, it means the lexicographically smallest element occurs at that point.
"""

import heapq
import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def main(t):
    n = int(input())
    arr = list(map(int, input().split()))
    q = int(input())
    change = []
    dic = {}
    heap = []
    minindex = -1
    for i in range(q):
        l, r, diff = map(int, input().split())
        l -= 1  # Convert to 0-based indexing
        change.append((l, r, diff))
        if l not in dic:
            dic[l] = 0
        dic[l] += diff
        if r not in dic:
            dic[r] = 0
        dic[r] -= diff
        if dic[l] == 0:
            del dic[l]
        if dic[r] == 0:
            del dic[r]
        heapq.heappush(heap, l)
        heapq.heappush(heap, r)
        if diff < 0:
            # Check if there's a negative value in the prefix sum after applying this operation
            while heap and heap[0] not in dic:
                heapq.heappop(heap)
            if len(heap) > 0 and dic[heap[0]] < 0:
                # Update the index of when the first negative prefix sum appears
                minindex = i
                # Clear data structures to avoid processing future operations
                dic.clear()
                heap = []
    # Reconstruct the difference array up to the last best point
    ans = [0] * (n + 1)
    for i in range(minindex + 1):
        l, r, diff = change[i][0], change[i][1], change[i][2]
        ans[l] += diff
        ans[r] -= diff
    # Compute prefix sum to get the actual change array
    for j in range(1, n):
        ans[j] += ans[j - 1]
    # Add original array values to get the final result
    for j in range(n):
        ans[j] += arr[j]
    # Remove the extra element added at the end
    ans.pop()
    print(*ans)


T = int(input())
t = 1
while t <= T:
    main(t)
    t += 1


# https://github.com/VaHiX/CodeForces/