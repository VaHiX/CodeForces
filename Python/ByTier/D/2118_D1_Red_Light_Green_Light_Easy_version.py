# Problem: CF 2118 D1 - Red Light, Green Light (Easy version)
# https://codeforces.com/contest/2118/problem/D1

"""
D1. Red Light, Green Light (Easy version)

Purpose:
This code determines whether a person starting at various positions on a strip will eventually leave the strip within 10^100 seconds. The movement is governed by traffic lights that turn red at specific times based on their position and delay.

Algorithms/Techniques:
- Simulation with precomputed transitions between traffic lights
- Modular arithmetic to determine red/green light states
- Graph traversal (forward/backward) to check escape paths

Time Complexity: O(n^2 + q * n) per test case
Space Complexity: O(n^2 + q) per test case

The solution precomputes which lights can be reached from each other in forward and backward directions based on the condition:
(d[j] - d[i] + p[j] - p[i]) % k == 0 for moving backward (from j to i)
(d[j] - d[i] - p[j] + p[i]) % k == 0 for moving forward (from i to j)

For each query, it checks if current position leads to an escape path by simulating movement through the graph of lights.
"""

for t in range(int(input())):
    n, k = map(int, input().split())
    p = list(map(int, input().split()))
    d = list(map(int, input().split()))
    e = [[-1, -1] for i in range(n)]
    # Precompute transitions between lights
    for i in range(n):
        # Find previous light that can lead to current light (backward movement)
        for j in range(i - 1, -1, -1):
            if (d[j] - d[i] + p[j] - p[i]) % k == 0:
                e[i][0] = j
                break
        # Find next light that can be reached from current light (forward movement)
        for j in range(i + 1, n):
            if (d[j] - d[i] - p[j] + p[i]) % k == 0:
                e[i][1] = j
                break
    q1 = int(input())
    q = list(map(int, input().split()))
    # Process each query
    for i in range(len(q)):
        te = -1
        # Find traffic light at the starting position (or closest one)
        for j in range(n):
            if p[j] >= q[i] and (p[j] - q[i]) % k == d[j]:
                te = j
                break
        # If no suitable traffic light found at start, person will escape
        if te == -1:
            print("YES")
        else:
            tr = 1  # Direction flag: 0 for backward, 1 for forward
            cur = e[te][0]  # Start moving toward previous light
            fl = 0  # Flag to indicate failure condition (no valid path found)
            cov = 1  # Counter for traversal steps
            # Simulate movement in the graph of lights
            while cov < (2 * n + 1) and cur != te or tr == 1:
                nx = e[cur][tr]  # Get next node based on direction
                if nx == -1:  # No next node available
                    fl = 1
                    break
                else:
                    cur = nx
                    tr = (tr + 1) % 2  # Alternate direction
                    cov += 1
            # If path exists that leads to leaving the strip
            if fl == 1:
                print("YES")
            else:
                print("NO")


# https://github.com/VaHiX/codeForces/