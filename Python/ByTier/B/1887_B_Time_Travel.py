# Problem: CF 1887 B - Time Travel
# https://codeforces.com/contest/1887/problem/B

"""
Purpose: 
    This code solves a time-travel problem in Berland where roads exist at different points in time.
    The goal is to find the minimum number of time travels needed to go from city 1 to city n,
    considering that at each time moment, only one road can be used to move from the current city.

Algorithms/Techniques:
    - Graph traversal using BFS-like approach with time-aware connections
    - Preprocessing roads into adjacency list grouped by time moments
    - Maintaining waiting list of cities reachable at each time moment
    - Simulating time travel with a queue-based logic

Time Complexity: O(n + t + sum(m_i)) where sum(m_i) is the total number of roads across all time moments.
Space Complexity: O(n * t + n) for adjacency list and waiting lists storage.
"""

def sol():
    n, t = map(int, input().split())
    # Build adjacency list d[i] stores (neighbor, time) for city i
    d = [[] for i in range(n)]
    for c in range(t):
        for _ in range(int(input())):
            x, y = map(int, input().split())
            x -= 1  # Convert to 0-indexed
            y -= 1
            d[x].append((y, c))  # Add edge from x to y at time c
            d[y].append((x, c))  # Add edge from y to x at time c (undirected)
    
    input()  # Skip empty line or unused input
    vis = [False] * n  # Track visited cities
    vis[0] = True  # Start at city 1 (0-indexed)
    # wait[a] contains list of cities that can be reached at time moment a
    wait = [[] for i in range(t)]
    # Initially add neighbors of starting node (city 0) to wait list
    for i, j in d[0]:
        wait[j].append(i)
    
    ans = 0  # Count of time travels
    n1 = n - 1  # Target city (0-indexed)
    
    # Process each time travel
    for a in map(int, input().split()):
        ans += 1  # Increment time travel count
        a -= 1  # Convert to 0-indexed time
        q = []  # Queue for newly reachable cities
        
        # Process all cities that can be reached at this time moment
        for ch in wait[a]:
            if ch == n1:  # If reached destination city
                return print(ans)
            if not vis[ch]:  # If not visited yet, mark as visited
                q.append(ch)
                vis[ch] = True
        
        wait[a] = []  # Clear the waiting list for this time
        # Add neighbors of newly visited cities to the appropriate waiting lists
        for c in q:
            for i, j in d[c]:
                if not vis[i]:  # If neighbor is not visited, add to waiting list
                    wait[j].append(i)
    
    print(-1)  # Could not reach destination


sol()


# https://github.com/VaHiX/CodeForces/