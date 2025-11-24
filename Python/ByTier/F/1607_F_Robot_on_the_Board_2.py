# Problem: CF 1607 F - Robot on the Board 2
# https://codeforces.com/contest/1607/problem/F

"""
Algorithm: Find the starting position on a grid that allows a robot to take the maximum number of steps before breaking.
Techniques: 
- DFS traversal with cycle detection on a directed graph
- Graph representation using grid positions as nodes
- Cycle detection and distance calculation using negative values to mark visited nodes
- Distance tracking for each node to determine maximum steps

Time Complexity: O(n * m) where n and m are dimensions of the grid
Space Complexity: O(n * m) for storing the distance array and recursion stack
"""

dij = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # Direction vectors: right, down, left, up
inf = 4294967295  # Large constant representing infinity
md = 998244353  # Modulo value (not used in current implementation)

for _ in range(int(input())):
    input()  # Read blank line
    h, w = map(int, input().split())  # Read grid dimensions
    n = h * w + 1  # Total nodes including exit node
    e = h * w  # Exit node index
    # Convert characters to direction indices (R=0, D=1, L=2, U=3)
    ss = [["RDLU".find(c) for c in input().rstrip()] for _ in range(h)]

    def dfs(u):
        """DFS function to traverse and calculate distance from node u"""
        d = -inf  # Initialize distance counter with large negative value
        uu = []  # Stack to keep track of visited nodes in current path
        i, j = divmod(u, w)  # Convert linear index to 2D coordinates
        while dist[u] == -2:  # While node is unvisited
            uu.append(u)  # Add node to current path
            dist[u] = d  # Mark node with current distance
            d += 1  # Increment distance
            di, dj = dij[ss[i][j]]  # Get direction from current cell
            i, j = i + di, j + dj  # Move to next cell
            if i < 0 or j < 0 or i >= h or j >= w:  # If out of bounds
                u = e  # Set to exit node
                break
            u = i * w + j  # Convert coordinates back to linear index
        if dist[u] < -2:  # If we hit a cycle, adjust distance
            d -= dist[u]  # Calculate cycle length
            dist[u] = d  # Set distance for cycle start
            while uu and uu[-1] != u:  # Process nodes in the cycle
                v = uu.pop()  # Pop from stack
                dist[v] = d  # Set distance to cycle length
        else:  # If reached a visited node (not part of cycle)
            uu.append(u)  # Add to path
        uu.reverse()  # Reverse to get proper order
        for u, v in zip(uu, uu[1:]):  # Set distances for all nodes in path
            dist[v] = dist[u] + 1  # Increment distance

    dist = [-2] * n  # Initialize distance array with -2 (unvisited)
    dist[e] = 0  # Exit node has distance 0
    for i in range(h):  # For each row
        for j in range(w):  # For each column
            u = i * w + j  # Convert to linear index
            if dist[u] != -2:  # Skip if already visited
                continue
            dfs(u)  # Start DFS from this node
    mx = max(dist)  # Find maximum distance
    u = dist.index(mx)  # Find index of maximum distance
    i, j = divmod(u, w)  # Convert back to 2D coordinates
    print(i + 1, j + 1, mx)  # Output 1-indexed coordinates and maximum steps


# https://github.com/VaHiX/CodeForces/