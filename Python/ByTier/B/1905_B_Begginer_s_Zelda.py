# Problem: CF 1905 B - Begginer's Zelda
# https://codeforces.com/contest/1905/problem/B

"""
Minimum Zelda Operations on a Tree

Algorithm:
The problem reduces to finding the minimum number of operations to reduce a tree to a single vertex.
Each operation compresses a path between two vertices into one vertex. 
The key insight is that we need to think in terms of "leaves" (vertices with degree 1) and how they can be paired.

Since we are essentially trying to pair up leaf nodes such that each pair reduces to one node,
the minimum number of operations needed corresponds to:
(number of leaves + 1) // 2

Time Complexity: O(n) where n is the number of vertices
Space Complexity: O(n) for storing the degree array
"""

import sys

input = sys.stdin.readline


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n = readInt()
    deg = [0] * n
    for _ in range(n - 1):
        u, v = readInts()
        deg[u - 1] += 1
        deg[v - 1] += 1
    # Count the number of leaves (degree 1) and compute operations needed
    return (sum([d == 1 for d in deg]) + 1) // 2


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/