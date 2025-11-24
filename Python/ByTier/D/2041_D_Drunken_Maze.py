# Problem: CF 2041 D - Drunken Maze
# https://codeforces.com/contest/2041/problem/D

"""
D. Drunken Maze
Purpose: Find the shortest path from S to T in a maze, with the constraint that
         no more than 3 consecutive steps can be in the same direction.
         Uses 0-1 BFS with state tracking for (row, col, last_direction, consecutive_count).

Algorithms/Techniques: 
    - 0-1 BFS (Breadth-First Search with state tracking)
    - State compression: (n, m, direction, consecutive_steps)

Time Complexity: O(n * m * 4 * 4) = O(n * m)
Space Complexity: O(n * m * 4 * 4) = O(n * m)

State representation:
    - n, m: current position
    - i: last direction taken (0=right, 1=down, 2=left, 3=up)
    - c: number of consecutive steps in that direction
"""
from collections import deque

N, M = map(int, input().split())
S = [input() for n in range(N)]
dn = [0, 1, 0, -1]  # Direction deltas for right, down, left, up
dm = [1, 0, -1, 0]

# Indexing function to map state to a unique integer for distance array
def idx(n, m, d, c):
    return ((n * M + m) * 4 + d) * 4 + c

inf = 1 << 30  # Infinite distance placeholder
dist = [inf] * N * M * 4 * 4  # Distance array to track minimum steps to each state
queue = deque([])

# Initialize starting point
for n in range(N):
    for m in range(M):
        if S[n][m] == "S":
            dist[idx(n, m, 0, 0)] = 0  # Start with direction 0 (right) and 0 consecutive steps
            queue.append((n, m, 0, 0))
            
while queue:
    n, m, i, c = queue.popleft()  # Current position, direction, consecutive count
    d = dist[idx(n, m, i, c)]  # Current distance to this state
    
    # Try all 4 directions
    for ii in range(4):
        # If same direction as previous, increment counter, else reset to 1
        if i == ii:
            cc = c + 1
        else:
            cc = 1
            
        # If we have more than 3 steps in the same direction, skip
        if cc == 4:
            continue
            
        # Compute next position
        nn = n + dn[ii]
        mm = m + dm[ii]
        
        # Check bounds and if cell is not a wall
        if 0 <= nn < N and 0 <= mm < M and S[nn][mm] != "#":
            dd = d + 1  # One step forward
            # If a shorter path to this state is found
            if dist[idx(nn, mm, ii, cc)] > dd:
                dist[idx(nn, mm, ii, cc)] = dd
                queue.append((nn, mm, ii, cc))  # Add to queue for further processing

# Find the minimum distance to reach the end cell T
ans = inf
for n in range(N):
    for m in range(M):
        if S[n][m] == "T":
            for i in range(4):    # Any direction
                for c in range(4): # Any consecutive count
                    ans = min(ans, dist[idx(n, m, i, c)])
                    
# Output result: -1 if no path exists, otherwise the minimum steps
if ans == inf:
    ans = -1
print(ans)


# https://github.com/VaHiX/CodeForces/