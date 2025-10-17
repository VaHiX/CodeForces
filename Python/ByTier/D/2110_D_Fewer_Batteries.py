# Problem: CF 2110 D - Fewer Batteries
# https://codeforces.com/contest/2110/problem/D

"""
D. Fewer Batteries

Problem Description:
In a robot competition, there are n checkpoints, each containing b[i] batteries. The robot starts at checkpoint 1 with no batteries and must reach checkpoint n. There are m one-way passages between checkpoints, each requiring a minimum number of batteries (w) to traverse. At each checkpoint, the robot can collect up to b[v] batteries. Batteries are cumulative and recharged at every checkpoint.

Approach:
This is a binary search on the answer combined with a BFS/DFS-style reachability check.
1. Binary search on the possible number of batteries at the end (from 0 to max weight).
2. For each candidate value, use a greedy-like algorithm to determine if it's feasible to reach checkpoint n:
   - Using a modified Bellman-Ford or similar logic, track maximum battery count that can be achieved at each checkpoint.
   - At each node, we can collect up to b[v] batteries and move to neighbors requiring w batteries.
3. If a path exists, try smaller values; otherwise, increase the value.

Time Complexity: O((n + m) * log(maxw)) where maxw is the maximum weight among all edges.
Space Complexity: O(n + m)

Algorithms/Techniques:
- Binary search on answer
- Greedy path checking via dynamic programming style update
- Graph traversal with battery accumulation

"""

import sys

input = sys.stdin.readline


def can_reach(n, adj, b, S):
    # H[u] stores the maximum batteries that can be accumulated at node u
    H = [-1] * (n + 1)
    H[1] = min(b[1], S)  # Start with available batteries at checkpoint 1 (but limited by S)
    for u in range(1, n + 1):
        if H[u] < 0:  # Can't reach this node
            continue
        hu = H[u]
        for v, w in adj[u]:  # For each neighbor and edge weight
            if hu >= w:  # If have enough batteries to traverse the edge
                # Update max battery count at v considering all possibilities:
                # current_hu + b[v] (after collecting) but capped by S
                H[v] = max(H[v], min(hu + b[v], S))
    return H[n] >= 0  # Can we reach node n with at least 0 batteries


t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    b = [0] + list(map(int, input().split()))  # 1-indexed
    adj = [[] for _ in range(n + 1)]
    maxw = 0
    for _ in range(m):
        s, t_, w = map(int, input().split())
        adj[s].append((t_, w))  # Build adjacency list with edge weights
        maxw = max(maxw, w)
    lo, hi, ans = 0, maxw, -1
    while lo <= hi:
        mid = (lo + hi) // 2
        if can_reach(n, adj, b, mid):  # Check feasibility with target battery limit
            ans = mid
            hi = mid - 1  # Try smaller battery requirement
        else:
            lo = mid + 1   # Need more batteries
    print(ans)


# https://github.com/VaHiX/codeForces/