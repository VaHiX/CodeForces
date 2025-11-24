# Problem: CF 2172 M - Maximum Distance To Port
# https://codeforces.com/contest/2172/problem/M

"""
Algorithm: BFS to compute shortest distances from port (city 1) to all other cities.
Then, for each product type, find the maximum distance among all cities producing that product.

Time Complexity: O(n + m) - BFS traversal visits each node and edge once.
Space Complexity: O(n + m) - Storage for adjacency list and distance array.

The problem asks to find the longest shortest path from any city producing a specific product to the port city (city 1).
We use BFS from city 1 to compute all shortest distances, then for each product type,
we find the maximum distance among all nodes of that product type.
"""

n, m, k = map(int, input().split())
p = list(map(int, input().split()))  # Product types of each city
g = [[] for _ in range(n + 1)]       # Adjacency list representation of the graph
for _ in range(m):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)

d = [-1] * (n + 1)   # Distance array initialized to -1 (unvisited)
d[1] = 0             # Distance from port (city 1) to itself is 0
q = [1]              # Queue for BFS, starting with port city 1
h = 0                # Head pointer for the queue

# Perform BFS to compute distances from port city 1
while h < len(q):
    u = q[h]
    h += 1
    for v in g[u]:   # For each neighbor v of u
        if d[v] == -1:  # If v is unvisited
            d[v] = d[u] + 1  # Set distance to u's distance + 1
            q.append(v)      # Add v to queue for further exploration

r = [0] * (k + 1)    # Result array for maximum distance per product type
for i in range(1, n + 1):  # For each city
    product_type = p[i - 1]  # Product type of city i (0-indexed in p)
    r[product_type] = max(r[product_type], d[i])  # Update max distance for this product type

print(*r[1:])  # Output result for product types 1 to k


# https://github.com/VaHiX/CodeForces/