# Problem: CF 1842 D - Tenzing and His Animal Friends 
# https://codeforces.com/contest/1842/problem/D

""" D. Tenzing and His Animal Friends
https://codeforces.com/contest/1842/problem/D

Algorithms: 
- This problem involves finding the maximum total time Tenzing can play with his animal friends given certain constraints.
- The solution uses a variant of Dijkstra's algorithm to compute the shortest path from friend 1 (source) to friend n (sink).
- Each edge in the graph represents a constraint, where u and v are friends and w is the upper bound on the time that exactly one of them is playing with Tenzing.

Time Complexity: O((V + E) log V) where V = n (number of friends) and E = m (number of constraints)
Space Complexity: O(V + E) for the adjacency list representation and auxiliary arrays
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
output = sys.stdout.write


def debug(*args):
    if os.environ.get("debug") in [None, "0"]:
        return
    from inspect import currentframe, getframeinfo
    from re import search

    frame = currentframe().f_back
    s = getframeinfo(frame).code_context[0]
    r = search(r"\((.*)\)", s).group(1)
    vnames = r.split(", ")
    var_and_vals = [f"{var }={val }" for var, val in zip(vnames, args)]
    prefix = f"{currentframe ().f_back .f_lineno :02d}: "
    print(f'{prefix }{", ".join (var_and_vals )}')


INF = float("inf")


from heapq import heappop, heappush


def solve_1(N, M, edges):
    # Build adjacency list for the graph
    adj = [[] for _ in range(N)]
    for u, v, w in edges:
        u -= 1
        v -= 1
        adj[u].append([v, w])
        adj[v].append([u, w])

    # Track which friends are still alive (playing) and when they became dead
    alive = [1] * N
    dead_since = [-1] * N
    time = 0
    ops = []

    # Initialize the first removal operation
    rm = (0, 1 - N)
    while len(ops) < N * N:
        rmt, rmu = rm
        rmu = -rmu

        time += rmt
        dead_since[rmu] = time
        if rmt:
            ops.append(["".join(map(str, alive)), rmt])
        alive[rmu] = 0

        if not rmu:
            return time, ops

        # Find next friend to remove based on minimum time
        rm = (INF, INF)
        for u in range(N):
            if not alive[u]:
                continue
            for v, t in adj[u]:
                if not alive[v]:
                    rm = min(rm, (t - time + dead_since[v], -u))
        if rm == (INF, INF):
            break

    return INF, []


def solve_2(N, M, edges):
    # Build adjacency list for the graph
    adj = [[] for _ in range(N)]
    for u, v, w in edges:
        u -= 1
        v -= 1
        adj[u].append([v, w])
        adj[v].append([u, w])

    # Compute shortest distances from friend n to all other friends
    dist = [INF] * N
    dist[N - 1] = 0
    h = [(0, N - 1)]
    ops = []
    
    # Process nodes in order of increasing distance
    while h:
        d, u = heappop(h)
        if dist[u] < d:
            continue
        ops.append(u)
        if u == 0:
            break
        for v, w in adj[u]:
            if dist[v] <= d + w:
                continue
            dist[v] = d + w
            heappush(h, (d + w, v))

    # If friend 1 is unreachable from friend n, the problem has no solution
    if dist[0] is INF:
        return INF, []

    # Reconstruct solution by building time segments
    res = []
    mask = [1] * N
    mask[N - 1] = 0  # Mark friend n as not playing
    for i in range(1, len(ops)):
        t = dist[ops[i]] - dist[ops[i - 1]]
        if t:
            res.append(["".join(map(str, mask)), t])
        mask[ops[i]] = 0  # Mark current friend as not playing

    return dist[0], res


solve = solve_2


def main():
    N, M = list(map(int, input().split()))
    edges = [list(map(int, input().split())) for _ in range(M)]
    tot, ops = solve(N, M, edges)
    if tot is INF:
        print("inf")  # Output "inf" if infinite time is possible
    else:
        print(tot, len(ops))
        for o in ops:
            print(*o)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/