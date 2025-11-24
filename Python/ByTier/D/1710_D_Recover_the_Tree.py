# Problem: CF 1710 D - Recover the Tree
# https://codeforces.com/contest/1710/problem/D

"""
Algorithm: Union-Find (Disjoint Set Union) with Segment Processing
Purpose: Recover a tree from information about which contiguous segments of vertices form connected components.

The solution works by processing segments in order of increasing length. For each segment [i,j] that is good (i.e., the vertices i to j form a connected component), we try to union vertices i to j-1 with vertex j. This is done by maintaining a union-find structure where each set represents a connected component. We track the leftmost and rightmost vertices in each set.

Time Complexity: O(n^3 * α(n)) where α(n) is the inverse Ackermann function (nearly constant)
Space Complexity: O(n^2) for the input storage, plus O(n) for the DSU structure

The key idea is that for a good segment [i,j], the nodes i to j-1 must already be connected to j in the current forest. When we find such good segments, we merge the components appropriately.
"""

def run():
    n = int(input())

    # Read the input matrix A[i][j] where A[i][j] = 1 if segment [i, j] is good
    A = [[0] * n for _ in range(n)]
    for i in range(n):
        s = input()
        for j in range(i, n):
            A[i][j] = s[j - i] == "1"

    # Union-Find data structure elements
    c = list(range(n))    # parent pointers
    R = list(range(n))    # rightmost vertex in component
    L = list(range(n))    # leftmost vertex in component
    rank = [0] * n        # rank for union by rank optimization

    # Find root of element with path compression
    def comp(i):
        if c[i] != i:
            c[i] = comp(c[i])
        return c[i]

    # Union two components
    def union(i, j):
        p = comp(i)
        q = comp(j)
        if p == q:
            return
        # Union by rank
        if rank[p] < rank[q]:
            p, q = q, p
        c[q] = p
        if rank[p] == rank[q]:
            rank[p] += 1
        # Update bounds
        L[p] = min(L[p], L[q])
        R[p] = max(R[p], R[q])

    E = [] # List to store edges
    # Process segments of all lengths from 2 to n
    for k in range(2, n + 1):
        for i in range(n + 1 - k):
            j = i + k - 1
            cj = comp(j)
            if A[i][j]:  # If segment [i, j] is good
                P = []
                l = i
                # Collect all vertices in the left part that aren't directly connected to j
                while (cl := comp(l)) != cj:
                    P.append(l)
                    l = R[cl] + 1

                if P:
                    E.append((P[0], j))
                if len(P) > 1:
                    E.append((P[1], j))

                # Add edges between consecutive vertices in P
                for i in range(2, len(P)):
                    E.append((P[i - 2], P[i]))

                # Union all vertices in P with j
                for x in P:
                    union(x, j)

    # Print edges in sorted order to match output format
    E.sort()
    for x, y in E:
        print(x + 1, y + 1)


for _ in range(int(input())):
    run()


# https://github.com/VaHiX/CodeForces/