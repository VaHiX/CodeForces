# Problem: CF 1913 E - Matrix Problem
# https://codeforces.com/contest/1913/problem/E

"""
Algorithm: Minimum Cost Flow
Time Complexity: O((V+E)^2 * log(V) * F) where V is number of nodes, E is number of edges, F is the flow
Space Complexity: O(V^2) for the adjacency matrix and capacity matrix

This problem involves finding the minimum number of operations to transform a binary matrix 
such that each row and column has exactly the specified number of 1s. It's modeled as a 
minimum cost flow problem where:
- Source connects to each row with capacity equal to required 1s in that row
- Each column connects to sink with capacity equal to required 1s in that column  
- Each cell (i,j) has an edge from row i to column j with capacity 1 and cost 0 if already 1, 1 if 0
- The cost represents the number of operations needed to change a value
- The minimum cost flow gives us the minimum operations required
"""

from __future__ import print_function

import os
import random
import sys
from collections import deque
from io import BytesIO, IOBase
from math import *
from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


def main():
    pass


BUFSIZE = 8192


def lcm(a, b):
    return (a * b) // gcd(a, b)


def ceilDiv(a, b):
    if a % b == 0:
        return a // b
    else:
        return a // b + 1


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


class myDict:
    def __init__(self, func):
        self.RANDOM = random.randint(0, 1 << 32)
        self.default = func
        self.dict = {}

    def items(self):
        return [(i ^ self.RANDOM, j) for i, j in self.dict.items()]

    def __getitem__(self, key):
        myKey = self.RANDOM ^ key
        if myKey not in self.dict:
            self.dict[myKey] = self.default()
        return self.dict[myKey]

    def __setitem__(self, key, item):
        myKey = self.RANDOM ^ key
        self.dict[myKey] = item

    def __iter__(self):
        return iter(i ^ self.RANDOM for i in self.dict)

    def __contains__(self, key):
        return key ^ self.RANDOM in self.dict

    def __repr__(self):
        return repr({i ^ self.RANDOM: j for i, j in self.dict.items()})


class mySet:
    def __init__(self):
        self.random = random.randint(0, 1 << 32)
        self.set = set()

    def add(self, key):
        self.set.add(key ^ self.random)

    def remove(self, key):
        self.set.remove(key ^ self.random)

    def __contains__(self, key):
        return key ^ self.random in self.set

    def __iter__(self):
        return iter(i ^ self.random for i in self.set)

    def __len__(self):
        return len(self.set)

    def __repr__(self):
        s = set()
        for item in self.set:
            s.add(item ^ self.random)
        return repr(s)


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)


input = lambda: sys.stdin.readline().rstrip("\r\n")
mod = 10**9 + 7


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return list(s[: len(s)])


def invr():
    return map(int, input().split())


INF = float("inf")


class Edge:
    def __init__(self, from_, to, capacity, cost):
        self.from_ = from_
        self.to = to
        self.capacity = capacity
        self.cost = cost


# Function to find shortest paths using modified Dijkstra
def shortest_paths(n, v0, d, p):
    # Initialize distances and visited array
    d[v0] = 0
    inq = [False] * n
    q = deque()
    q.append(v0)

    # Process nodes in BFS order
    while q:
        u = q.popleft()
        inq[u] = False
        # Iterate through adjacent edges
        for v in adj[u]:
            # Update if we found a better path
            if capacity[u][v] > 0 and d[v] > d[u] + cost[u][v]:
                d[v] = d[u] + cost[u][v]
                p[v] = u
                # Add to queue if not already in it
                if not inq[v]:
                    inq[v] = True
                    q.append(v)


# Minimum cost flow algorithm
def min_cost_flow(N, edges, K, s, t):
    global adj, capacity, cost, d, p
    # Initialize adjacency list and matrices
    adj = [[] for _ in range(N)]
    cost = [[0] * N for _ in range(N)]
    capacity = [[0] * N for _ in range(N)]

    # Build the graph from edge list
    for e in edges:
        adj[e.from_].append(e.to)
        adj[e.to].append(e.from_)
        cost[e.from_][e.to] = e.cost
        cost[e.to][e.from_] = -e.cost  # Reverse edge has negative cost
        capacity[e.from_][e.to] = e.capacity

    flow = 0
    cst = 0
    d = [float("inf")] * N
    p = [-1] * N

    # Continue until required flow is achieved
    while flow < K:
        d = [INF] * N
        p = [-1] * N
        # Find shortest path
        shortest_paths(n + m + 2, 0, d, p)
        # If no path exists, return -1
        if d[n + m + 1] == INF:
            return -1
            
        # Calculate minimum flow through the path
        f = K - flow
        cur = n + m + 1
        while cur != s:
            f = min(f, capacity[p[cur]][cur])
            cur = p[cur]

        flow += f
        cst += f * d[n + m + 1]
        cur = n + m + 1
        # Update capacities along path
        while cur != s:
            capacity[p[cur]][cur] -= f
            capacity[cur][p[cur]] += f
            cur = p[cur]

    if flow < K:
        return -1
    else:
        return cst


# Read input
n, m = invr()
l = [inlt() for i in range(n)]
a = inlt()
b = inlt()
# Check if solution is possible
if sum(a) != sum(b):
    print(-1)
    exit()
    
edges = []
c = 0  # Count of preexisting 1s

# Add edges from source to row nodes
for i in range(n):
    new_edge = Edge(0, i + 1, a[i], 0)
    edges.append(new_edge)
    
# Add edges from column nodes to sink
for i in range(m):
    new_edge = Edge(n + i + 1, n + m + 1, b[i], 0)
    edges.append(new_edge)

# Add edges for each cell
for i in range(n):
    for j in range(m):
        cst = 0
        if l[i][j] == 0:  # Cell has 0, needs to be changed with cost 1
            cst = 1
            new_edge = Edge(i + 1, n + j + 1, 1, cst)
        else:  # Cell has 1, no cost to keep it
            new_edge = Edge(i + 1, n + j + 1, 1, 0)
            c += 1  # Count existing 1s
        edges.append(new_edge)

# Run minimum cost flow
a = min_cost_flow(n + m + 2, edges, sum(a), 0, n + m + 1)
if a == -1:
    print(-1)
else:
    print(c - sum(b) + a * 2)  # Final result calculation


# https://github.com/VaHiX/CodeForces/