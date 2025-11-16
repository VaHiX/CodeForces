# Problem: CF 1775 D - Friendly Spiders
# https://codeforces.com/contest/1775/problem/D

"""
Algorithm: 
Graph traversal using BFS with prime factorization preprocessing to find shortest path
between two spiders in a graph where edges exist if gcd of their leg counts > 1.
Time Complexity: O(N * sqrt(max_a) + V + E) where N is number of spiders, V = N, E = number of edges.
Space Complexity: O(N + max_a) for storing lpd array and adjacency info.

The key idea is:
1. Preprocess smallest prime divisor (lpd) for all numbers up to max_a using sieve.
2. For each spider, factorize its leg count and map prime factors to spider indices.
3. BFS traversal: for each node, explore all neighbors reachable via shared prime factors.
4. Reconstruct path using parent pointers from BFS.

This algorithm treats the spider colony as a graph where nodes are spiders and edges exist if gcd > 1.
"""

from collections import deque
from math import gcd
from sys import stdin

input = lambda: stdin.readline().rstrip("\r\n")


n = int(input())
a = list(map(int, input().split()))
s, t = map(int, input().split())

if s == t:
    print(1)
    print(s)
    exit(0)

s -= 1
t -= 1

# Check if direct connection exists
if gcd(a[s], a[t]) > 1:
    print(2)
    print(s + 1, t + 1)
    exit(0)


N = int(3e5) + 1
# lpd[i] stores smallest prime divisor of i
lpd = [0] * N
for i in range(2, N):
    if lpd[i]:
        continue
    for x in range(i, N, i):
        lpd[x] = i

# fac[p] stores list of spider indices that have a leg count divisible by prime p
fac = {}
for i, x in enumerate(a):
    while x > 1:
        p = lpd[x]
        while x % p == 0:
            x //= p
        if p not in fac:
            fac[p] = []
        fac[p].append(i)


def getPrimeFactors(x):
    # Returns list of prime factors of x
    pf = []
    while x > 1:
        p = lpd[x]
        while x % p == 0:
            x //= p
        pf += [p]
    return pf


def BFS(s, t, v, parent):
    # BFS to find shortest path from s to t
    q = deque([s])
    vis = [0] * v        # Visited array for spiders
    seen = [0] * 300001  # Visited array for primes used to avoid reprocessing

    for i in range(v):
        parent[i] = -1   # Initialize parent pointers

    vis[s] = 1

    while q:
        u = q.popleft()           # Current spider index
        x = a[u]                  # Legs of current spider
        for p in getPrimeFactors(x):  # For each prime factor
            if seen[p]:
                continue
            seen[p] = 1

            for i in fac[p]:      # For each spider with this prime factor
                if vis[i]:
                    continue
                vis[i] = 1
                parent[i] = u     # Record parent
                q.append(i)       # Add to queue
                if i == t:
                    return 1      # Found target
    return 0


def solve(s, t, v):
    parent = [0] * v

    if BFS(s, t, v, parent) == 0:
        print(-1)
        return

    path = [t + 1]              # Build path from target to source
    while parent[t] != -1:
        t = parent[t]
        path += [t + 1]

    print(len(path))
    print(*reversed(path))


solve(s, t, n)


# https://github.com/VaHiX/CodeForces/