# Problem: CF 1499 G - Graph Coloring
# https://codeforces.com/contest/1499/problem/G

"""
Algorithm: Online Graph Edge Coloring using Blossom Algorithm
Time Complexity: O(n * m) amortized for all operations, where n is number of vertices and m is number of edges
Space Complexity: O(n + m) for storing graph and auxiliary data structures

This code solves the problem of online edge coloring in bipartite graphs to minimize 
sum of absolute differences between red and blue edges incident to each vertex.
The solution uses a modified blossom algorithm approach for maintaining even cycles 
and efficiently updating the coloring when new edges are added.
"""

import os
import sys
from collections import deque

input = sys.stdin.buffer.readline


def f(u, v):
    # Helper function to encode edge information in a compact form
    return u << 20 ^ v


n1, n2, m = map(int, input().split())
n = n1 + n2
mod = 998244353
# Initialize adjacency list for the graph
G = [set() for _ in range(n + 1)]
for i in range(1, m + 1):
    x, y = map(int, input().split())
    y += n1  # Adjust y to represent second part vertices
    G[x].add(f(y, i))  # Add edge from x to y with index i
    G[y].add(f(x, i))  # Add edge from y to x with index i

q = int(input())
# Precompute powers of 2 modulo 998244353
pow2 = [1] * (m + q + 5)
for i in range(1, m + q + 5):
    pow2[i] = 2 * pow2[i - 1] % mod

ans = 0  # Hash of current optimal coloring
r0 = []  # List of red edges (indices) in the coloring
u = [0] * (n + 1)  # Union-find like array to track components
q1 = [deque()]  # List of queues representing even cycles

# First pass: process initial edges to initialize components
for s in range(1, n + 1):
    q0 = [s]
    if len(G[s]) & 1:  # If vertex degree is odd
        q0 = [s]
        while G[q0[-1]]:
            i = q0[-1]
            x = G[i].pop()
            j, k = x >> 20, x & 0xFFFFF  # Extract endpoint and edge index
            G[j].remove(f(i, k))  # Remove the reverse edge
            if not len(q0) & 2:  # Even length: add to left
                q0.append(k)
            else:  # Odd length: add to right
                q0.append(-k)
            q0.append(j)  # Add endpoint to path
        if q0[0] == q0[-1]:  # Check if cycle is closed
            for i in range(1, len(q0), 4):
                j = q0[i]
                ans += pow2[j]
                r0.append(j)
        else:  # Not a cycle, just a path
            for i in range(1, len(q0), 4):
                ans += pow2[q0[i]]
            u[s], u[q0[-1]] = len(q1), len(q1)
            q1.append(deque(q0))
# Second pass: handle remaining edges
for s in range(1, n + 1):
    q0 = [s]
    while G[s]:
        i = q0[-1]
        x = G[i].pop()
        j, k = x >> 20, x & 0xFFFFF
        G[j].remove(f(i, k))
        if len(q0) & 1:  # If odd length path
            ans += pow2[k]
            r0.append(k)
        q0.append(j)  # Continue building path

# Process all queries
for _ in range(q):
    t = list(map(int, input().split()))
    if t[0] == 1:  # Add new edge
        x, y = t[1], t[2] + n1  # Extract nodes and adjust y
        m += 1  # Increment edge index
        # Handle addition of new edge to existing components/paths
        if not max(u[x], u[y]):  # Both components are new
            ans += pow2[m]
            u[x], u[y] = len(q1), len(q1)
            q1.append(deque([x, m, y]))
        elif not min(u[x], u[y]):  # One is a new component
            if not u[x]:
                x, y = y, x  # Swap to make sure x is in component
            q0 = q1[u[x]]
            u[x], u[y] = 0, u[x]
            if q0[0] == x:  # Path starts with x
                if q0[1] < 0:  # Second element is a negative index (blue edge)
                    ans += pow2[m]
                    q0.appendleft(m)
                else:  # Second element is positive (red edge)
                    q0.appendleft(-m)
                q0.appendleft(y)
            else:  # Path ends with x
                if q0[-2] < 0:  # Second to last is blue edge
                    ans += pow2[m]
                    q0.append(m)
                else:  # Second to last is red edge
                    q0.append(-m)
                q0.append(y)
        elif u[x] == u[y]:  # Same component
            q0 = q1[u[x]]
            u[x] = u[y] = 0
            if q0[1] < 0:  # If second element is blue
                ans += pow2[m]
                r0.append(m)
            # Remove last two elements and update
            q0.pop()
            while q0:
                if q0[-1] > 0:
                    r0.append(q0[-1])
                q0.pop()
                q0.pop()
        else:  # Different components
            # Merge smaller component into larger one
            if len(q1[u[x]]) < len(q1[u[y]]):
                x, y = y, x
            qx, qy, d = q1[u[x]], q1[u[y]], -1
            # Update mapping of nodes to new component
            u[y ^ qy[0] ^ qy[-1]] = u[x ^ qx[0] ^ qx[-1]]
            u[x] = u[y] = 0
            # Connect components through new edge
            if qx[0] == x:
                if qx[1] < 0:
                    ans += pow2[m]
                    d = 1
                    qx.appendleft(m)
                else:
                    qx.appendleft(-m)
                qx.appendleft(y)
                if qy[0] == y:
                    qy.popleft()
                    if qy[0] * d > 0:
                        while qy:
                            v = qy[0]
                            ans += -pow2[v] if v > 0 else pow2[-v]
                            qx.appendleft(-qy.popleft())
                            qx.appendleft(qy.popleft())
                    else:
                        while qy:
                            qx.appendleft(qy.popleft())
                else:
                    qy.pop()
                    if qy[-1] * d > 0:
                        while qy:
                            v = qy[-1]
                            ans += -pow2[v] if v > 0 else pow2[-v]
                            qx.appendleft(-qy.pop())
                            qx.appendleft(qy.pop())
                    else:
                        while qy:
                            qx.appendleft(qy.pop())
            else:
                if qx[-2] < 0:
                    ans += pow2[m]
                    d = 1
                    qx.append(m)
                else:
                    qx.append(-m)
                qx.append(y)
                if qy[0] == y:
                    qy.popleft()
                    if qy[0] * d > 0:
                        while qy:
                            v = qy[0]
                            ans += -pow2[v] if v > 0 else pow2[-v]
                            qx.append(-qy.popleft())
                            qx.append(qy.popleft())
                    else:
                        while qy:
                            qx.append(qy.popleft())
                else:
                    qy.pop()
                    if qy[-1] * d > 0:
                        while qy:
                            v = qy[-1]
                            ans += -pow2[v] if v > 0 else pow2[-v]
                            qx.append(-qy.pop())
                            qx.append(qy.pop())
                    else:
                        while qy:
                            qx.append(qy.pop())
        ans %= mod  # Keep answer within bounds
        os.write(1, b"%d\n" % ans)  # Output current hash value
    else:  # Print optimal coloring for current graph
        r = list(r0)
        # Append all edges in components to final list
        for q0 in q1:
            x = 0
            for i in q0:
                if x and i > 0:
                    r.append(i)
                x ^= 1
        k = len(r)
        os.write(1, b"%d %s\n" % (k, " ".join(map(str, r)).encode()))


# https://github.com/VaHiX/CodeForces/