# Problem: CF 1731 E - Graph Cost
# https://codeforces.com/contest/1731/problem/E

"""
Purpose: 
This code solves the problem of constructing a graph with 'n' nodes and 'm' edges,
where each edge has a weight equal to the GCD of its node indices. The goal is to 
minimize the total cost of adding edges, where adding k edges of weight (k+1) costs (k+1).

Algorithm:
1. Precompute how many edges exist for each possible GCD value using inverse inclusion-exclusion principle.
2. Greedily select the largest possible weight edges (from large to small) to minimize cost.

Time Complexity: O(n log n) - Due to iterating over multiples and inverse inclusion-exclusion process.
Space Complexity: O(n) - For storing edge counts per GCD value.
"""

for _ in range(int(input())):
    n, m = map(int, input().split())

    # edges[i] stores number of edges with weight i
    edges = [0] * (n + 1)
    
    # Iterate from largest possible GCD down to 1
    for mult in range(n, 0, -1):
        # Count how many numbers from 1 to n are divisible by 'mult'
        cnts = n // mult

        # Initially assume all pairs have GCD 'mult' 
        edges[mult] = (cnts * (cnts - 1)) // 2

        # Remove overcounted pairs that actually have a larger GCD multiple
        for i in range(mult * 2, n + 1, mult):
            edges[mult] -= edges[i]

    ans = 0

    # Try to use maximum weight edges first to minimize cost
    for x in range(n, 1, -1):
        # Check if we can form at least (x-1) edges with weight x
        # and there are at least (x-1) such edges possible
        if m >= x - 1 and edges[x] >= x - 1:
            # Calculate how many full packages (of size x-1) we can take
            st = min(m // (x - 1), edges[x] // (x - 1))
            ans += st * x         # Add cost of this package
            m -= st * (x - 1)     # Reduce remaining required edges

    # If we couldn't fulfill all 'm' edges, output -1
    if m:
        print(-1)
    else:
        print(ans)


# https://github.com/VaHiX/CodeForces/