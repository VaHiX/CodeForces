# Problem: CF 1936 C - Pokémon Arena
# https://codeforces.com/contest/1936/problem/C

"""
Algorithm: Dijkstra's with modified graph
Time Complexity: O((n*m + n*m*log(n*m)) = O(n*m*log(n*m))
Space Complexity: O(n*m)

This problem can be solved using a modified Dijkstra's algorithm on a graph where:
- Each Pokémon has m nodes in the graph, one for each attribute
- We build a graph with 2*n*m nodes: 
  - First n*m nodes represent current state of Pokémon attributes
  - Next n*m nodes represent the "target" state where the attribute is increased
- Edges connect:
  - Cost to increase attributes (k cost for k increase)
  - Duel edges (cost = hire cost, win condition a[i][j] >= current a[j])
- Nodes are connected with costs representing minimum increase needed to win
- We run Dijkstra from node 0 (initial state of 1st Pokémon) to node (n-1)*n (state of nth Pokémon)
"""

import heapq
import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def main(t):

    m, n = map(int, input().split()) # m attributes, n pokemons
    cost = list(map(int, input().split()))
    data = []
    for _ in range(m):
        data.append(list(map(int, input().split())))

    tot = m * n # total number of attribute nodes per pokemon

    # Initialize adjacency list for the graph
    neigh = [[] for _ in range(2 * tot)] # 2 * tot nodes: current state and target state

    # Connect each node with its "target" node (for attribute increase)
    for index in range(m * n):
        i = index // n  # pokemon index
        j = index % n   # attribute index
        # Connect current node to target node (increase cost = cost of pokemon)
        neigh[index].append((index + tot, cost[i]))
        # Connect target node back to current node (no cost)
        neigh[index + tot].append((index, 0))
        # Connect to next attribute in same pokemon (no cost)
        if j != n - 1:
            neigh[index].append((index + 1, 0))
            neigh[index + 1].append((index, 0))

    # For each attribute j, process all pokemons
    for j in range(n):
        temp = []
        for i in range(m):
            temp.append((data[i][j], i)) # (attribute_value, pokemon_index)
        temp.sort()
        # Connect adjacent pokemons by attribute j (smaller to larger)
        for i in range(m - 1):
            index = temp[i][1] * n + j + tot # target node of pokemon with lower value
            nextindex = temp[i + 1][1] * n + j + tot # target node of pokemon with higher value
            # Edge cost is the difference in attribute values needed to increase from lower to higher
            neigh[index].append((nextindex, temp[i + 1][0] - temp[i][0]))
            neigh[nextindex].append((index, 0)) # reverse edge, no additional cost

    # Dijkstra to find minimum cost
    distance = [float("inf")] * (2 * tot) # minimum distances to each node
    heap = []
    heapq.heappush(heap, (0, (m - 1) * n)) # start from last pokemon's first node
    while heap:
        ele = heapq.heappop(heap)
        (d, index) = ele
        # Skip if already processed with smaller distance
        if distance[index] <= d:
            continue
        distance[index] = d
        # Explore neighbors
        for nextindex, nextd in neigh[index]:
            if distance[nextindex] <= d + nextd:
                continue
            heapq.heappush(heap, (d + nextd, nextindex))

    ans = distance[0] # minimum cost to reach final state
    print(ans)


T = int(input())
t = 1
while t <= T:
    main(t)
    t += 1


# https://github.com/VaHiX/CodeForces/