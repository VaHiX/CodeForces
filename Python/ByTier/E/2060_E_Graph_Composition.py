# Problem: CF 2060 E - Graph Composition
# https://codeforces.com/contest/2060/problem/E

"""
E. Graph Composition

Problem Description:
Given two undirected graphs F and G with n vertices, determine the minimum number of operations to make F structurally equivalent to G.
Operations allowed:
1. Remove an edge from F if it exists.
2. Add an edge to F if it doesn't exist.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression for tracking connected components.
- Process edges of G first to build a reference structure.
- For each edge in F, decide whether it needs to be removed or kept based on component connectivity in G.
- Count how many operations are needed to match the connectivity of G.

Time Complexity: O(m1 + m2 + n * α(n)) where α(n) is the inverse Ackermann function (nearly constant).
Space Complexity: O(n)

"""

import sys

input = sys.stdin.readline


def find(p, x):
    # Find root with path compression
    stack = []
    while x != p[x]:
        stack.append(x)
        x = p[x]
    while stack:
        p[stack.pop()] = x  # Path compression
    return x


def union(p, a, b):
    # Union by smaller root
    a, b = find(p, a), find(p, b)
    if a < b:
        p[b] = a
    else:
        p[a] = b


t = int(input())
for _ in range(t):
    n, m1, m2 = map(int, input().split())
    p1 = [i for i in range(n)]  # Union-Find for graph F
    p2 = [i for i in range(n)]  # Union-Find for graph G (reference)
    cnt1, cnt2 = n, n  # Number of connected components in F and G
    
    edge1 = []
    for _ in range(m1):
        a, b = map(int, input().split())
        a -= 1
        b -= 1
        edge1.append((a, b))
    
    for _ in range(m2):
        a, b = map(int, input().split())
        a -= 1
        b -= 1
        if find(p2, a) != find(p2, b):  # If not already in same component
            union(p2, a, b)
            cnt2 -= 1  # Reduce connected components count
    
    ans = 0
    for i, j in edge1:
        if find(p2, i) != find(p2, j):
            # Edge in F connects different components in G => need to add edge in F
            ans += 1
        elif find(p1, i) != find(p1, j):
            # Edge in F is in correct component in G but not yet unioned -> merge it
            union(p1, i, j)
            cnt1 -= 1
            
    print(ans + cnt1 - cnt2)


# https://github.com/VaHiX/codeForces/