# Problem: CF 1794 E - Labeling the Tree with Distances
# https://codeforces.com/contest/1794/problem/E

"""
Algorithm: Tree Distance Labeling Problem
Purpose: Find all "good" vertices in a tree where each vertex can be labeled such that 
         the distance from that vertex to every other vertex matches the given labels.

Approach:
1. Build the tree from input edges.
2. Perform BFS to compute parent relationships.
3. Compute initial information using a hash-like computation (based on tree traversal).
4. Use a second pass to compute final info for each node.
5. Compute possible label sums using a rolling hash technique.
6. Identify vertices whose computed value matches one of the possible label sums.

Time Complexity: O(n)
Space Complexity: O(n)
"""

import sys

input = sys.stdin.buffer.readline

# Precomputed primes for hashing
p1 = 176860696068671
q1 = 181395559296673


def process(n, A, G):
    # Build adjacency list representation of the tree
    g = [[] for i in range(n + 1)]
    for u, v in G:
        g[u].append(v)
        g[v].append(u)
    
    # Initialize parent array to track tree structure
    parent = [None for i in range(n + 1)]
    parent[1] = -1  # Root node has no parent
    
    # BFS to compute parent relationships
    start = [[1]]
    while True:
        next_s = []
        for x in start[-1]:
            for y in g[x]:
                if parent[y] is None:
                    parent[y] = x
                    next_s.append(y)
        if len(next_s) == 0:
            break
        start.append(next_s)
    
    # Compute initial info using hash-based computation
    info = [0 for i in range(n + 1)]
    while len(start) > 0:
        row = start.pop()
        for x in row:
            info[x] = (info[x] + 1) % q1
            y = parent[x]
            if y != -1:
                info[y] = (info[y] + info[x] * p1) % q1
    
    # Compute final info for each node
    final_info = [None for i in range(n + 1)]
    final_info[1] = info[1]
    start = [1]
    while len(start) > 0:
        next_s = []
        for x in start:
            for y in g[x]:
                if final_info[y] is None:
                    final_info[y] = (p1 * (final_info[x] - p1 * info[y]) + info[y]) % q1
                    next_s.append(y)
        start = next_s
    
    # Compute all possible label sums using rolling hash
    entry = 0
    for x in A:
        entry = (entry + pow(p1, x, q1)) % q1
    I = 1
    possible = set([])
    for i in range(n):
        possible.add((I + entry) % q1)
        I = (p1 * I) % q1
    
    # Find all good vertices
    answer = []
    for i in range(1, n + 1):
        if final_info[i] in possible:
            answer.append(i)
    
    # Output results
    m = len(answer)
    answer = " ".join(map(str, answer))
    sys.stdout.write(f"{m }\n")
    sys.stdout.write(f"{answer }\n")
    return


# Read input and process
n = int(input())
A = [int(x) for x in input().split()]
G = []
for i in range(n - 1):
    u, v = [int(x) for x in input().split()]
    G.append([u, v])
process(n, A, G)


# https://github.com/VaHiX/CodeForces/