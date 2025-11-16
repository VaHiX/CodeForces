# Problem: CF 1210 A - Anadi and Domino
# https://codeforces.com/contest/1210/problem/A

"""
A. Anadi and Domino

Problem Description:
Anadi has a set of 21 dominoes, each with two parts containing from 1 to 6 dots.
He wants to place as many dominoes as possible on the edges of a graph such that:
- Each domino can be placed on one edge
- Each edge fits at most one domino
- For each vertex, all domino halves directed toward it must have the same number of dots

Algorithm:
- Generate all possible dominoes (1-1, 1-2, ..., 6-6)
- Test pairs of vertices (i, j) to see how many dominoes can be placed
- For each pair (i,j), compute all edges incident to these vertices
- Check which edges go from i to j or j to i, and count how many additional dominoes can be placed in this scenario

Time Complexity: O(n^2 * m) where n is number of vertices and m is number of edges.
Space Complexity: O(m) for storing edges.

"""
def solve(n, e, one):
    v = list(range(2, n + 1))
    for i in one:
        v.insert(
            i,
        )


n, m = map(int, input().split())
if n <= 6:
    print(m)
else:
    e = []
    for _ in range(m):
        a, b = map(int, input().split())
        e.append((a - 1, b - 1))  # Convert to 0-based indexing
    maxe = 0
    for i in range(n - 1):
        for j in range(i + 1, n):  # Loop over all pairs of vertices
            one = {i, j}  # Set of two vertices
            dist = set()  # Set of neighbors of these two vertices
            ecnt = 0  # Counter for used edges
            for ee in e:  # Iterate through all edges
                if ee[0] in one:  # Edge connects to vertex i or j
                    dist.add(ee[1])  # Add neighbor to the set
                elif ee[1] in one:
                    dist.add(ee[0])
                else:
                    ecnt = ecnt + 1  # Edge is not connected to either vertex in (i,j)
            ecnt = ecnt + len(dist)  # Count valid domino placements along edges
            maxe = max(maxe, ecnt)  # Update maximum count
    print(maxe)


# https://github.com/VaHiX/codeForces/