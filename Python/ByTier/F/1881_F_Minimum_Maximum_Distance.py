# Problem: CF 1881 F - Minimum Maximum Distance
# https://codeforces.com/contest/1881/problem/F

"""
Algorithm: Minimum Maximum Distance in Tree
Techniques: 
- Multi-source BFS to compute distances from all marked nodes
- Diameter finding using two BFS traversals
- Binary search on the answer (implicit in the problem)

Time Complexity: O(n) for each test case, as we do at most two BFS traversals
Space Complexity: O(n) for storing adjacency list and distance arrays

This solution finds the minimum value of f_i (maximum distance from vertex i to any marked vertex) 
by computing the tree diameter and using the fact that the answer is (diameter + 1) // 2.
"""

import sys


def main():
    input = sys.stdin.read().split()
    ptr = 0
    TC = int(input[ptr])
    ptr += 1
    for _ in range(TC):
        n = int(input[ptr])
        k = int(input[ptr + 1])
        ptr += 2
        mk = list(map(int, input[ptr : ptr + k]))
        ptr += k
        adj = [[] for _ in range(n + 1)]
        for __ in range(n - 1):
            x = int(input[ptr])
            y = int(input[ptr + 1])
            adj[x].append(y)
            adj[y].append(x)
            ptr += 2
        if k == 1:
            print(0)
            continue
        # First BFS from one of the marked vertices to find the farthest vertex
        d1 = [0] * (n + 1)
        d1[0] = -1
        stack = [(mk[0], 0)]
        while stack:
            u, p = stack.pop()
            d1[u] = d1[p] + 1
            for v in adj[u]:
                if v != p:
                    stack.append((v, u))
        # Find the vertex farthest from the starting marked vertex
        a = max(mk, key=lambda x: d1[x])
        # Second BFS from this farthest vertex to find the diameter
        d2 = [0] * (n + 1)
        d2[0] = -1
        stack = [(a, 0)]
        while stack:
            u, p = stack.pop()
            d2[u] = d2[p] + 1
            for v in adj[u]:
                if v != p:
                    stack.append((v, u))
        # The minimum maximum distance is half the diameter (rounded up)
        max_dis = max(d2[x] for x in mk)
        print((max_dis + 1) // 2)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/