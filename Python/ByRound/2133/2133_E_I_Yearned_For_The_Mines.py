# Problem: CF 2133 E - I Yearned For The Mines
# https://codeforces.com/contest/2133/problem/E

"""
E. I Yearned For The Mines

Purpose:
This code solves the problem of catching a hidden Herobrine in a tree structure by performing a sequence of operations.
The goal is to guarantee that Herobrine is caught within at most floor(5/4 * n) operations, regardless of where he starts or how he moves.

Algorithms/Techniques:
- Tree traversal using BFS (Breadth-First Search) 
- Leaf removal process to reduce the tree to a "core" structure
- Operation-based strategy to ensure Herobrine is caught:
  - Checks (operation 1) to detect if Herobrine is in a node
  - Destructions (operation 2) to remove edges, limiting movement

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm first processes the tree in a bottom-up manner, identifying leaves and assigning colors/flags based on how many neighbors they have.
Then it uses a two-phase DFS-like approach to generate operations:
1. First, checks all nodes that are "in danger" (color 2) by destructions.
2. Then performs regular checks for remaining non-leaf nodes until the whole tree is covered.

"""

t = int(input())
from copy import deepcopy

for _ in range(t):
    n = int(input())
    res = []
    conn = [[] for _ in range(n + 1)]
    deg = [0] * (n + 1)
    color = [[0, 0, 0] for _ in range(n + 1)]  # color[i][j]: number of neighbors of node i with color j
    c = [0 for _ in range(n + 1)]
    vis = [False for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b = map(int, input().split())
        conn[a].append(b)
        conn[b].append(a)
        deg[b] += 1
        deg[a] += 1
    
    deg2 = deepcopy(deg)  # copy of degrees for later modification
    
    # Start with all leaf nodes (degree == 1, except root which is 1 if n > 1)
    stack = [i for i in range(2, n + 1) if deg[i] == 1]
    
    for s in stack:
        vis[s] = True   # mark visited
    
    while stack:
        cur = stack.pop()
        # assign color to current node based on color counts of its neighbors
        if color[cur][0] >= 3 or color[cur][1] >= 1:
            c[cur] = 2
        elif color[cur][0] == 2:
            c[cur] = 1
        else:
            c[cur] = 0

        for nxt in conn[cur]:  # iterate through all neighbors of cur node
            color[nxt][c[cur]] += 1   # update neighbor colors based on this node's color
            deg[nxt] -= 1    # decrease degree as the leaf is removed
            if deg[nxt] == 1 and nxt != 1:   # if neighbor becomes a leaf (not root)
                vis[nxt] = True
                stack.append(nxt)  # push to process
    
    # Handle root node separately
    if color[1][0] >= 3 or color[1][1] >= 1:
        c[1] = 2
    elif color[1][0] == 2:
        c[1] = 1
    else:
        c[1] = 0

    # Apply operation 2 to all nodes that are "color 2" (they're safe paths)
    for i in range(1, n + 1):
        if c[i] == 2:
            res.append([2, i])   # destroy edges of this node
            res.append([1, i])   # check it
            deg2[i] = -1         # mark as processed
            for nxt in conn[i]:  # update degrees of neighbors
                deg2[nxt] -= 1

    # Perform regular checks on remaining nodes (operation 1)
    for i in range(1, n + 1):
        if deg2[i] == -1 or c[i] > 0 or deg2[i] > 1:
            continue   # skip already processed or too connected
        cur = i
        while True:
            f = 0
            res.append([1, cur])   # check current node
            deg2[cur] = -1         # mark as processed
            for nxt in conn[cur]:  # iterate through adjacent nodes
                if deg2[nxt] >= 0:  # if not processed yet
                    cur = nxt       # move to next node
                    f = 1
                    break
            if f == 0:   # no more unvisited neighbors
                break

    print(len(res))
    for a, b in res:
        print(str(a) + " " + str(b))


# https://github.com/VaHiX/codeForces/