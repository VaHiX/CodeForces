# Problem: CF 1991 E - Coloring Game
# https://codeforces.com/contest/1991/problem/E

"""
Algorithm: Graph Coloring and Game Theory
Purpose: Determine which player (Alice or Bob) has a winning strategy in a game where they color vertices of a graph.
Technique: 
- Use bipartite checking to determine if the graph can be 2-colored
- If graph is bipartite, Bob can always win by playing optimally
- If graph is not bipartite, Alice can always win by forcing a conflict

Time Complexity: O(n + m) per test case, where n is number of vertices and m is number of edges.
Space Complexity: O(n + m) for storing the adjacency list and color information.

The problem is essentially about determining if a graph has a valid 2-coloring.
If it does, the second player (Bob) can always win.
If it doesn't, the first player (Alice) can always win.
This is because we are dealing with a game where players color vertices,
and a conflict (same color on adjacent vertices) means the first player (Alice) wins.
If the graph is 2-colorable, then one of the two players will always lose if they play optimally.
"""

def bip(g, n, clr):
    # Function to check if graph is bipartite using BFS
    clr[1] = 1  # Start coloring with color 1
    vis = [0] * (n + 1)  # Visited array to track visited nodes
    vis[1] = 1  # Mark starting node as visited
    s = [1]  # Stack for BFS
    
    while s:
        x = s.pop()  # Pop a node from stack
        # Determine the opposite color
        opc = 2 if clr[x] == 1 else 1
        for i in g[x]:  # Check all neighbors
            if vis[i] == 0:  # If neighbor is unvisited
                vis[i] = 1  # Mark as visited
                clr[i] = opc  # Color it with opposite color
                s.append(i)  # Add to stack for further exploration
            elif clr[i] != opc:  # If neighbor is already colored but with different color
                return 0  # Graph is not bipartite
    return 1  # Graph is bipartite


def main():
    # Read number of vertices and edges
    n, m = (int(i) for i in input().split())
    
    # Create adjacency list representation of the graph
    g = [[] for i in range(n + 1)]
    for i in range(m):
        u, v = map(int, input().split())
        g[u].append(v)  # Add edge u-v
        g[v].append(u)  # Add edge v-u (undirected)
    
    # Initialize color array
    clr = [0] * (n + 1)
    
    # Check if graph is bipartite
    if bip(g, n, clr):
        # If bipartite, Bob wins
        print("Bob", flush=True)
        
        # Separate vertices into two groups based on colors
        one = []
        two = []
        x = y = i = j = 0  # x and y are counts, i and j are iterators
        
        # Categorize vertices by their color assignment
        for k in range(1, n + 1):
            if clr[k] == 1:
                x += 1
                one.append(k)
            else:
                y += 1
                two.append(k)
        
        # Distribute vertices to Bob's color choices
        while i < x and j < y:
            z = input()
            if z == "-1":
                break
            a, b = map(int, z.split())
            a = min(a, b)  # Choose smaller color for first player
            if a == 1:
                print(one[i], 1, flush=True)
                i += 1
            else:
                print(two[j], 2, flush=True)
                j += 1
        
        # If first group is exhausted, assign remaining vertices from second group
        if i == x:
            while j < y:
                z = input()
                if z == "-1":
                    break
                a, b = map(int, z.split())
                a = max(a, b)  # Choose larger color
                print(two[j], a, flush=True)
                j += 1
        else:  # If second group is exhausted, assign remaining from first
            while i < x:
                z = input()
                if z == "-1":
                    break
                a, b = map(int, z.split())
                a = min(a, b)
                if a == 2:
                    a = 3
                print(one[i], a, flush=True)
                i += 1
    else:
        # If not bipartite, Alice wins
        print("Alice", flush=True)
        # Alice will always choose colors 1 and 2 for each turn
        for i in range(n):
            print(1, 2, flush=True)
            x = input()
            if x == "-1":
                break


# Read number of test cases and process each one
t = int(input())
while t:
    main()
    t -= 1


# https://github.com/VaHiX/CodeForces/