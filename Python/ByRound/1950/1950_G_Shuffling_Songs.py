# Problem: CF 1950 G - Shuffling Songs
# https://codeforces.com/contest/1950/problem/G

"""
Code Purpose:
This code solves the problem of finding the minimum number of songs to remove from a playlist so that the remaining songs can be arranged in an "exciting" order. An exciting playlist is one where each adjacent pair of songs either shares the same writer or the same genre.

The approach uses:
- A bitset to represent subsets of songs
- BFS to explore all valid orderings of songs
- Preprocessing to identify which songs can be adjacent (same writer or genre)
- Dynamic exploration of valid permutations using BFS with state tracking

Time Complexity:
O(2^n * n^2 + n * 2^n) where n <= 16. The first term accounts for the BFS with up to 2^n states and transitions, and the second term for preprocessing.

Space Complexity:
O(2^n + n^2) for the valid array and the adjacency matrix.
"""

from collections import deque
from sys import stdin

input = lambda: stdin.readline()
t = int(input())
maxm = 1 << 16
mp = [[0 for _ in range(16)] for _ in range(16)]
w = []
g = []
valid = [0] * maxm


def tos(lis):
    # Convert list of indices to a bitmask
    res = 0
    for x in lis:
        res |= 1 << x
    return res


def bfs():
    res = 0
    q = deque([])
    # Initialize BFS with each individual song
    for i in range(n):
        valid[1 << i] = 1
        q.append([i])
    while len(q):
        fr = q.popleft()
        st = tos(fr)
        res = max(res, len(fr))
        # Try adding each unvisited song to the sequence
        for i in range(n):
            if st >> i & 1:  # Skip if song is already in sequence
                continue
            # Try inserting at various positions in the current sequence
            for j in range(1, len(fr)):
                if mp[fr[j]][i] and mp[fr[j - 1]][i]:
                    # Insert before position j
                    nxt = st | (1 << i)
                    if valid[nxt]:  # Skip if already processed
                        continue
                    valid[nxt] = 1
                    q.append(fr[:j] + [i] + fr[j:])
            # Try inserting at the beginning
            if mp[fr[0]][i]:
                nxt = st | (1 << i)
                if not valid[nxt]:
                    valid[nxt] = 1
                    q.append([i] + fr)
            # Try inserting at the end
            if mp[fr[-1]][i]:
                nxt = st | (1 << i)
                if not valid[nxt]:
                    valid[nxt] = 1
                    q.append(fr + [i])
    return res


for _ in range(t):
    n = int(input())
    w.clear()
    g.clear()
    for i in range(n):
        for j in range(n):
            mp[i][j] = 0  # Reset adjacency matrix
    for i in range(1 << n):
        valid[i] = 0  # Reset valid states
    for i in range(n):
        s = input().split()
        w.append(s[0])
        g.append(s[1])
    # Build adjacency matrix based on same writer or genre
    for i in range(n):
        for j in range(i + 1, n):
            if w[i] == w[j] or g[i] == g[j]:
                mp[i][j] = 1
                mp[j][i] = 1
    print(n - bfs())  # Minimum removals = total - max valid sequence length


# https://github.com/VaHiX/CodeForces/