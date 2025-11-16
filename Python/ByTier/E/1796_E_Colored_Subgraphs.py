# Problem: CF 1796 E - Colored Subgraphs
# https://codeforces.com/contest/1796/problem/E

"""
Problem: E. Colored Subgraphs

This problem asks us to find the maximum possible cost of a tree when coloring its vertices 
under certain constraints. The cost is defined as the minimum number of vertices assigned 
to any color in a valid coloring.

Key constraints:
1. Vertices of the same color must form a connected subgraph.
2. Vertices of the same color must have distinct distances from the root.

We use a rerooting technique (tree DP) to compute for each node the minimum size of a color
class that can be formed in a valid coloring of the subtree rooted at that node.

Approach:
- Use rerooting technique to compute the answer for each node as root.
- For each node, maintain three values (a, b, minimum) representing:
  - a: minimum distance from root to any node in current subtree
  - b: second minimum distance from root to any node in current subtree
  - minimum: minimum size of a valid color class we can form

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the tree and DP states
"""

import random
import sys
from collections import Counter


class SafeCounter(Counter):
    """
    A Counter subclass that obfuscates keys using a random 64-bit integer to prevent hash collision attacks.

    Only supports integer keys by default. Other key types can be supported by converting them to integers.
    """

    def __init__(self, *args, r64=None, **kwargs):
        self.r64 = r64 or random.getrandbits(64)
        super().__init__(*args, **kwargs)

    def _transform_key(self, key):
        """Apply an XOR-based transformation to the key."""
        if not isinstance(key, int):
            raise TypeError(
                f"SafeCounter only supports integer keys, got {type (key )}."
            )
        return key ^ self.r64

    def __setitem__(self, key, value):
        transformed_key = self._transform_key(key)
        super().__setitem__(transformed_key, value)

    def __delitem__(self, key):
        transformed_key = self._transform_key(key)
        super().__delitem__(transformed_key)

    def __getitem__(self, key):
        transformed_key = self._transform_key(key)
        return super().__getitem__(transformed_key)

    def __contains__(self, key):
        transformed_key = self._transform_key(key)
        return super().__contains__(transformed_key)


def input():
    return sys.stdin.readline().rstrip("\r\n")


alphabets = list("abcdefghijklmnopqrstuvwxyz")
vowels = list("aeiou")
MOD1 = int(1e9 + 7)
MOD2 = 998244353
INF = int(1e17)
I = lambda: input()
II = lambda: int(input())
MII = lambda: map(int, input().split())
LI = lambda: list(input().split())
LII = lambda: list(map(int, input().split()))
LGMII = lambda: map(lambda x: int(x) - 1, input().split())
LGLII = lambda: list(map(lambda x: int(x) - 1, input().split()))
inf = float("inf")


def exclusive(A, zero, combine, node):
    n = len(A)
    exclusiveA = [zero] * n

    for bit in range(n.bit_length())[::-1]:
        for i in range(n)[::-1]:

            exclusiveA[i] = exclusiveA[i // 2]
        for i in range(n & ~int(bit == 0)):

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


def solve():
    n = int(input())
    graph = [[] for _ in range(n)]
    default = [(inf, inf, inf) for _ in range(n)]

    def combine(nodeDP, neiDP, node, eind):
        a, b, mini = nodeDP
        cp, cm = neiDP
        mini = min(cm, mini)
        if a > cp:
            b = a
            a = cp
        elif b > cp:
            b = cp
        return (a, b, mini)

    def finalize(nodeDP, node, eind):
        a, b, mini = nodeDP
        if a == inf:
            return 1, inf
        return a + 1, min(mini, b)

    for _ in range(n - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        graph[u].append(v)
        graph[v].append(u)
    rootDP, _, _ = rerooter(graph, default, combine, finalize)
    print(max(min(x) for x in rootDP))


for _ in range(II()):
    t = solve()


# https://github.com/VaHiX/CodeForces/