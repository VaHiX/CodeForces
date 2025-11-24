# Problem: CF 1866 I - Imagination Castle
# https://codeforces.com/contest/1866/problem/I

"""
Algorithms/Techniques: Dynamic Programming, Greedy Simulation, Game Theory

Time Complexity: O(N * M + K)
Space Complexity: O(N * M)

This code determines the winner of a game played on an N x M chessboard where a castle piece moves 
only right or down. The game ends when a player moves the castle to a special tile (a win), or if no 
more moves are possible (a loss). Using backward simulation and greedy strategy, we determine whether 
the first player (Chaneka) has a winning move or not.

The key insight:
- For each row from bottom to top, we process special tiles.
- We track the rightmost column that is "blocked" by a special tile in the current row segment.
- If there exists a valid path to a special tile from (1,1), then Chaneka wins immediately.
"""

import sys

input = sys.stdin.buffer.readline
n, m, k = map(int, input().split())
special = [[] for _ in range(n)]
for _ in range(k):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    special[x].append(y)

j = m - 1
has0 = [0] * m

# Process rows from bottom to top (excluding the first row)
for i in range(n - 1, 0, -1):
    # Move j back while has0[j] is true (column is blocked)
    while j >= 0 and has0[j]:
        j -= 1
    
    mxjt = -1
    # For each special tile in current row, mark it as blocked
    for jt in special[i]:
        has0[jt] = 1
        mxjt = max(jt, mxjt)
    
    # If we can still move right and the current column j is beyond the farthest blocked column
    if j >= 0 and j > mxjt:
        has0[j] = 1

# Check if any special tile is in the first row or if (1,1) is blocked
if special[0] or has0[0]:
    print("Chaneka")
else:
    # If no special tile on first row and column 0 is not blocked,
    # then check if there's a valid move left after all processing
    while j >= 0 and has0[j]:
        j -= 1
    print("Chaneka" if j else "Bhinneka")


# https://github.com/VaHiX/codeForces/