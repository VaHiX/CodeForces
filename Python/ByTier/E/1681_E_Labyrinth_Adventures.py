# Problem: CF 1681 E - Labyrinth Adventures
# https://codeforces.com/contest/1681/problem/E

"""
Algorithm: 2D Point-to-Point Shortest Path in Layered Grid with Doors
Time Complexity: O(M * log^2(N)) where M is number of queries and N is grid size
Space Complexity: O(N + M) for storing doors and queries

This solution uses a divide-and-conquer approach with dynamic programming to efficiently
compute shortest paths in a layered labyrinth. Each layer is a square grid, and doors
connect adjacent layers. The solution precomputes distances between layers using DP,
then answers queries using a recursive divide-and-conquer strategy based on layer depth.

Key Techniques:
1. Divide and Conquer: Recursively split the problem by layer depth
2. Dynamic Programming: Precompute layer-to-layer distances
3. Coordinate Transformation: Convert 1-based to 0-based indexing
4. Layer-based Distance Calculation: Efficiently compute distances across layers
"""

import sys

input = sys.stdin.readline

from typing import List, Tuple

INF = 10**18
N = int(input())

# Store door positions for each layer (0-indexed internally)
# inpos[i] contains doors from layer i to layer i+1
# outpos[i] contains doors from layer i+1 to layer i
inpos: List[Tuple[Tuple[int, int], Tuple[int, int]]] = [((0, 0), (0, 0))] * N
outpos = list(inpos)

# Read door positions for each layer
for i in range(1, N):
    yt, xt, yr, xr = map(int, input().split())
    assert yt == xr == i, i
    # Convert to 0-based indexing
    outpos[i - 1] = ((xt - 1, yt - 1), (xr - 1, yr - 1))
    inpos[i] = ((xt - 1, yt), (xr, yr - 1))


def dist(x1, y1, x2, y2) -> int:
    """Calculate Manhattan distance between two points"""
    return abs(x1 - x2) + abs(y1 - y2)


M = int(input())
O = [INF] * M  # Result array
qs = []  # List to hold queries (x1, y1, x2, y2, query_index)

# Read and convert queries to 0-based coordinates
for i in range(M):
    y1, x1, y2, x2 = map(lambda s: int(s) - 1, input().split())
    # Ensure that the first point is in a layer with smaller or equal depth
    if max(x1, y1) > max(x2, y2):
        x1, y1, x2, y2 = x2, y2, x1, y1

    # If both points are in the same layer, directly compute distance
    if max(x1, y1) == max(x2, y2):
        O[i] = dist(x1, y1, x2, y2)
    else:
        qs.append((x1, y1, x2, y2, i))


# D[i][0] and D[i][1] store minimum distances to reach layer i via top door or right door respectively
D = [[0, 0] for _ in range(N)]


def solve(lo: int, hi: int, qs: List[Tuple]):
    """Recursive function to solve queries using divide and conquer"""
    m = (lo + hi) // 2  # Midpoint layer

    left, here, right = [], [], []
    # Partition queries based on whether they cross the midpoint layer
    for t in qs:
        x1, y1, x2, y2, qi = t
        # If both points are in layers < m, go left
        if max(x2, y2) < m:
            left.append(t)
        # If both points are in layers >= m, go right
        elif max(x1, y1) >= m:
            right.append(t)
        # If points cross layer m, process here
        else:
            here.append(t)

    if here:
        assert m > 0  # Ensure we have at least one layer to process
        # Process each door orientation (0 = top door, 1 = right door)
        for mdoor in range(2):
            # Get doors for current layer m
            tdoor, rdoor = inpos[m]
            # Distance to reach layer m via tdoor or rdoor
            D[m] = [0, dist(*tdoor, *rdoor)]
            if mdoor:  # If taking right door first, swap
                D[m].reverse()

            # Forward pass: compute distances from layer m to higher layers
            for i in range(m, hi - 1):
                in_tdoor, in_rdoor = inpos[i]
                out_tdoor, out_rdoor = outpos[i]
                # Compute minimum distances to next layer
                D[i + 1][0] = min(
                    D[i][0] + dist(*in_tdoor, *out_tdoor) + 1,
                    D[i][1] + dist(*in_rdoor, *out_tdoor) + 1,
                )
                D[i + 1][1] = min(
                    D[i][0] + dist(*in_tdoor, *out_rdoor) + 1,
                    D[i][1] + dist(*in_rdoor, *out_rdoor) + 1,
                )

            # Backward pass: compute distances from layer m to lower layers
            for i in range(m - 1, lo - 1, -1):
                in_tdoor, in_rdoor = outpos[i]
                out_tdoor, out_rdoor = inpos[i]
                D[i][0] = min(
                    D[i + 1][0] + dist(*in_tdoor, *out_tdoor) + 1,
                    D[i + 1][1] + dist(*in_rdoor, *out_tdoor) + 1,
                )
                D[i][1] = min(
                    D[i + 1][0] + dist(*in_tdoor, *out_rdoor) + 1,
                    D[i + 1][1] + dist(*in_rdoor, *out_rdoor) + 1,
                )

            # Process queries that cross the current midpoint layer
            for x1, y1, x2, y2, qi in here:
                l1, l2 = max(x1, y1), max(x2, y2)  # Layer depths of start and end points
                assert l1 < m and l2 >= m  # Ensure query crosses layer m

                # Get door positions for current layers
                in_tdoor, in_rdoor = inpos[l2]
                d_in_tdoor, d_in_rdoor = D[l2]  # Distance to reach layer l2

                out_tdoor, out_rdoor = outpos[l1]
                d_out_tdoor, d_out_rdoor = D[l1 + 1]  # Distance from layer l1+1
                # Add cost for passing through layer boundaries
                d_out_tdoor += 1
                d_out_rdoor += 1

                # Distance from end point to closest door in layer l2 (to reach layer m)
                dr = min(
                    dist(x2, y2, *in_tdoor) + d_in_tdoor,
                    dist(x2, y2, *in_rdoor) + d_in_rdoor,
                )

                # Distance from start point to closest door in layer l1+1
                dl = min(
                    dist(x1, y1, *out_tdoor) + d_out_tdoor,
                    dist(x1, y1, *out_rdoor) + d_out_rdoor,
                )

                O[qi] = min(O[qi], dl + dr)  # Update minimum path distance

    # Recursively solve queries in left and right subproblems
    if left:
        solve(lo, m, left)
    if right:
        solve(m, hi, right)


solve(0, N, qs)

print("\n".join(map(str, O)))


# https://github.com/VaHiX/CodeForces/