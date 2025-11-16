# Problem: CF 1764 F - Doremy's Experimental Tree
# https://codeforces.com/contest/1764/problem/F

"""
Code Purpose:
This code reconstructs a tree from given f(i,j) values, which represent the sum of shortest path distances from each vertex to the cycle formed by adding an edge of weight 1 between vertices i and j. 
The approach uses a Union-Find data structure to build the minimum spanning tree with a special weight calculation based on the given f(i,j) values. 

Algorithms/Techniques:
1. Union-Find (Disjoint Set Union) for building the minimum spanning tree
2. Mathematical derivation to compute edge weights based on the f(i,j) values
3. Sorting edges by computed weights to construct the tree in MST order

Time Complexity:
- Time: O(n^3 log n) due to computing all edges (O(n^2)), sorting them (O(n^2 log n)), and Union-Find operations (n^2 for union operations)
- Space: O(n^2) for storing the input matrix and edges

Space Complexity:
- O(n^2) for storing the input matrix and the edges list
- O(n) for Union-Find structure
"""

from collections import defaultdict


class UnionFind:
    def __init__(self, n):
        self.n = n
        self.parents = [-1] * n

    def find(self, x):
        if self.parents[x] < 0:
            return x
        else:
            self.parents[x] = self.find(self.parents[x])
            return self.parents[x]

    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)

        if x == y:
            return False

        if self.parents[x] > self.parents[y]:
            x, y = y, x

        self.parents[x] += self.parents[y]
        self.parents[y] = x
        return True

    def size(self, x):
        return -self.parents[self.find(x)]

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def members(self, x):
        root = self.find(x)
        return [i for i in range(self.n) if self.find(i) == root]

    def roots(self):
        return [i for i, x in enumerate(self.parents) if x < 0]

    def group_count(self):
        return len(self.roots())

    def all_group_members(self):
        group_members = defaultdict(list)
        for member in range(self.n):
            group_members[self.find(member)].append(member)
        return group_members


from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    n = int(input())
    A = [list(map(int, input().split())) for _ in range(n)]

    edges = []
    # For each pair of vertices (i,j), compute the weight using a formula derived from the f(i,j) values
    for i in range(n):
        for j in range(i):
            d = A[i][i] + A[j][j] - 2 * A[i][j]
            if d % n == 0:  # Check if the calculation leads to an integer weight
                d //= n
                # Encode the edge (i,j) with its weight in a single number for sorting
                edges.append(d * n * n + i * n + j)
    edges.sort()  # Sort edges by their computed weights
    UF = UnionFind(n)

    # Process each edge in sorted order and add it to the MST if it doesn't form a cycle
    for tmp in edges:
        d = tmp // (n * n)  # Extract the weight
        ij = tmp - n * n * d  # Extract the vertex indices
        i = ij // n  # Extract i
        j = ij - n * i  # Extract j
        if UF.union(i, j):  # If the edge connects two separate components, add it to the tree
            print(i + 1, j + 1, d)  # Output the edge (1-indexed) with its weight


solve()


# https://github.com/VaHiX/CodeForces/