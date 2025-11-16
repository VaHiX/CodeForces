# Problem: CF 1790 G - Tokens on Graph
# https://codeforces.com/contest/1790/problem/G

""" G. Tokens on Graph
https://codeforces.com/contest/1790/problem/G

Algorithm:
- Build adjacency list representation of the graph
- Identify vertices that are bonuses
- Mark vertices that can bounce (both adjacent vertices are bonuses)
- Run BFS from vertex 1 to find minimum distance to reach bonus vertices
- For each token, calculate minimum steps to reach bonus and then finish
- Check if we can reach the finish with the given tokens and bonuses
- Special cases: 
  - If a token is already at vertex 1, return "YES"
  - If only one token, check if it can reach finish in at most 2 moves
  - Otherwise, count how many tokens can be used for bouncing

Time Complexity: O(N + M) where N is number of vertices and M is number of edges
Space Complexity: O(N + M) for adjacency list and auxiliary arrays
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


from collections import deque


def solve(N, M, C, B, chips, bonuses, edges):
    # Convert to 0-indexed
    chips = [u - 1 for u in chips]
    is_bonus = [0] * N
    for b in bonuses:
        is_bonus[b - 1] = 1

    adj = [[] for _ in range(N)]
    can_bounce = [0] * N
    for u, v in edges:
        u -= 1
        v -= 1
        adj[u].append(v)
        adj[v].append(u)
        if is_bonus[u] and is_bonus[v]:
            can_bounce[u] = can_bounce[v] = 1

    # BFS from finish vertex (0) to find minimum distance to reach bonus vertices
    dist = [INF] * N
    dist[0] = 0
    queue = deque([0])
    while queue:
        u = queue.popleft()
        for v in adj[u]:
            # Only consider bonus vertices that haven't been visited yet
            if not is_bonus[v] or dist[v] < INF:
                continue
            dist[v] = dist[u] + 1
            queue.append(v)

    best = None
    # For each token, find the minimum steps to reach bonus and then finish
    for u in chips:
        if not u:  # If token is already at finish vertex
            return "YES"
        d = INF
        for v in adj[u]:
            d = min(d, dist[v] + 1)
        if d < INF and (not best or best[0] > d):
            best = (d, u)
    if not best:
        return "NO"

    need, chosen = best
    # If only one token, check if it can reach finish in at most 2 moves
    if C == 1:
        return "YES" if need < 2 else "NO"

    have = 0
    for u in chips:
        if u == chosen:
            continue
        # Count tokens that can bounce (have bonus neighbors)
        if any(can_bounce[v] for v in adj[u]):
            have += INF
        elif any(is_bonus[v] for v in adj[u]):
            have += 1

    return "YES" if have >= need - 1 else "NO"


def main():
    T = int(input())
    for _ in range(T):
        N, M = list(map(int, input().split()))
        C, B = list(map(int, input().split()))
        chips = list(map(int, input().split()))
        bonuses = list(map(int, input().split()))
        edges = [list(map(int, input().split())) for _ in range(M)]
        _ = input()
        res = solve(N, M, C, B, chips, bonuses, edges)
        print(res)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/