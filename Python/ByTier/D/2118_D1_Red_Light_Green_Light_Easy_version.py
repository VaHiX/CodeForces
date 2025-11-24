# Problem: CF 2118 D1 - Red Light, Green Light (Easy version)
# https://codeforces.com/contest/2118/problem/D1

"""
Problem: Red Light, Green Light (Easy version)

This problem models a strip with traffic lights that toggle between red and green based on periodic patterns.
Each traffic light has a delay 'd' and a period 'k'. The light is red at times l*k + d for integer l >= 0.
We simulate movement starting from given positions, turning around upon hitting a red light.

Techniques:
- Preprocessing: For each light, precompute the nearest previous and next light satisfying certain modular conditions.
- Simulation: For each query position, attempt to trace whether movement is unbounded or bounded.

Time Complexity: O(n^2 + q*n) per test case
Space Complexity: O(n^2) for storing adjacency relationships

Algorithm:
1. Preprocess each light's nearest previous/next valid light satisfying modular property.
2. For each query position:
   a. Find the first valid light with correct phase matching.
   b. Simulate movement using precomputed links to check if loop occurs or movement escapes.

"""

for t in range(int(input())):
    n, k = map(int, input().split())
    p = list(map(int, input().split()))
    d = list(map(int, input().split()))
    e = [[-1, -1] for i in range(n)]
    
    # Preprocessing step: For each light, compute nearest previous and next lights satisfying condition
    for i in range(n):
        # Find previous light where (d[j] - d[i] + p[j] - p[i]) % k == 0
        for j in range(i - 1, -1, -1):
            if (d[j] - d[i] + p[j] - p[i]) % k == 0:
                e[i][0] = j
                break
        # Find next light where (d[j] - d[i] - p[j] + p[i]) % k == 0
        for j in range(i + 1, n):
            if (d[j] - d[i] - p[j] + p[i]) % k == 0:
                e[i][1] = j
                break
    
    q1 = int(input())
    q = list(map(int, input().split()))
    
    # Process each query position
    for i in range(len(q)):
        te = -1  # Index of matching light with correct initial conditions
        # Find first light whose p[j] >= q[i] and (p[j] - q[i]) % k == d[j]
        for j in range(n):
            if p[j] >= q[i] and (p[j] - q[i]) % k == d[j]:
                te = j
                break
        
        # If no such light exists, the person can escape to infinity -> YES
        if te == -1:
            print("YES")
        else:
            tr = 1  # Track direction: 0 means previous link, 1 means next link
            cur = e[te][0]  # Start from the previous link of the matching light
            fl = 0  # Flag to indicate breaking condition
            cov = 1  # Counter for number of steps taken
            # Simulate movement using links until either:
            # - we exceed a limit (to prevent infinite loops)
            # - or we hit a dead end (-1)
            while cov < (2 * n + 1) and cur != te or tr == 1:
                nx = e[cur][tr]  # Next node in current direction
                
                if nx == -1:  # Dead end reached
                    fl = 1
                    break
                else:
                    cur = nx
                    tr = (tr + 1) % 2  # Toggle between previous/next links
                    cov += 1
            
            # If we hit dead end, means we're stuck -> YES (escape)
            if fl == 1:
                print("YES")
            else:
                print("NO")  # Else looped around without escaping -> NO


# https://github.com/VaHiX/CodeForces/