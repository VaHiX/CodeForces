# Problem: CF 1938 B - Attraction Score
# https://codeforces.com/contest/1938/problem/B

"""
Algorithm: Maximum Attraction Score
Approach: 
This solution uses a greedy approach combined with dynamic programming techniques to find the maximum attraction score.
The algorithm processes nodes in a specific order (based on degree), and for each node, it examines:
1. All pairs of neighbors connected to the current node (for 2-cliques)
2. All triplets of neighbors (for 3-cliques)
3. All quadruplets of neighbors (for 4-cliques)

Key insight: 
- Nodes with degree <= 5 are processed in a queue for optimization
- For each processed node, the algorithm evaluates potential maximum scores through different combinations of its neighbors
- A penalty term is computed for each subset with disconnected pairs of cities
- Memoization is used to store and reuse computed scores for combinations of cities (SZ2 for pairs, SZ3 for triplets)

Time Complexity: O(N * D^4) where N is number of nodes and D is max degree (bounded by 5 in the queue processing)
Space Complexity: O(N * D^2) for storing adjacency lists and memoization tables

Note: The queue-based processing and degree constraint are key optimizations that make this feasible for the given constraints.
"""

import sys
from collections import deque
from itertools import combinations

input = sys.stdin.readline
F = lambda: [*map(int, input().split())]
penalty = 10**6


def rmv(x):
    # Remove node x from adjacency lists of its neighbors
    for y in ADJ:
        G[y].pop(x)
        # Add neighbor to queue if degree drops to 5 or less
        if VIS[y] == 0 and len(G[y]) <= 5:
            Q.append(y)
            VIS[y] = 1


N, M = F()
# Read coordinates (but not used in solution - only for input parsing)
for _ in range(N):
    input()
# Initialize adjacency list
G = [{} for _ in range(N)]
# Read edges
for _ in range(M):
    a, b, v = F()
    a -= 1  # Convert to 0-indexed
    b -= 1
    G[a][b] = v  # Store edge weight
    G[b][a] = v  # Edge is undirected

# Queue for processing nodes with small degree
Q = deque()
SZ2 = {}  # Memoization for pairs of cities
SZ3 = {}  # Memoization for triplets of cities

VIS = [0] * N
# Add all nodes with degree <= 5 to queue for processing
for i in range(N):
    if len(G[i]) <= 5:
        Q.append(i)
        VIS[i] = 1
ans = 0  # Maximum attraction score found
while Q:
    x = Q.popleft()  # Get next node to process
    l = len(G[x])  # Degree of current node
    if l == 0:  # Skip isolated nodes
        continue
    ADJ = []
    # Build list of adjacent nodes
    for y in G[x]:
        ADJ.append(y)
        # Consider single highway as potential score
        ans = max(ans, G[x][y])

    if l == 1:  # If node is connected to only 1 other, remove it
        rmv(x)
        continue

    # Process pairs of neighbors of the current node
    for a, b in combinations(ADJ, 2):
        if b not in G[a]:  # Skip if no direct connection between neighbors
            continue
        # Compute score for this triangle
        s = G[x][a] + G[x][b] + G[a][b]
        ans = max(ans, s)

        # Update memoization tables for pairs
        K = sorted([a, b, x])
        for i in range(2):
            for j in range(i + 1, 3):
                aa, bb = K[i], K[j]
                if (aa, bb) in SZ2:
                    ans = max(ans, SZ2[(aa, bb)] + s)
                    SZ2[(aa, bb)] = max(SZ2[(aa, bb)], s - G[aa][bb] - penalty)
                else:
                    SZ2[(aa, bb)] = s - G[aa][bb] - penalty
    if l == 2:  # If node has degree 2, remove it
        rmv(x)
        continue

    # Process triplets of neighbors of the current node
    for a, b, c in combinations(ADJ, 3):
        cnt = 0  # Count of disconnected pairs
        s = G[x][a] + G[x][b] + G[x][c]
        # Update score with edges connecting x to neighbors
        if b in G[a]:
            s += G[a][b]
        else:
            cnt += 1
            s -= penalty
        if c in G[a]:
            s += G[a][c]
        else:
            cnt += 1
            s -= penalty
        if c in G[b]:
            s += G[b][c]
        else:
            cnt += 1
            s -= penalty
        ans = max(ans, s)
        if cnt > 0:  # Skip if more than 1 disconnected pair (too expensive)
            continue

        # Update memoization for triplets
        K = sorted([a, b, c, x])
        aa, bb, cc, dd = K[0], K[1], K[2], K[3]
        if (aa, bb, cc) in SZ3:
            ans = max(ans, SZ3[(aa, bb, cc)] + s)
            SZ3[(aa, bb, cc)] = max(
                SZ3[(aa, bb, cc)], G[dd][aa] + G[dd][bb] + G[dd][cc] - penalty
            )
        else:
            SZ3[(aa, bb, cc)] = G[dd][aa] + G[dd][bb] + G[dd][cc] - penalty

        # Try all permutations of the triplet to ensure all combinations are covered
        aa, bb, cc, dd = K[0], K[1], K[3], K[2]
        if (aa, bb, cc) in SZ3:
            ans = max(ans, SZ3[(aa, bb, cc)] + s)
            SZ3[(aa, bb, cc)] = max(
                SZ3[(aa, bb, cc)], G[dd][aa] + G[dd][bb] + G[dd][cc] - penalty
            )
        else:
            SZ3[(aa, bb, cc)] = G[dd][aa] + G[dd][bb] + G[dd][cc] - penalty

        aa, bb, cc, dd = K[0], K[2], K[3], K[1]
        if (aa, bb, cc) in SZ3:
            ans = max(ans, SZ3[(aa, bb, cc)] + s)
            SZ3[(aa, bb, cc)] = max(
                SZ3[(aa, bb, cc)], G[dd][aa] + G[dd][bb] + G[dd][cc] - penalty
            )
        else:
            SZ3[(aa, bb, cc)] = G[dd][aa] + G[dd][bb] + G[dd][cc] - penalty

        aa, bb, cc, dd = K[1], K[2], K[3], K[0]
        if (aa, bb, cc) in SZ3:
            ans = max(ans, SZ3[(aa, bb, cc)] + s)
            SZ3[(aa, bb, cc)] = max(
                SZ3[(aa, bb, cc)], G[dd][aa] + G[dd][bb] + G[dd][cc] - penalty
            )
        else:
            SZ3[(aa, bb, cc)] = G[dd][aa] + G[dd][bb] + G[dd][cc] - penalty
    
    if l == 3:  # If node has degree 3, remove it
        rmv(x)
        continue

    # Process quadruplets of neighbors of the current node
    for a, b, c, d in combinations(ADJ, 4):
        cnt = 0
        s = G[x][a] + G[x][b] + G[x][c] + G[x][d]
        # Update score with edges connecting x to neighbors
        if b in G[a]:
            s += G[a][b]
        else:
            cnt += 1
            s -= penalty
        if c in G[a]:
            s += G[a][c]
        else:
            cnt += 1
            s -= penalty
        if d in G[a]:
            s += G[a][d]
        else:
            cnt += 1
            s -= penalty
        if c in G[b]:
            s += G[b][c]
        else:
            cnt += 1
            s -= penalty
        if d in G[b]:
            s += G[b][d]
        else:
            cnt += 1
            s -= penalty
        if d in G[c]:
            s += G[c][d]
        else:
            cnt += 1
            s -= penalty
        if cnt >= 2:  # Too many disconnected pairs, skip
            continue
        ans = max(ans, s)

    rmv(x)  # Remove processed node

print(ans)  # Output maximum attraction score


# https://github.com/VaHiX/CodeForces/