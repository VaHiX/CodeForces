# Contest 1575, Problem M: Managing Telephone Poles
# URL: https://codeforces.com/contest/1575/problem/M

import sys

input = sys.stdin.readline
INF = 10**18


def get_nearest_dist(initial_dist):
    n = len(initial_dist)

    convex_pos = [0] * n
    intersection_pos = [0.0] * (n + 1)

    num_src = 0
    convex_pos[0] = 0
    intersection_pos[0] = -float("inf")
    intersection_pos[1] = float("inf")

    def intersect(q1: int, q2: int) -> float:
        return ((initial_dist[q2] + q2 * q2) - (initial_dist[q1] + q1 * q1)) / (
            2 * (q2 - q1)
        )

    for idx in range(1, n):
        if initial_dist[idx] == INF:
            continue
        x = intersect(convex_pos[num_src], idx)
        while x <= intersection_pos[num_src]:
            num_src = num_src - 1
            x = intersect(convex_pos[num_src], idx)
        num_src += 1
        convex_pos[num_src] = idx
        intersection_pos[num_src] = x
        intersection_pos[num_src + 1] = float("inf")

    # print(convex_pos)
    # print(intersection_pos)

    dist = [0] * n
    idx = 0
    for i in range(n):
        while i > intersection_pos[idx + 1]:
            idx += 1
        q = convex_pos[idx]
        diff = i - q
        dist[i] = diff * diff + initial_dist[q]

    return dist


def main() -> None:
    n, m = map(int, input().split())
    rows, cols = n + 1, m + 1
    grid = [input().strip() for _ in range(rows)]

    col_dist = [[0] * cols for _ in range(rows)]
    for j in range(cols):
        base = [0 if grid[i][j] == "1" else INF for i in range(rows)]
        dist = get_nearest_dist(base)
        for i in range(rows):
            col_dist[i][j] = dist[i]

    total_dist = 0
    for i in range(rows):
        dist = get_nearest_dist(col_dist[i])
        total_dist += sum(dist)

    print(total_dist)


if __name__ == "__main__":
    main()
