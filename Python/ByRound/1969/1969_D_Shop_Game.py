# Problem: CF 1969 D - Shop Game
# https://codeforces.com/contest/1969/problem/D

"""
Algorithm: Greedy with Priority Queue (Heap)
Approach:
1. Filter items where b_i > a_i (only consider items that give Alice profit).
2. Sort these items by b_i in descending order.
3. Use a greedy approach with a max heap to decide which items Alice should buy:
   - Initially, Alice buys the first k items from the sorted list.
   - For remaining items, she evaluates if swapping one of the previously bought items for the current item improves her profit.
   - A max heap is used to keep track of the highest cost items Alice has bought so far.

Time Complexity: O(n * log n) due to sorting and heap operations.
Space Complexity: O(n) for storing filtered items and heap usage.
"""

import sys

input = sys.stdin.readline
import heapq


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n, k = readInts()
    a, b = readList(), readList()
    # Filter items where Bob's price is greater than Alice's, sorted by Bob's price descending
    a = sorted([(a[i], b[i]) for i in range(n) if b[i] - a[i] > 0], key=lambda x: -x[1])
    n = len(a)
    if n <= k:
        return 0
    h, ans = [], 0
    # Calculate initial profit assuming Alice buys all items from k onwards
    v = sum([a[i][1] - a[i][0] for i in range(n) if i >= k])
    for i in range(n):
        if i < k:
            # Push Alice's cost into max heap (using negative values)
            heapq.heappush(h, -a[i][0])
            v -= a[i][0]
        else:
            # Update max profit seen so far
            ans = max(ans, v)
            # Subtract Bob's payment for this item
            v -= a[i][1]
            # Add current item's cost to heap
            heapq.heappush(h, -a[i][0])
            # Remove the most expensive item Alice bought so far
            v -= heapq.heappop(h)
    return max(ans, v)


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/