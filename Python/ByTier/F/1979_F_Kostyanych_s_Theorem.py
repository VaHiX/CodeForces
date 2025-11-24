# Problem: CF 1979 F - Kostyanych's Theorem
# https://codeforces.com/contest/1979/problem/F

"""
Algorithm: Kostyanych's Theorem - Finding Hamiltonian Path
Approach:
    - Use interactive queries to find a Hamiltonian path in a modified complete graph.
    - The graph starts as a complete graph with n vertices, then n-2 edges are removed.
    - We use a greedy strategy based on degree information to identify vertices and their connections.
    - At each step:
        * Query the number of vertices with degree at least (n-2) where n is current vertex count
        * The returned vertex v1 is removed from the graph
        * If v2 is non-zero, it's the vertex not connected to v1
        * Record the connection (v1, v2) or (v3, 0) if v2 is zero
    - After all but two vertices are removed:
        * Reconstruct the path from the recorded connections
        * Join the two parts in reverse order to form a Hamiltonian path

Time Complexity: O(n^2) due to potential nested loop in reconstruction of path
Space Complexity: O(n) for storing vertex set and operations

"""

from sys import stdout


def query(d):
    # Query the number of vertices with degree >= d
    print("? %d" % d)
    stdout.flush()
    return map(int, (input().split()))


for _ in range(int(input())):
    # Initialize set of vertices
    vx = set(i for i in range(1, int(input()) + 1))
    ops = []  # Store the connections found during query process
    
    # Continue until only 2 vertices remain
    while len(vx) > 2:
        # Query for vertices with degree >= (current number of vertices - 2)
        v1, v2 = query(len(vx) - 2)
        # Remove v1 from the active vertex set
        vx.remove(v1)
        # If v2 > 0, it means a vertex not connected to v1 was provided
        if v2 > 0:
            # Append the connection (v1, v2)
            ops += [(v1, v2)]
        else:
            # If v2 == 0, v1 is connected to all other vertices; need another query
            v3, _ = query(0)
            # Remove v3 from active set
            vx.remove(v3)
            # Record that neither v1 nor v3 are connected to a vertex (they form a pair)
            ops += [(v3, 0), (v1, 0)]
    
    # Get the last two remaining vertices
    p1, p2 = list(vx), []
    # Reconstruct paths from the collected operations
    for v1, v2 in ops[::-1]:
        # Depending on which part of path the vertex belongs to, append accordingly
        (p2 if p1[-1] == v2 else p1).append(v1)
    
    # Output the final Hamiltonian path by reversing and combining the two parts
    print("! %s" % " ".join(map(str, p1[::-1] + p2)))
    stdout.flush()


# https://github.com/VaHiX/CodeForces/