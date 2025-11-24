# Problem: CF 2029 D - Cool Graph
# https://codeforces.com/contest/2029/problem/D

"""
Code Purpose:
This code solves the "Cool Graph" problem where we need to transform a given undirected graph into either a tree or an empty graph using a specific operation. 
The operation allows choosing three vertices and toggling the existence of edges between them.

Algorithm/Techniques:
- The solution uses a greedy approach combined with bit manipulation (XOR) to manage edge toggling.
- It first processes all edges connecting to vertex 1, and toggles edges to bring vertex 1 into a state where its degree is even.
- Then, it balances the degrees of all vertices using a greedy pairing approach.
- This ensures the final graph can be made into either a tree or an empty graph by adjusting the operations accordingly.

Time Complexity:
O(n + m) per test case, as we iterate through edges once and vertices a constant number of times.

Space Complexity:
O(n) for storing connection states and result operations.
"""

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()
for _ in range(int(input())):
    n, m = map(int, input().split())
    conn = [0] * (n + 1)
    res = []
    for _ in range(m):
        u, v = map(int, input().split())
        if u > v:
            u, v = v, u
        # If the edge is not connected to vertex 1, toggle it
        if u != 1:
            res += ((1, u, v),)
            conn[u] ^= 1
        conn[v] ^= 1
    # Balance the connections for all vertices except 1
    for u in range(2, n + 1):
        if conn[u]:
            for v in range(2, n + 1):
                if not conn[v]:
                    res += ((1, u, v),)
                    u = v
            break
    print(len(res))
    for x in res:
        print(*x)


# https://github.com/VaHiX/CodeForces/