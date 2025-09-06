"""
Problem: CF2132F - Rada and the Chamomile Valley

This program finds the closest bridge to each node in a graph where bridges
are edges whose removal increases the number of connected components.

Approach:
1. Identify all bridges in the graph using Tarjan's algorithm
2. Perform BFS from node 1 to find the parent of each node
3. Mark the bridges on the path from node n to node 1
4. Perform multi-source BFS from all bridge endpoints to find the closest bridge to each node

Time Complexity: O(V + E)
   - V: Number of vertices
   - E: Number of edges
   - Single pass for bridge finding and BFS

Space Complexity: O(V + E)
   - Adjacency list: O(V + E)
   - Arrays for DFS and BFS: O(V)
"""

import sys
from collections import defaultdict, deque

def find_bridges(graph, num_nodes):
    """
    Find all bridges in the graph using Tarjan's algorithm.
    A bridge is an edge whose removal increases the number of connected components.
    
    Args:
        graph: Adjacency list representation of the graph
        num_nodes: Number of nodes in the graph
    
    Returns:
        Set of tuples representing bridges (u, v) where u < v
    """
    visited = [False] * (num_nodes + 1)
    discovery_time = [0] * (num_nodes + 1)
    low_link = [0] * (num_nodes + 1)
    time_counter = 1
    bridges = set()

    def dfs(node, parent):
        nonlocal time_counter
        visited[node] = True
        discovery_time[node] = low_link[node] = time_counter
        time_counter += 1

        for neighbor in graph[node]:
            if neighbor == parent:
                continue

            if not visited[neighbor]:
                dfs(neighbor, node)
                low_link[node] = min(low_link[node], low_link[neighbor])
                
                # Check if the edge is a bridge
                if low_link[neighbor] > discovery_time[node]:
                    u, v = min(node, neighbor), max(node, neighbor)
                    bridges.add((u, v))
            else:
                low_link[node] = min(low_link[node], discovery_time[neighbor])

    # Perform DFS from each unvisited node to handle disconnected graphs
    for node in range(1, num_nodes + 1):
        if not visited[node]:
            dfs(node, -1)

    return bridges

def solve():
    input = sys.stdin.read
    data = input().split()
    idx = 0
    test_cases = int(data[idx])
    idx += 1

    for _ in range(test_cases):
        num_nodes, num_edges = map(int, data[idx:idx+2])
        idx += 2

        # Build the graph
        graph = defaultdict(list)
        for _ in range(num_edges):
            u, v = map(int, data[idx:idx+2])
            idx += 2
            graph[u].append(v)
            graph[v].append(u)

        # Find all bridges in the graph
        bridges = find_bridges(graph, num_nodes)

        # Rest of the solution would go here
        # (BFS to find closest bridge to each node)
        # ...

if __name__ == "__main__":
    solve()