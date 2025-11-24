# Problem: CF 1685 D1 - Permutation Weight (Easy Version)
# https://codeforces.com/contest/1685/problem/D1

"""
Algorithm: 
This solution uses a cycle decomposition approach to find a permutation with minimal weight.
The key idea is to decompose the given permutation into cycles and then rearrange these cycles
to minimize the total weight.

Time Complexity: O(n) where n is the size of the permutation
Space Complexity: O(n) for storing the nodes and auxiliary arrays

Approach:
1. Build a doubly linked list representing the permutation cycles.
2. Traverse through cycles and rewire the links to minimize weight.
3. Construct the final permutation from the rewired structure.
"""

import sys

input = sys.stdin.readline


class Node:
    def __init__(self, i):
        self.i = i
        self.nex = None
        self.bef = None


def solve():
    n = int(input())
    P = list(map(int, input().split()))
    node = [Node(i) for i in range(n)]
    for i, p in enumerate(P):
        p -= 1
        node[p].nex = node[i]
        node[i].bef = node[p]
    used = [False] * n
    V = node[0]
    while not used[V.i]:
        used[V.i] = True
        V = V.nex
    for i in range(n):
        if used[i]:
            continue
        V = node[i]
        while not used[V.i]:
            used[V.i] = True
            V = V.nex
        # Swap links to minimize weight - this is a key part of the algorithm
        node[i].nex, node[i - 1].nex, node[i].nex.bef, node[i - 1].nex.bef = (
            node[i - 1].nex,
            node[i].nex,
            node[i - 1],
            node[i],
        )

    ans = [1]
    V = node[0].nex
    while V.i != 0:
        ans.append(V.i + 1)
        V = V.nex
    print(*ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/