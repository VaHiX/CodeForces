# Problem: CF 2059 D - Graph and Graph
# https://codeforces.com/contest/2059/problem/D

"""
D. Graph and Graph

Purpose:
This problem involves finding the minimum total cost of moving two tokens simultaneously in two different graphs, where each token moves to adjacent vertices in its respective graph at each step. The cost of a move is defined as the absolute difference between the new positions of the two tokens.

Approach:
- Use a modified Dijkstra-like algorithm with a deque (0-1 BFS) to find the minimum cost path.
- Key idea: the state is represented by (v1, v2), where v1 and v2 are current positions of tokens in graph 1 and 2 respectively.
- Stop vertices are those where the two graphs share an edge between the same vertex (intersection of neighbors).
- For every valid move from a token at position u1 in graph 1 to u2 in graph 2, we calculate cost = offset + |u1 - u2|.
- We use a deque of queues based on cost for 0-1 BFS, allowing for better efficiency compared to regular Dijkstra.

Time Complexity: O(n * (m1 + m2)) per test case.
Space Complexity: O(n^2 + m1 + m2) for storing adjacency lists and seen matrix.

Algorithms/Techniques:
- 0-1 BFS using deque with buckets
- Graph traversal with state tracking
"""

import sys
from collections import deque


def input_general():
    return sys.stdin.readline().rstrip("\r\n")


def input_num():
    return int(sys.stdin.readline().rstrip("\r\n"))


def input_multi(x=int):
    return map(x, sys.stdin.readline().rstrip("\r\n").split())


def input_list(x=int):
    return list(input_multi(x))


def main():
    n, s1, s2 = input_multi()
    m1 = input_num()
    ed1 = [[] for _ in range(n + 1)]
    for _ in range(m1):
        u, v = input_multi()
        ed1[u].append(v)
        ed1[v].append(u)
    m2 = input_num()
    ed2 = [[] for _ in range(n + 1)]
    for _ in range(m2):
        u, v = input_multi()
        ed2[u].append(v)
        ed2[v].append(u)
    stop = set()
    # Identify vertices where both graphs have a common neighbor
    for u in range(1, n + 1):
        if set(ed1[u]).intersection(set(ed2[u])):
            stop.add(u)
    seen = [[10**10 for _ in range(n + 1)] for _ in range(n + 1)]
    seen[s1][s2] = 0
    dq = deque([[(s1, s2)]])  # Initialize queue with starting state (s1,s2)
    offset = 0
    in_stack = 1  # Counter of elements to be processed
    while in_stack:
        # Remove empty queues
        while len(dq[0]) == 0:
            offset += 1
            dq.popleft()
        v1, v2 = dq[0].pop()  # Get next state to process
        in_stack -= 1
        if v1 == v2 and v1 in stop:  # If both tokens are at same position and it's a stop vertex
            print(offset)
            return
        if offset > seen[v1][v2]:  # Skip outdated states
            continue
        for u1 in ed1[v1]:  # Move token in first graph
            for u2 in ed2[v2]:  # Move token in second graph
                new = abs(u1 - u2)  # Cost to reach new state
                cost = offset + new
                if cost < seen[u1][u2]:  # Update minimum cost if better path found
                    seen[u1][u2] = cost
                    while len(dq) <= new:  # Extend deque if needed
                        dq.append([])
                    dq[new].append((u1, u2))  # Add new state to appropriate queue
                    in_stack += 1  # Increment counter
    print(-1)  # No solution found


if __name__ == "__main__":
    cases = input_num()
    for _ in range(cases):
        main()



# https://github.com/VaHiX/codeForces/