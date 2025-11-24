# Problem: CF 1498 F - Christmas Game
# https://codeforces.com/contest/1498/problem/F

"""
Algorithm: Tree Rerooting with XOR Game State
Techniques: 
- Tree rerooting
- Bit manipulation (XOR)
- Prefix/suffix computation using exclusive function

Time Complexity: O(n * k * log(n))
Space Complexity: O(n * k)

The problem asks us to determine the winner of a game played on a tree where players can move presents from deeper nodes to ancestor nodes at a fixed depth k. The key insight is that each node's game state can be represented as a vector of length k, where each element corresponds to a specific depth level. Using tree rerooting, we compute for each possible root whether the total game state (XOR of all nodes' states) leads to a winning or losing position for Alice.

This code implements a general rerooting framework to compute dynamic programming states efficiently across all possible tree roots. The game state for each node is computed as the XOR of its presents at different depth levels, and the result for each root is determined by checking if the total XOR of all nodes' states is non-zero (indicating Alice wins).
"""

import sys

input = sys.stdin.readline


def exclusive(A, zero, combine, node):
    n = len(A)
    exclusiveA = [zero] * n

    for bit in range(n.bit_length())[::-1]:
        for i in range(n >> max(bit - 1, 0))[::-1]:

            exclusiveA[i] = exclusiveA[i // 2]
        for i in range(n & ~(bit == 0)):

            ind = (i >> bit) ^ 1
            exclusiveA[ind] = combine(exclusiveA[ind], A[i], node, i)
    return exclusiveA


def rerooter(graph, default, combine, finalize=lambda nodeDP, node, eind: nodeDP):
    n = len(graph)
    rootDP = [0] * n
    forwardDP = [None] * n
    reverseDP = [None] * n

    DP = [0] * n
    bfs = [0]
    P = [0] * n
    for node in bfs:
        for nei in graph[node]:
            if P[node] != nei:
                P[nei] = node
                bfs.append(nei)

    for node in reversed(bfs):
        nodeDP = default[node]
        for eind, nei in enumerate(graph[node]):
            if P[node] != nei:
                nodeDP = combine(nodeDP, DP[nei], node, eind)
        DP[node] = finalize(nodeDP, node, graph[node].index(P[node]) if node else -1)

    for node in bfs:
        DP[P[node]] = DP[node]
        forwardDP[node] = [DP[nei] for nei in graph[node]]
        rerootDP = exclusive(forwardDP[node], default[node], combine, node)
        reverseDP[node] = [
            finalize(nodeDP, node, eind) for eind, nodeDP in enumerate(rerootDP)
        ]
        rootDP[node] = finalize(
            (
                combine(rerootDP[0], forwardDP[node][0], node, 0)
                if n > 1
                else default[node]
            ),
            node,
            -1,
        )
        for nei, dp in zip(graph[node], reverseDP[node]):
            DP[nei] = dp
    return rootDP, forwardDP, reverseDP


n, k = [int(x) for x in input().split()]
k2 = k * 2

graph = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v = [int(x) - 1 for x in input().split()]
    graph[u].append(v)
    graph[v].append(u)

A = [int(x) for x in input().split()]


default = [[A[node]] + [0] * (k2 - 1) for node in range(n)]


def combine(nodeDP, neiDP, node, eind):
    A = list(nodeDP)
    B = neiDP
    for i in range(k2):
        A[i] ^= B[i - 1]
    return A


def finalize(nodeDP, node, eind):
    return nodeDP


rootDP, forwardDP, reverseDP = rerooter(graph, default, combine, finalize)


def xorsum(A):
    x = 0
    for a in A[k:]:
        x ^= a
    return x


print(*[+(xorsum(dp) > 0) for dp in rootDP])


# https://github.com/VaHiX/CodeForces/