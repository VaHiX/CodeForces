# Problem: CF 1704 E - Count Seconds
# https://codeforces.com/contest/1704/problem/E

"""
Problem: Count Seconds
Algorithm: Simulation with Graph Traversal
Time Complexity: O(n * (n + m)) where n is number of nodes and m is number of edges
Space Complexity: O(n + m) for storing graph and auxiliary arrays

This solution simulates the process described in the problem:
1. For each second, we find all nodes with positive values (S)
2. For each node in S:
   - Decrement its value by 1
   - Distribute 1 to all its neighbors
3. We track when all values become 0
4. Special handling for the node with no outgoing edges to ensure correct simulation

The simulation uses a simplified approach where each step updates the array based on the current state.
"""

T = int(input())
while T:
    T -= 1
    n, m = list(map(int, input().split()))
    arr = list(map(int, input().split()))
    g = [[] for _ in range(n)]
    deg = [0] * n
    out = [0] * n
    for _ in range(m):
        x, y = list(map(int, input().split()))
        x -= 1
        y -= 1
        g[x].append(y)
        deg[y] += 1
        out[x] += 1

    index = -1
    for i in range(n):
        if out[i] == 0:
            index = i
            break

    t = 0
    for _ in range(n): # At most n steps needed
        if not any(arr): # If all values are 0
            break
        t += 1
        nxt = [0] * n
        for x in range(n):
            for y in g[x]: # For each neighbor of x
                nxt[y] += arr[x] # Add value from x to y
        nxt[index] += max(0, arr[index] - 1) # Handle the special node
        arr = nxt

    print((t + arr[index]) % 998244353)


# https://github.com/VaHiX/CodeForces/