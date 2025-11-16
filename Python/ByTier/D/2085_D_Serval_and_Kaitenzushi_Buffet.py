# Problem: CF 2085 D - Serval and Kaitenzushi Buffet
# https://codeforces.com/contest/2085/problem/D

"""
D. Serval and Kaitenzushi Buffet

Algorithm: Sliding window with a min-heap to maintain the k largest elements.
Approach:
    - Process plates from right to left (backwards).
    - Use a min-heap to keep track of the k largest deliciousness values seen so far in a window of size k.
    - When we hit a new group of k plates, we add the smallest element of that group to the heap and remove the smallest if needed.
    - Keep track of how many elements have been added to maintain group size.
    
Time Complexity: O(n * log k) per test case due to heap operations
Space Complexity: O(k) for maintaining the heap

This solution efficiently finds the optimal set of plates Serval can take by ensuring 
in each batch of k+1 plates, he takes the one with maximum deliciousness and discards 
the rest in a way that maximizes total gain.
"""

import sys

input = sys.stdin.readline
import heapq as hq

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    dcs = [*map(int, input().split())]
    heap = []
    cnt = 0
    for i in range(n - 1, -1, -1):  # Iterate from right to left
        cnt += 1
        if cnt == k + 1:  # When we have processed k+1 plates, process them as a group
            cnt = 0  # Reset counter
            hq.heappush(heap, dcs[i])  # Push the current plate's deliciousness into heap
        elif heap and heap[0] < dcs[i]:  # If there's an element smaller than the current one
            hq.heappop(heap)  # Remove the smallest
            hq.heappush(heap, dcs[i])  # Add the current one
    print(sum(heap))  # Sum of the k largest elements in each group of size k+1


# https://github.com/VaHiX/codeForces/