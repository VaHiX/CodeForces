# Problem: CF 1948 E - Clique Partition
# https://codeforces.com/contest/1948/problem/E

"""
Algorithm: Clique Partition for Vertex Assignment
Time Complexity: O(n)
Space Complexity: O(n)

This solution assigns integers to vertices in a way that minimizes the number of cliques needed to partition the graph.
The key idea is to group vertices into segments where each segment forms a clique based on the constraint |i-j| + |a_i - a_j| <= k.
For each segment, we assign values in a way that maximizes the overlap between vertices in the same clique.
The assignment strategy ensures that the number of cliques needed is minimized by overlapping the value ranges optimally.

The algorithm uses a greedy approach to build segments of size at most k, and assigns values in a way to ensure the constraint is satisfied
within each segment while minimizing inter-segment edges.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def solve() -> None:
    n, k = mint()
    a = [0] * n  # Array to store assigned values to vertices
    c = [0] * n  # Array to store clique assignments for vertices
    i = q = 0    # i: current vertex index, q: number of cliques used
    
    # Process each segment of vertices
    while i < n:
        # Determine the end of the current segment (at most k vertices)
        r = min(n - 1, i + k - 1)
        q += 1  # Increment clique count
        
        # Calculate the middle of the segment to assign values
        d = (i + 1 + r + 1) // 2
        
        # Assign values to vertices in the current segment
        for j in range(i, r + 1):
            a[j], c[j] = d, q  # Assign value d and clique q to vertex j
            d += 1  # Increment value for next vertex
            if d > r + 1:  # Wrap around if needed
                d = i + 1
        i = r + 1  # Move to next segment

    print(*a)
    print(q)
    print(*c)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/