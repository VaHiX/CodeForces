# Problem: CF 1876 C - Autosynthesis
# https://codeforces.com/contest/1876/problem/C

"""
Algorithm: 
This code attempts to solve a problem involving coloring nodes in a directed graph to make a sequence of uncircled elements equal to the sequence of operations performed. The approach is based on:
1. Topological sorting to find nodes that can be processed without cycles
2. For remaining unprocessed nodes, perform a BFS to color them in alternating fashion
3. Validate if coloring is valid and generate the output sequence

Time Complexity: O(n) - Linear time traversal of nodes and edges.
Space Complexity: O(n) - Extra space for adjacency list, in-degree tracking, and color tracking.
"""

import sys
from os import path
from collections import deque

if path.exists("Input.txt"):
    sys.stdin = open("Input.txt", "r")
    sys.stdout = open("Output.txt", "w")

input = sys.stdin.buffer.readline
print = sys.stdout.write

from collections import *
from random import randint

class mydict:
    def __init__(self, func=lambda: 0):
        self.random = randint(0, 1 << 32)
        self.default = func
        self.dict = {}

    def __getitem__(self, key):
        mykey = self.random ^ key
        if mykey not in self.dict:
            self.dict[mykey] = self.default()
        return self.dict[mykey]

    def get(self, key, default):
        mykey = self.random ^ key
        if mykey not in self.dict:
            return default
        return self.dict[mykey]

    def __setitem__(self, key, item):
        mykey = self.random ^ key
        self.dict[mykey] = item

    def getkeys(self):
        return [self.random ^ i for i in self.dict]

    def __str__(self):
        return f"{[(self .random ^i ,self .dict [i ])for i in self .dict ]}"

def solve():
    color = [0] * n
    q = deque()
    exitt = [0] * n
    for i in range(n):
        if not inn[i]:
            q.append(i)
            exitt[i] = 1
            color[i] = 1
    while q:
        for i in range(len(q)):
            node = q.popleft()
            for nbr in adj[node]:
                if not exitt[nbr]:
                    inn[nbr] -= 1
                    color[nbr] |= color[node]
                    if inn[nbr] == 0 or color[nbr]:
                        q.append(nbr)
                        exitt[nbr] = 1
                        color[nbr] ^= 1
    for i in range(n):
        if exitt[i]:
            continue
        q = deque()
        q.append(i)
        start = 0
        cnt = 0
        while q:
            cnt += 1
            node = q.popleft()
            color[node] = start
            exitt[node] = 1
            for nbr in adj[node]:
                if not exitt[nbr]:
                    q.append(nbr)
            start ^= 1
        if cnt & 1:
            print("-1\n")
            return
    b = []
    for i in range(n):
        val = a[i]
        if color[i]:
            b.append(val)
            if color[val]:
                print("-1\n")
                return
    for i in range(len(b)):
        b[i] += 1
    print(str(len(b)) + "\n")
    print(" ".join(map(str, b)) + "\n")

for _ in range(1):
    n = int(input())
    a = [int(x) - 1 for x in input().split()]
    adj = [[] for i in range(n)]
    inn = [0] * n
    for i in range(n):
        adj[i].append(a[i])
        inn[a[i]] += 1
    solve()


# https://github.com/VaHiX/CodeForces/