# Problem: CF 1898 F - Vova Escapes the Matrix
# https://codeforces.com/contest/1898/problem/F

"""
Algorithm: Maximize blocked cells while preserving matrix type
Techniques: 
- BFS to find distances from Vova's position to all reachable cells
- BFS with bipartite graph tracking to find shortest paths from exits
- Type classification based on number of exits

Time Complexity: O(n * m) per test case, since each cell is visited at most a constant number of times
Space Complexity: O(n * m) for storing the grid and distance arrays

The problem involves determining the maximum number of cells that can be blocked such that:
1. Vova's starting position is not blocked
2. The matrix type (1st, 2nd, or 3rd) remains unchanged

Approach:
1. Classify the matrix type by counting reachable exits
2. For 1st type (no exits): return 0
3. For 2nd type (single exit): maximize blocking on path to exit
4. For 3rd type (multiple exits): use a more complex approach to block cells that don't affect exit connectivity
"""
import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Convert 2D coordinates to 1D index
    return u * m + v


def bfs(s):
    # BFS from Vova's position to compute distances to all reachable cells
    q = [s]
    dist = [inf] * (n * m)
    dist[s] = 0
    for i in q:
        x, y = divmod(i, m)
        di = dist[i]
        for dx, dy in v0:
            nx, ny = x + dx, y + dy
            if not 0 <= nx < n or not 0 <= ny < m:
                continue
            j = f(nx, ny)
            if not z[j] and dist[j] == inf:
                q.append(j)
                dist[j] = di + 1
    return dist


def bfs2():
    # BFS to find shortest path from each exit to all cells - two-stage approach
    q = []
    for i in range(1, n - 1):
        # Add left and right boundary cells (except corners) to queue
        if not z[f(i, 0)]:
            q.append(f(i, 0) << 1)
        if not z[f(i, m - 1)]:
            q.append(f(i, m - 1) << 1)
    for j in range(1, m - 1):
        # Add top and bottom boundary cells (except corners) to queue
        if not z[f(0, j)]:
            q.append(f(0, j) << 1)
        if not z[f(n - 1, j)]:
            q.append(f(n - 1, j) << 1)
    
    # dist and v arrays for tracking distances and cell identifiers 
    dist, v = [inf] * (2 * n * m), [0] * (2 * n * m)
    for i in q:
        dist[i], v[i] = 0, i >> 1  # Initialize queue with distance 0 and vertex id
        
    for i in q:
        x, y = divmod(i >> 1, m)
        di, vi = dist[i], v[i]
        for dx, dy in v0:
            nx, ny = x + dx, y + dy
            if not 0 <= nx < n or not 0 <= ny < m:
                continue
            j = f(nx, ny) << 1  # Double index to represent both stages of the graph
            if z[j >> 1]:  # If cell is blocked
                continue
            if dist[j] == inf:
                q.append(j)
                dist[j], v[j] = di + 1, vi  # Add to queue with updated distance and vertex id
            elif dist[j ^ 1] == inf and v[j] ^ vi:  # If we're trying to reach the other vertex stage
                q.append(j ^ 1)
                dist[j ^ 1], v[j ^ 1] = di + 1, vi  # Add to queue with flipped bit for stage switching
    return dist


t = int(input())
ans = []
inf = pow(10, 9) + 1  # Infinity value for distance tracking
v0 = [(1, 0), (-1, 0), (0, 1), (0, -1)]  # Possible movement directions (down, up, right, left)
for _ in range(t):
    n, m = map(int, input().split())
    z = [0] * (n * m)  # Grid to represent blocked cells (1) and empty cells (0)
    for i in range(n):
        s = list(input().rstrip())
        for j in range(m):
            if s[j] & 1:  # If character is '#', mark as blocked
                z[f(i, j)] = 1
            elif not s[j] & 8:  # If character is 'V', mark as empty but note starting position
                i0, j0 = i, j  # Store Vova's starting position
    s = f(i0, j0)  # Convert Vova's position to 1D index
    dist = bfs(s)  # Compute distance from Vova to all reachable cells
    
    c, mi = 0, inf  # c counts exits, mi tracks minimum distance to exit
    
    # Count exits and their distances from Vova
    for i in range(1, n - 1):
        if dist[f(i, 0)] ^ inf:  # If cell is reachable from left boundary
            c += 1
            mi = min(mi, dist[f(i, 0)])
        if dist[f(i, m - 1)] ^ inf:  # If cell is reachable from right boundary
            c += 1
            mi = min(mi, dist[f(i, m - 1)])
    for j in range(1, m - 1):
        if dist[f(0, j)] ^ inf:  # If cell is reachable from top boundary
            c += 1
            mi = min(mi, dist[f(0, j)])
        if dist[f(n - 1, j)] ^ inf:  # If cell is reachable from bottom boundary
            c += 1
            mi = min(mi, dist[f(n - 1, j)])
    
    # Handle different matrix types
    if c <= 1:
        # Type 1st (no exits) or 2nd (single exit)
        # Return the number of cells that can't be blocked (Vova, exits, and their distances)
        ans0 = n * m - sum(z) - 1 - c * mi
        ans.append(ans0)
        continue
    
    # For Type 3rd (multiple exits)
    d0 = bfs2()  # Compute shortest paths from exits to all cells
    mi = inf
    # Find minimum total distance from Vova to exit, passing through any cell
    for i in range(n * m):
        mi = min(mi, dist[i] + d0[i << 1] + d0[i << 1 ^ 1] + 1)  # Add 1 for connecting edge
    ans0 = n * m - sum(z) - mi  # Total cells minus blocked - minimum path cost
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/