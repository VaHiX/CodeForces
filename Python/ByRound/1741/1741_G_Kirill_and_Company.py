# Problem: CF 1741 G - Kirill and Company
# https://codeforces.com/contest/1741/problem/G

"""
Problem: G. Kirill and Company

Purpose:
This code solves a problem where Kirill and his friends live in a connected undirected graph. 
Some friends have cars and can give rides to friends without cars, but only if they can reach 
them via a shortest path. The goal is to minimize the number of friends without cars who have 
to walk.

Algorithms/Techniques:
- BFS to compute shortest distances from vertex 1 to all other vertices
- Bitmask dynamic programming to track which friends without cars can be picked up by friends with cars
- Set-based optimization to efficiently track possible combinations

Time Complexity: O(n + f * 2^k + 2^k * k) where:
- n is number of vertices, f is number of friends, k is number of friends without cars
- BFS: O(n + m)
- DP: O(f * 2^k) for updating, O(2^k * k) for finding minimum

Space Complexity: O(n + 2^k) for storing distances, variables, masks, and backpack DP array
"""

from collections import deque


def solve():
    # Read graph input
    n, m = map(int, input().split())
    sl = [[] for _ in range(n)]  # adjacency list
    for _ in range(m):
        u, v = map(int, input().split())
        u -= 1  # Convert to 0-indexed
        v -= 1
        sl[u] += [v]
        sl[v] += [u]
    
    # Read friends' homes
    f = int(input())
    h = [int(x) - 1 for x in input().split()]  # Convert to 0-indexed
    
    # Track which friends have cars (using bitmask)
    mask = [0] * n  # mask[v] stores which friends without cars live at vertex v
    k = int(input())
    p = [int(x) - 1 for x in input().split()] + [-1]  # Convert to 0-indexed and add sentinel
    
    # Mark which friends live at each vertex using a bitmask
    j = 0
    for i in range(k):
        # Mark the friend who doesn't have a car at vertex h[p[i]]
        mask[h[p[i]]] += 1 << i  
        
    # Variables to store possible bitmasks for each vertex
    vars = [set() for _ in range(n)]
    
    # Distance array and BFS setup
    dist = [-1] * n
    dist[0] = 0  # Starting vertex
    vars[0].add(mask[0])  # Add initial mask for vertex 0 (where Kirill is)
    q = deque([0])
    
    # BFS to compute distances and possible mask combinations
    while len(q) > 0:
        v = q.popleft()
        for u in sl[v]:  # For each neighbor
            if dist[u] == -1:  # Not visited
                dist[u] = dist[v] + 1
                q.append(u)
            # If this neighbor is at the same distance from source, update its possible masks
            if dist[u] == dist[v] + 1:
                for msk in vars[v]:
                    vars[u].add(msk | mask[u])  # Merge the masks
    
    # DP with bitmask to decide which friends without cars to pick up
    backpack = [False] * (1 << k)  # backpack[msk] = True if we can pick up subset represented by msk
    backpack[0] = True  # Initially we haven't picked anyone
    
    # Process each friend who has a car
    j = 0  # to track current friend without car
    for i in range(f):
        # Skip friends who have cars
        if i == p[j]:
            j += 1
            continue
            
        # New state after considering this friend
        nw = backpack.copy()  # Copy current states
        
        # For each existing combination of friends picked up
        for msk in range(1 << k):
            if not backpack[msk]:  # Already impossible combination
                continue
                
            # For each possible group of friends at friend's home that can be picked up
            for var in vars[h[i]]:  # var is a possible mask at vertex h[i]
                nw[msk | var] = True  # Add var to current mask
        
        # Update backpack to new state
        backpack, nw = nw, backpack  # Swap references
    
    # Find minimum amount of friends without cars who have to walk
    mn = k  # Maximum possible friends without cars
    for msk in range(1 << k):
        if not backpack[msk]:  # Combination not reachable
            continue
            
        # Count number of bits in the mask (i.e., how many friends without cars are left)
        ans = 0
        for b in range(k):
            if msk & (1 << b) == 0:  # This friend wasn't picked up
                ans += 1
        mn = min(mn, ans)  # Minimum friends without cars to walk
    
    print(mn)


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/