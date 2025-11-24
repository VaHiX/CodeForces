# Problem: CF 1615 D - X(or)-mas Tree
# https://codeforces.com/contest/1615/problem/D

""" D. X(or)-mas Tree
https://codeforces.com/contest/1615/problem/D

Algorithm: 
- Build a graph where each edge is represented with its parity (0 or 1) based on the given values
- For edges with unknown values (-1), we treat them as variables to be determined
- Use a graph coloring technique to assign parities to edges (0 or 1) such that the XOR of values along any path matches the given parity constraints
- For each edge with unknown value, assign it based on the two end nodes' colors
- Time Complexity: O(N + M) for each test case, where N is number of nodes and M is number of edges
- Space Complexity: O(N + M) to store the graph and processing information
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
output = sys.stdout.write

DEBUG = os.environ.get("debug") is not None

if DEBUG:
    from inspect import currentframe, getframeinfo
    from re import search


def debug(*args):
    if not DEBUG:
        return
    frame = currentframe().f_back
    s = getframeinfo(frame).code_context[0]
    r = search(r"\((.*)\)", s).group(1)
    vnames = r.split(", ")
    var_and_vals = [f"{var }={val }" for var, val in zip(vnames, args)]
    prefix = f"{currentframe ().f_back .f_lineno :02d}: "
    print(f'{prefix }{", ".join (var_andVals )}')


INF = float("inf")


def solve():
    N, M = list(map(int, input().split()))

    edges = []
    obs = [[] for _ in range(N + 1)]

    for _ in range(N - 1):
        u, v, w = list(map(int, input().split()))
        edges.append((u, v, w))
        if w != -1:
            w = bin(w).count("1") % 2  # Convert value to parity (0 or 1)
            obs[u].append((v, w))
            obs[v].append((u, w))

    for _ in range(M):
        u, v, w = list(map(int, input().split()))
        obs[u].append((v, w))
        obs[v].append((u, w))

    color = [-1] * (N + 1)
    for u in range(1, N + 1):
        if color[u] != -1:
            continue
        color[u] = 0
        stack = [u]
        while stack:
            u = stack.pop()
            for v, w in obs[u]:
                if color[v] == -1:
                    color[v] = color[u] ^ w  # XOR to find color of neighbor node
                    stack.append(v)
                elif color[v] != color[u] ^ w:
                    print("NO")
                    return

    print("YES")

    for u, v, w in edges:
        if w != -1:
            print(u, v, w)
        else:
            print(u, v, color[u] ^ color[v])  # Assign value based on node colors


def main():
    T = int(input())
    for _ in range(T):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/