# Problem: CF 1575 M - Managing Telephone Poles
# https://codeforces.com/contest/1575/problem/M

"""
Algorithm: Minima of Convex Functions using Convex Hull Trick
Purpose: Efficiently compute the sum of squared Euclidean distances from each point to the nearest telephone pole in a grid.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

This solution uses the Convex Hull Trick (CHT) to optimize the calculation of minimum distances.
For each column, it calculates the minimum squared distance to any pole in that column.
Then, for each row, it calculates the minimum squared distance to any pole in that row,
combining the previous column distances with the row distances.

The key technique is to use the convex hull trick for finding the minimum value of a set of quadratic functions.
"""

import sys

input = sys.stdin.readline
INF = 10**18


def get_nearest_dist(initial_dist):
    """
    Use Convex Hull Trick to compute the minimum distance for each position.
    This function processes a 1D array of distances and returns the minimum distance
    to any pole from each position, where pole positions are marked with 0,
    and non-pole positions (with infinite distance) are marked with INF.
    """
    n = len(initial_dist)
    convex_pos = [0] * n
    intersection_pos = [0.0] * (n + 1)
    num_src = 0
    convex_pos[0] = 0
    intersection_pos[0] = -float("inf")
    intersection_pos[1] = float("inf")

    def intersect(q1: int, q2: int) -> float:
        # Compute intersection point of two parabolas representing the cost function
        return ((initial_dist[q2] + q2 * q2) - (initial_dist[q1] + q1 * q1)) / (
            2 * (q2 - q1)
        )

    for idx in range(1, n):
        if initial_dist[idx] == INF:
            continue
        x = intersect(convex_pos[num_src], idx)
        # Remove outdated entries from convex hull
        while x <= intersection_pos[num_src]:
            num_src = num_src - 1
            x = intersect(convex_pos[num_src], idx)
        num_src += 1
        convex_pos[num_src] = idx
        intersection_pos[num_src] = x
        intersection_pos[num_src + 1] = float("inf")
    dist = [0] * n
    idx = 0
    for i in range(n):
        # Find correct parabola in convex hull
        while i > intersection_pos[idx + 1]:
            idx += 1
        q = convex_pos[idx]
        diff = i - q
        dist[i] = diff * diff + initial_dist[q]
    return dist


def main() -> None:
    # Read grid dimensions
    n, m = map(int, input().split())
    rows, cols = n + 1, m + 1
    # Read grid
    grid = [input().strip() for _ in range(rows)]
    col_dist = [[0] * cols for _ in range(rows)]
    
    # For each column, calculate minimum distance to pole in that column
    for j in range(cols):
        base = [0 if grid[i][j] == "1" else INF for i in range(rows)]
        dist = get_nearest_dist(base)
        for i in range(rows):
            col_dist[i][j] = dist[i]
    
    total_dist = 0
    # For each row, calculate combined minimum distance to nearest pole
    for i in range(rows):
        dist = get_nearest_dist(col_dist[i])
        total_dist += sum(dist)
    print(total_dist)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/