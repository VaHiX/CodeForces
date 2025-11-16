# Problem: CF 2020 D - Connect the Dots
# https://codeforces.com/contest/2020/problem/D

"""
Algorithm: Union-Find (Disjoint Set Union)
Purpose: To determine the number of connected components after connecting points in specific patterns.

Time Complexity: O(n * d * α(n)) where α(n) is the inverse Ackermann function (practically constant).
Space Complexity: O(n + m) for storing the union-find structure and the temporary array 'l2'.

The solution uses a Union-Find data structure to efficiently manage and merge connected components.
It processes each operation to determine which points should be connected and then uses union operations
to merge the components accordingly. The key idea is to simulate the operations by marking which 
points are connected in a grid-like pattern using an auxiliary table 'l2' to track overlapping intervals.

Input:
- n points on a line and m operations
- Each operation specifies a start point 'a', step 'd', and number of points 'k' to connect in arithmetic progression

Output:
- Number of connected components after all operations
"""
import sys

input = sys.stdin.readline


def find(par, node):
    # Find root of node with path compression
    if par[node] != node:
        par[node] = find(par, par[node])
    return par[node]


def union(par, rank, node1, node2):
    # Union two nodes by rank
    root1 = find(par, node1)
    root2 = find(par, node2)
    if root1 != root2:
        if rank[root1] > rank[root2]:
            par[root2] = root1
        elif rank[root1] < rank[root2]:
            par[root1] = root2
        else:
            par[root2] = root1
            rank[root1] += 1


for i in range(int(input())):
    n, m = list(map(int, input().split()))
    # l2[i][d] stores the maximum k value for arithmetic sequence starting at i with step d
    l2 = [[-1 for p in range(11)] for j in range(n)]
    rank = [0] * n
    par = [j for j in range(n)]
    for j in range(m):
        a, d, k = list(map(int, input().split()))
        if k != 0:
            l2[a - 1][d] = max(l2[a - 1][d], k)
    for j in range(n):
        for d in range(1, 11):
            if l2[j][d] > 0:
                # Union current point with next one in the sequence
                union(par, rank, j, j + d)
                # Update the remaining length at next point
                l2[j + d][d] = max(l2[j + d][d], l2[j][d] - 1)
    # Count unique root nodes to determine number of connected components
    result = set(find(par, j) for j in range(n))
    print(len(result))


# https://github.com/VaHiX/CodeForces/