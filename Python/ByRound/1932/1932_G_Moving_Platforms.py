# Problem: CF 1932 G - Moving Platforms
# https://codeforces.com/contest/1932/problem/G

"""
Algorithm: Shortest Path with Dynamic Level Changes
Approach: Dijkstra's Algorithm with Custom Distance Function
Time Complexity: O((V + E) * log V) where V is number of platforms, E is number of passages
Space Complexity: O(V + E) for graph storage and Dijkstra's data structures

This solution uses Dijkstra's algorithm to find the minimum number of steps to reach platform n from platform 1.
The key insight is that platform levels change over time according to a linear formula.
To determine if we can move from platform u to platform v in some step, we need to solve a modular linear equation.
The distance function computes the earliest step at which platform u and v will have the same level.
"""

import os
import sys
from heapq import heappop, heappush
from io import BytesIO, IOBase


def dijkstra(graph, start, compute_dist):
    n = len(graph)
    dist, parents = [float("inf")] * n, [-1] * n
    dist[start] = 0

    queue = [(0, start)]
    while queue:
        path_len, v = heappop(queue)
        if path_len == dist[v]:
            for w in graph[v]:
                curr_len = compute_dist(path_len, v, w)
                if curr_len < dist[w]:
                    dist[w], parents[w] = curr_len, v
                    heappush(queue, (curr_len, w))

    return dist


def extended_gcd(a, b):
    """returns gcd(a, b), s, r s.t. a * s + b * r == gcd(a, b)"""
    s, old_s = 0, 1
    r, old_r = b, a
    while r:
        q = old_r // r
        old_r, r = r, old_r - q * r
        old_s, s = s, old_s - q * s
    return old_r, old_s, (old_r - old_s * a) // b if b else 0


def modinv(a, m):
    """returns the modular inverse of a w.r.t. to m, works when a and m are coprime"""
    g, x, _ = extended_gcd(a % m, m)
    return x % m if g == 1 else None


def main():
    t = int(input())

    for _ in range(t):
        n, m, H = map(int, input().split())
        l = [int(li) for li in input().split()]
        s = [int(si) for si in input().split()]

        graph = [[] for _ in range(n)]
        for _ in range(m):
            u, v = map(int, input().split())
            graph[u - 1].append(v - 1)
            graph[v - 1].append(u - 1)

        def compute_dist(curr, u, v):
            # Calculate current levels of platforms u and v
            start_u = (l[u] + s[u] * curr) % H
            start_v = (l[v] + s[v] * curr) % H

            # Solve modular equation: (s[u] - s[v]) * step + (start_u - start_v) = 0 (mod H)
            # This is equivalent to: (s[u] - s[v]) * x = (start_v - start_u) (mod H)
            g, x, _ = extended_gcd((s[u] - s[v]) % H, H)
            if (start_v - start_u) % H % g != 0:
                # No solution exists for the modular equation
                return float("inf")

            # Compute minimal step using extended Euclidean algorithm
            # The formula is derived from the extended GCD result
            dist = ((start_v - start_u) % H // g * x) % (H // g)
            return curr + dist + 1  # Add 1 because we start counting from step 1

        sol = dijkstra(graph, 0, compute_dist)[-1]
        print(-1 if sol == float("inf") else sol)


BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/