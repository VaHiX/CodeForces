# Problem: CF 1846 G - Rudolf and CodeVid-23
# https://codeforces.com/contest/1846/problem/G

"""
Code Purpose:
This program finds the minimum number of days to eliminate all symptoms of the "CodeVid-23" virus by applying medicines optimally.
Each medicine has a duration, symptoms it removes, and side effects (symptoms it causes).
The problem is modeled as a shortest path in a graph where nodes represent symptom states (bitmask) and edges represent applying a medicine.
Dijkstra's algorithm is used to find the minimum number of days to reach the state with no symptoms.

Algorithms/Techniques:
- Bitmasking to represent symptom states
- Dijkstra's shortest path algorithm with a priority queue
- State transition using bitwise operations for applying medicines

Time Complexity: O(2^n * m * log(2^n)) where n is the number of symptoms and m is the number of medicines
Space Complexity: O(2^n) for the distance array and priority queue
"""

import sys

input = sys.stdin.readline
from heapq import heappop, heappush


def LII():
    return list(map(int, input().strip().split()))


inf = 10**7


def main():
    n, m = LII()
    # Convert initial symptoms from binary string to integer bitmask
    t = int(input(), 2)
    # Read medicines: [duration, removes_mask, side_effects_mask]
    A = [[int(input()), int(input(), 2), int(input(), 2)] for _ in range(m)]
    # Distance array to track minimum days to reach each symptom state
    d = [inf] * (1 << n)
    d[0] = 0  # No symptoms, 0 days needed
    pq = [(0, 0)]  # Priority queue: (days, symptom_mask)
    while pq:
        w, u = heappop(pq)
        # If all symptoms are gone, return the number of days
        if u & t == t:
            return w
        # Skip if we already found a better path to this state
        if w > d[u]:
            continue
        # Try each medicine
        for w2, a, b in A:
            # Compute new symptom state after applying medicine
            v = u | a  # Apply removals
            # Check if all side effects are present (can't apply if they are)
            if u & b == b and w + w2 < d[v]:
                d[v] = w + w2
                heappush(pq, (w + w2, v))
    return -1


for _ in range(int(input())):
    print(main())


# https://github.com/VaHiX/CodeForces/