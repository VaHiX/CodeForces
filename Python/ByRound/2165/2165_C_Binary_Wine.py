# Problem: CF 2165 C - Binary Wine
# https://codeforces.com/contest/2165/problem/C

import sys
from heapq import *

readint = lambda: int(sys.stdin.readline())
readints = lambda: map(int, sys.stdin.readline().split())
readar = lambda: list(map(int, sys.stdin.readline().split()))
flush = lambda: sys.stdout.flush()
readin = lambda: sys.stdin.readline()[:-1]
readins = lambda: map(str, sys.stdin.readline().split())

"""
Algorithm: Greedy with Min-Heap
Technique: For each query, we compute the minimum cost to make the XOR of selected elements equal to the target c.
We use a min-heap to efficiently manage the highest values in the array a, so that we can greedily reduce the cost of achieving the XOR.

Time Complexity: O(n log n + q * 35 * log 35)
Space Complexity: O(n + 35)

Sorting the array takes O(n log n), and for each query we perform at most 35 heap operations, each taking O(log 35).
"""

for _ in range(readint()):
    n, q = readints()
    ar = readar()
    ar.sort()
    ar.reverse()  # Sort in descending order to get highest values first
    for _ in range(q):

        highest = [0] * 35  # Array to store highest 35 values in heap (max 30 bits)
        for a in range(min(35, n)):  # Initialize heap with first 35 (or all) values
            highest[a] = -ar[a]  # Negative because Python has min-heap, but we want max-heap behavior
        heapify(highest)  # Convert list to heap

        x = readint()
        ex = 1
        br = list()
        # Convert target c to binary representation (list of powers of 2)
        while x != 0:
            if x % 2 == 1:
                br.append(ex)
            x //= 2
            ex *= 2
        br.reverse()  # Reverse to get LSB to MSB order

        ans = 0
        # For each bit in the binary representation of c
        for b in br:
            y = -heappop(highest)  # Get the maximum value available currently (negated)
            if y >= b:  # If this value is sufficient to cover the bit
                heappush(highest, -(y - b))  # Update heap after subtracting required bit
            else:  # If current value is too small
                ans += b - y  # We need to increment the array element to get this bit
                # We effectively increase one element to make it possible to represent 'b'

        print(ans)


# https://github.com/VaHiX/CodeForces/