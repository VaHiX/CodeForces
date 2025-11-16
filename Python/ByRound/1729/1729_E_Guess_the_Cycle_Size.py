# Problem: CF 1729 E - Guess the Cycle Size
# https://codeforces.com/contest/1729/problem/E

"""
Interactive problem to determine the size of a hidden cyclic graph.

The algorithm uses the property of cyclic graphs where for any two vertices a and b,
there are exactly two paths between them, and the sum of their lengths equals the total
number of vertices in the cycle (n). By querying pairs of vertices and analyzing the
responses, we can determine n.

Time Complexity: O(1) for the main loop, but depends on the number of queries (at most 23)
Space Complexity: O(1)

Approach:
- Query vertex 1 with vertices from 2 to 24.
- For each query, also query the reverse path.
- If both paths have equal length, their sum gives us info about the cycle.
- If one path returns -1, it indicates the vertex is outside the graph.
"""

for t in range(2, 25):  # Iterate through possible vertex indices
    print(f"? 1 {t }")  # Query from vertex 1 to vertex t
    x = int(input())    # Read the response for path 1->t
    print(f"? {t } 1")  # Query from vertex t to vertex 1 (reverse path)
    y = int(input())    # Read the response for path t->1
    if x != y:          # If the two paths have different lengths
        z = x + y       # The sum of the two path lengths equals n
    if x == -1:         # If the first query returns -1, vertex t is outside the graph
        z = t - 1       # The number of vertices is t-1
        break           # Exit the loop since we know the size
print("!", z)           # Output the determined size of the cycle


# https://github.com/VaHiX/CodeForces/