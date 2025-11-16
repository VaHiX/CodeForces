# Problem: CF 2021 C2 - Adjust The Presentation (Hard Version)
# https://codeforces.com/contest/2021/problem/C2

"""
C2. Adjust The Presentation (Hard Version)
Algorithms/Techniques: Segment tree with lazy propagation, heap-based approach for tracking earliest positions

Time Complexity: O((n + m + q) * log(n))
Space Complexity: O(n + m + q)

The problem involves maintaining a dynamic lineup of members where each slide must be presented by a specific member.
We use a heap to store the earliest occurrences of each member in the lineup and track violations (when earlier
members appear after later ones) to determine if a slideshow is "good".
"""

import sys

input = sys.stdin.readline
import heapq


def check(i):
    # If index out of bounds, return 0
    if i < 0 or i >= n - 1:
        return 0
    sc = 0
    # Pop invalid entries from heap for position i
    while B[erarliest[i][0]] != i:
        heapq.heappop(erarliest[i])
    # Pop invalid entries from heap for position i+1
    while B[erarliest[i + 1][0]] != i + 1:
        heapq.heappop(erarliest[i + 1])
    # If earliest occurrence of member at i is after member at i+1, there's a violation
    if erarliest[i][0] > erarliest[i + 1][0]:
        sc += 1
    return sc


for _ in range(int(input())):
    n, m, q = map(int, input().split())
    T = [0] * n  # Reindexing array
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))
    # Reindex based on initial order A
    for i in range(n):
        T[A[i] - 1] = i
    # Transform B to be indexed relative to new order
    B = [T[i - 1] for i in B] + list(range(n))
    erarliest = [[] for _ in range(n)]  # Min-heap to store indices of each member's earliest appearance
    # Initialize the heap with indices of members in their current positions
    for i, j in enumerate(B):
        heapq.heappush(erarliest[j], i)
    ok = 0  # Count of violations (earlier member after later member)
    # Check initial state for violations
    for i in range(n - 1):
        if erarliest[i][0] > erarliest[i + 1][0]:
            ok += 1
    # Process all queries including the initial state
    for x in range(q + 1):
        # Print result: "YA" if no violations (good), otherwise "TIDAK"
        if ok == 0:
            print("YA")
        else:
            print("TIDAK")
        if x == q:
            break
        # Read update query
        a, b = map(int, input().split())
        b -= 1
        b = T[b]  # Convert to new indexing scheme
        a -= 1
        old = B[a]  # Old position of member at index a
        z = {old, old - 1, b, b - 1}  # All affected indices
        # Update violations by removing outdated ones
        for i in z:
            ok -= check(i)
        B[a] = b  # Update the person at position a
        heapq.heappush(erarliest[b], a)  # Add new occurrence of member to heap
        # Update violations by adding new possible ones
        for i in z:
            ok += check(i)


# https://github.com/VaHiX/codeForces/