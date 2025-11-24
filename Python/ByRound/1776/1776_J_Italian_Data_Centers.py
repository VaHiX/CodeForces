# Problem: CF 1776 J - Italian Data Centers
# https://codeforces.com/contest/1776/problem/J

"""
Algorithm: Graph Simulation with BFS
Time Complexity: O(n * (n + m) * k) where n is number of servers, m is number of edges, k is years
Space Complexity: O(n * k) for storing the expanded graph

This code simulates the growth of a data center over k years and calculates the diameter.
Each year, for each server, two copies are created with same color, and for each edge,
connections are made according to the color of the servers involved.

The diameter is the maximum shortest path between any two servers in the final graph.
"""

def MII():
    return map(int, input().split())
def GMI():
    return map(lambda x: int(x) - 1, input().split())
def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))
def fmax(a, b):
    return a if a > b else b

n, m, k = MII()
colors = LGMI()  # Convert to 0-indexed colors
path = [[] for _ in range(n)]  # Adjacency list for original graph
for _ in range(m):
    u, v = GMI()  # Convert to 0-indexed
    path[u].append(v)
    path[v].append(u)

tmp = [[] for _ in range(2 * n)]  # Temporary storage for BFS queues
dis = [-1] * (2 * n)  # Distance array for BFS

inf = 2 * (n + k)  # Large value to represent infinity
ans = 0  # Store the final diameter

# For each server in the original graph, perform BFS to find distances
for i in range(n):
    # Initialize distances to infinity
    for j in range(2 * n):
        dis[j] = inf

    # Start BFS from server i (first copy)
    dis[i] = 0
    tmp[0].append(i)
    
    # BFS loop
    for i in range(2 * n):
        while tmp[i]:
            msk = tmp[i].pop()  # Get current node
            if dis[msk] == i:
                # Decompose msk to get server number and copy index
                s, u = divmod(msk, n)
                # Traverse neighbors in original graph
                for v in path[u]:
                    # Determine which copy of 'v' to connect to
                    # If same color, connect to same copy; else, connect to different copy
                    ns = s if colors[u] == colors[v] else s ^ 1
                    nv = ns * n + v  # Calculate index of new node
                    # Update distance if shorter path found
                    if dis[msk] + 1 < dis[nv]:
                        dis[nv] = dis[msk] + 1
                        tmp[dis[nv]].append(nv)  # Add to queue for next level

    # Calculate diameter contribution from this source node
    for j in range(n):
        # Check all pairs of nodes (j and j + n represent the two copies)
        # The actual distance will be the minimum of three possible paths:
        # 1. j -> j (same copy)
        # 2. j + n -> j + n (same copy)  
        # 3. j -> j + n (different copies)
        ans = fmax(ans, min(dis[j] + k, dis[j + n] + k, (dis[j] + dis[j + n] + k) // 2))

print(ans)


# https://github.com/VaHiX/CodeForces/