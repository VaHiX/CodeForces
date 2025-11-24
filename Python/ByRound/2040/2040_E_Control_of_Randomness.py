# Problem: CF 2040 E - Control of Randomness
# https://codeforces.com/contest/2040/problem/E

"""
Algorithm: Tree traversal with dynamic programming
Time Complexity: O(n * q) per test case, where n is the number of nodes and q is the number of queries.
Space Complexity: O(n) for storing the tree and auxiliary arrays.
"""

import sys

input = sys.stdin.readline


def solve():
    n, q = map(int, input().split())
    G = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b = map(int, input().split())
        a -= 1
        b -= 1
        G[a].append(b)
        G[b].append(a)
    P = [-1] * n  # Parent array
    Q = [0]  # BFS queue for tree traversal
    for i in Q:  # Traverse the tree to build parent relationships
        for j in G[i]:
            if P[i] != j:
                Q.append(j)
                P[j] = i
    for _ in range(q):
        idx, p = map(int, input().split())
        idx -= 1  # Convert to 0-based indexing
        switch = 0  # Toggle flag for determining when to collect branch sizes
        l = []  # List to store the number of branches (excluding the parent) at each step
        ans = 0  # Number of steps from current node to root (distance)
        while idx != 0:  # While not at root
            if switch:
                l.append(len(G[idx]) - 1)  # Add the number of children (excluding parent)
            switch ^= 1  # Toggle the flag
            idx = P[idx]  # Move to parent
            ans += 1  # Increment the step count
        l.sort()  # Sort the number of branches in ascending order
        for _ in range(min(len(l), p)):  # Use p coins optimally (remove largest values)
            l.pop()
        print(ans + sum(l) * 2)  # Final expected steps


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/