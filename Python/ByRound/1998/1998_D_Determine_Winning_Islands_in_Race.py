# Problem: CF 1998 D - Determine Winning Islands in Race
# https://codeforces.com/contest/1998/problem/D

"""
Algorithm: Dynamic Programming with Graph Traversal
Time Complexity: O(n + m) per test case
Space Complexity: O(n + m) per test case

This solution determines for each starting position s (1 <= s <= n-1) whether Bessie can win
the race when she starts on island s. The key insight is to compute the minimum number of
turns required for Elsie to reach each island, assuming optimal play.

The algorithm works as follows:
1. Build a graph of alternative bridges (excluding main bridges)
2. Calculate minimum distance for Elsie to reach each island using BFS-like DP
3. For each starting position, determine whether Bessie can reach island n before Elsie
4. Output a binary string indicating winning positions for Bessie
"""

import sys
from sys import stdin

input = lambda: stdin.readline()[:-1]
results = []


def solve():
    n, m = map(int, input().split())
    adj = [[] for _ in range(n + 1)]
    # Build adjacency list for alternative bridges (excluding main bridges)
    for _ in range(m):
        u, v = map(int, input().split())
        if v != u + 1:  # Skip main bridges (u -> u+1)
            adj[u].append(v)
    
    # time[i] stores minimum turns for Elsie to reach island i
    time = [1000000] * (n + 1)
    # dist[i] stores minimum distance for Elsie to reach island i using main bridges
    dist = [1000000] * (n + 1)
    dist[1] = 0  # Start position is island 1 for Elsie
    
    # Calculate minimum steps for Elsie
    x = n - 1  # Initialize with worst case scenario
    for i in range(1, n):  # Process each island from 1 to n-1
        # For each alternative bridge from island i
        for v in adj[i]:
            dist[v] = min(dist[i] + 1, dist[v])
            # Calculate minimum steps from i to end, adjusted for current island
            x = min(x, dist[i] + 1 + n - v)
        time[i + 1] = x  # Store minimum time needed to reach island i+1
        dist[i + 1] = min(dist[i + 1], dist[i] + 1)  # Update distance for next island
    
    ans = ""
    # Check if Bessie wins at each starting island
    for i in range(1, n):
        if time[i] < n - i:
            ans += "0"  # Elsie reaches island n faster, Bessie loses
        else:
            ans += "1"  # Bessie can reach island n before Elsie, Bessie wins
    results.append("".join(ans))


for __ in range(int(input())):
    solve()
sys.stdout.write("\n".join(results) + "\n")


# https://github.com/VaHiX/CodeForces/