# Problem: CF 2098 D - Baggage Claim
# https://codeforces.com/contest/2098/problem/D

"""
D. Baggage Claim
Algorithms/Techniques: Union-Find (Disjoint Set Union), Graph Theory, Path Reconstruction

Time Complexity: O(n * m * α(n * m)) where α is the inverse Ackermann function (n * m = total grid cells)
Space Complexity: O(n * m)

Approach:
- The problem reduces to reconstructing a path through a grid such that every two consecutive points are adjacent.
- Odd-indexed points are given, even-indexed points need to be inserted.
- The path must be simple — no repeated cells.
- For each component (connected group of cells), we determine valid ways to fill in the missing edges.
- Use Union-Find to track connected components and count how many choices there are for completing each segment.
"""

import sys

input = sys.stdin.readline
MOD = int(1e9 + 7)
for _ in range(int(input())):
    n, m, k = map(int, input().split())
    size = n * m
    pa = list(range(size))  # Union-Find parent array
    sz = [1] * size         # Size of each component
    need = [0] * size       # Number of edges needed in each component
    cnt = [0] * size        # Count of occurrences of each cell (to check uniqueness)
    fixed = [False] * size  # Whether a component's structure is fully determined

    def find(x):
        while pa[x] != x:
            pa[x] = pa[pa[x]]   # Path compression
            x = pa[x]
        return x

    def merge(u, v):
        u, v = find(u), find(v)
        if u != v:
            pa[v] = u           # Union two components
            sz[u] += sz[v]
            need[u] += need[v]
        need[u] += 1            # One more edge needed to connect them

    def id(x, y):
        return (x - 1) * m + (y - 1)  # Convert 2D coordinates to 1D index

    p = []
    ok = True
    # Read all k+1 odd-indexed points and check for duplicates
    for _ in range(k + 1):
        x, y = map(int, input().split())
        p.append((x, y))
        cid = id(x, y)
        cnt[cid] += 1
        if cnt[cid] > 1:
            ok = False
    if not ok:
        print(0)
        continue

    # Check that consecutive points are exactly two steps apart (L-shaped or straight) 
    for i in range(k):
        x1, y1 = p[i]
        x2, y2 = p[i + 1]
        if abs(x1 - x2) + abs(y1 - y2) != 2:
            print(0)
            break
    else:
        # For each pair of consecutive odd indices, insert even-indexed point(s)
        for i in range(k):
            x1, y1 = p[i]
            x2, y2 = p[i + 1]
            if abs(x1 - x2) == 2 or abs(y1 - y2) == 2:  # L-shaped segment
                u = id((x1 + x2) // 2, (y1 + y2) // 2)
                u = find(u)
                need[u] += 1       # This middle position is necessary
                fixed[u] = True    # Structure of this component is fixed
            else:                  # Straight segment
                u = id(x1, y2)
                v = id(x2, y1)
                merge(u, v)          # Join components using these two adjacent cells

        ans = 1
        vis = [False] * size     # Visited component tracking
        
        # Mark all root nodes as fixed if they have fixed structure
        for i in range(size):
            if fixed[i]:
                p_root = find(i)
                fixed[p_root] = True

        # Process components to compute number of valid completions
        for i in range(size):
            p_root = find(i)
            if vis[p_root]:      # Already processed
                continue
            vis[p_root] = True   # Mark component as processed
            
            # Validate whether the structure allows a valid completion
            if need[p_root] > sz[p_root] or need[p_root] < sz[p_root] - 1:
                ans = 0      # Invalid configuration
                break
            elif need[p_root] == sz[p_root] - 1:
                ans = ans * sz[p_root] % MOD    # One choice to extend path
            elif not fixed[p_root]:
                ans = ans * 2 % MOD             # Two independent choices in this component

        print(ans)


# https://github.com/VaHiX/codeForces/