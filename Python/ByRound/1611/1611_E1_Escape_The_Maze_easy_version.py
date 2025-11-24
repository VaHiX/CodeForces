# Problem: CF 1611 E1 - Escape The Maze (easy version)
# https://codeforces.com/contest/1611/problem/E1

"""
Algorithm: BFS-based solution to determine if Vlad can guarantee a win.
Techniques:
- BFS traversal to simulate the game
- For each possible exit (leaf node not equal to 1), check if Vlad can reach it before any friend.
- Time Complexity: O(n * k) in worst case, where n is number of nodes and k is number of friends.
- Space Complexity: O(n) for adjacency list and visited array.

The problem can be viewed as a race:
- Vlad starts at node 1 (0-indexed).
- Friends start at their respective nodes.
- Both move simultaneously, one step per turn.
- Vlad wins if he reaches a leaf node (degree 1) that is not node 1.
- Friends win if they catch Vlad (meet in same node or corridor).

We perform BFS starting from Vlad's initial position (node 0) and friends' positions.
We track the minimum time any person reaches each node.
If Vlad can reach a leaf before any friend, he wins.
"""

import sys
from collections import deque

input = sys.stdin.readline
S = lambda: input().rstrip()
I = lambda: int(S())
M = lambda: map(int, S().split())
L = lambda: list(M())
mod1 = 1000000000 + 7
mod2 = 998244353
for _ in range(I()):
    s = S()
    n, k = M()
    a = L()
    adj = [[] for i in range(n)]
    for i in range(n - 1):
        u, v = M()
        adj[u - 1].append(v - 1)
        adj[v - 1].append(u - 1)

    def bfs(i):
        q = deque()
        v = [0] * n
        v[i] = 1
        # Initialize queue with all friends' positions
        for j in a:
            q.append([j - 1, j - 1])  # [current_node, original_friend_node]
            v[j - 1] = 1
        # Add Vlad's starting position
        q.append([i, i])
        while q:
            r, p = q.popleft()
            # Check if this is a valid exit (leaf node not equal to 1)
            if r != 0 and p == 0 and len(adj[r]) == 1:
                return True
            for j in adj[r]:
                if v[j] == 0:
                    v[j] = 1
                    q.append([j, p])
        return False

    print("YES" if bfs(0) else "NO")


# https://github.com/VaHiX/CodeForces/