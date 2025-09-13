# Contest 76, Problem A: Gift
# URL: https://codeforces.com/contest/76/problem/A

import sys
import threading

import sys

data = sys.stdin
line = data.readline().split()

n, m = map(int, line)
g, s = map(int, data.readline().split())
edges = []  # (u, v, gold_req, silver_req, id)
for eid in range(m):
    parts = data.readline().split()

    u, v, gi, si = map(int, parts)
    # zero-index nodes for convenience
    edges.append((u - 1, v - 1, gi, si, eid))
# sort edges by gold requirement
edges.sort(key=lambda x: x[2])

# adjacency for current spanning forest: node -> list of (neighbor, silver_req, eid)
adj = [[] for _ in range(n)]
# maps of active tree edges
in_tree = set()
edge_uv = {}  # eid -> (u, v)
edge_si = {}  # eid -> si

best = float("inf")
# iterate over edges by increasing gold requirement
for u, v, gi, si_new, eid in edges:
    # check connectivity and optionally find cycle path
    # BFS from u to see if v reachable and track parent edges
    from collections import deque

    parent = [-1] * n
    parent_eid = [-1] * n
    dq = deque([u])
    parent[u] = u
    found = False
    while dq:
        x = dq.popleft()
        if x == v:
            found = True
            break
        for nei, si_old, oeid in adj[x]:
            if parent[nei] == -1:
                parent[nei] = x
                parent_eid[nei] = oeid
                dq.append(nei)
    if not found:
        # no cycle, just add edge
        adj[u].append((v, si_new, eid))
        adj[v].append((u, si_new, eid))
        in_tree.add(eid)
        edge_uv[eid] = (u, v)
        edge_si[eid] = si_new
    else:
        # cycle exists: retrieve path eids
        path_eids = []
        cur = v
        while cur != u:
            oeid = parent_eid[cur]
            path_eids.append(oeid)
            cur = parent[cur]
        # find edge with maximum silver on path
        max_si = -1
        eid_max = None
        for peid in path_eids:
            if edge_si[peid] > max_si:
                max_si = edge_si[peid]
                eid_max = peid
        # if the old edge is worse (larger si) than new, replace
        if max_si > si_new:
            # remove old edge
            ou, ov = edge_uv[eid_max]
            # remove from adjacency lists
            adj[ou] = [(nx, sreq, i_) for (nx, sreq, i_) in adj[ou] if i_ != eid_max]
            adj[ov] = [(nx, sreq, i_) for (nx, sreq, i_) in adj[ov] if i_ != eid_max]
            in_tree.remove(eid_max)
            del edge_uv[eid_max]
            del edge_si[eid_max]
            # add new edge
            adj[u].append((v, si_new, eid))
            adj[v].append((u, si_new, eid))
            in_tree.add(eid)
            edge_uv[eid] = (u, v)
            edge_si[eid] = si_new
    # if current forest is spanning tree
    if len(in_tree) == n - 1:
        # current maximum silver requirement among tree edges
        curr_max_s = max(edge_si[e] for e in in_tree)
        cost = gi * g + curr_max_s * s
        if cost < best:
            best = cost
# output result
if best == float("inf"):
    print(-1)
else:
    print(best)
