# Problem: CF 2137 G - Cry Me a River
# https://codeforces.com/contest/2137/problem/G

"""
G. Cry Me a River

Purpose:
This code solves a game theory problem on a directed acyclic graph (DAG). The game involves two players, Cry and River, who take turns moving a token along directed edges in the DAG. The goal is to determine if Cry wins when starting from a given node, assuming both players play optimally.

Players:
- Cry goes first.
- Cry wins if the token reaches a node with no outgoing edges.
- River wins if the token reaches a red node.
- If a node is both red and has no outgoing edges, River wins.
- Nodes are initially blue; queries can color nodes red.

Algorithms/Techniques:
- Game theory on DAGs using reverse propagation of winning states.
- Maintains counts of in-degrees for cry_wins and river_wins.
- BFS-like updates propagate through the graph when node colors change.

Time Complexity: O(n + m + q)
Space Complexity: O(n + m)

"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    n, m, q = map(int, input().split())
    out_degree = [0] * n
    in_edges = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(lambda x: int(x) - 1, input().split())
        out_degree[u] += 1
        in_edges[v].append(u)
    red = [False] * n
    cry_wins = [True] * n  # Initially, Cry can win from all nodes (because of the rules)
    n_cry_wins_next = out_degree[:]  # Counts how many edges need to stay blue for Cry to win
    river_wins = [False] * n
    n_river_wins_next = [0] * n  # Tracks number of red parents for each node to determine River wins
    ans = []
    for _ in range(q):
        t, u = map(lambda x: int(x) - 1, input().split())
        if t == 0:
            # Update node u to red
            if red[u]:
                continue  # Already red, no change needed
            red[u] = True
            q_queue = []
            if cry_wins[u]:
                # Cry loses the node if it becomes red
                cry_wins[u] = False
                for v in in_edges[u]:
                    n_cry_wins_next[v] -= 1  # Decrease count as one parent became red
                    q_queue.append(v)
            if not river_wins[u]:
                # River wins this node if it was not already a win for him && now becomes red
                river_wins[u] = True
                for v in in_edges[u]:
                    n_river_wins_next[v] += 1  # Increase red in-degree count
                    q_queue.append(~v)  # Use ~ to indicate we're propagating from river side (for handling)

            for u_prop in q_queue:
                if u_prop >= 0:
                    # Case propagated from Cry win side
                    if river_wins[u_prop]:
                        continue
                    if n_cry_wins_next[u_prop] < out_degree[u_prop]:
                        # If not all parents maintain cry_wins, River now wins this node
                        river_wins[u_prop] = True
                        for v in in_edges[u_prop]:
                            n_river_wins_next[v] += 1
                            q_queue.append(~v)
                else:
                    # Case from River win side
                    u_prop = ~u_prop
                    if not cry_wins[u_prop]:
                        continue
                    if n_river_wins_next[u_prop] == out_degree[u_prop]:
                        # All parents are red, so Cry loses
                        cry_wins[u_prop] = False
                        for v in in_edges[u_prop]:
                            n_cry_wins_next[v] -= 1
                            q_queue.append(v)
        elif t == 1:
            # Query whether Cry wins from node u
            ans.append("YES" if cry_wins[u] else "NO")
    return "\n".join(ans)


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/