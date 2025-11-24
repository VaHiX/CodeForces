# Problem: CF 2109 F - Penguin Steps
# https://codeforces.com/contest/2109/problem/F

"""
Algorithm: 
- Find minimum cost paths from (1,1) to (r,n) and from (n,1) to (r,n) using Dijkstra's algorithm
- Use binary search on the answer to find maximum dis_F 
- For each candidate answer, simulate Mouf's operations using a modified Dijkstra that accounts for:
  - How many operations are available
  - Which cells can be used (black cells only)
  - How operations affect the path cost for Fouad
Time Complexity: O(n^2 * log(n^2)) due to binary search and Dijkstra
Space Complexity: O(n^2) for storing distances and visited arrays
"""

import heapq
import sys
from collections import deque

INF = 0x3FFFFFFF
dx4 = (-1, 0, 1, 0)
dy4 = (0, 1, 0, -1)


def runcase():
    input = sys.stdin.readline
    n, p, k = map(int, input().split())
    p -= 1
    a = [list(map(int, input().split())) for _ in range(n)]
    s = [input().strip() for _ in range(n)]
    dist = [[INF] * n for _ in range(n)]
    pq = []

    def push4(d, i, j):
        nd = max(d, a[i][j])
        if nd < dist[i][j]:
            dist[i][j] = nd
            heapq.heappush(pq, (nd, i, j))

    push4(0, p, n - 1)
    while pq:
        d, i, j = heapq.heappop(pq)
        if d > dist[i][j]:
            continue
        for dir in range(4):
            ii, jj = i + dx4[dir], j + dy4[dir]
            if 0 <= ii < n and 0 <= jj < n:
                push4(d, ii, jj)
    ans1 = dist[0][0]
    ans2 = dist[n - 1][0]
    vis = [[False] * n for _ in range(n)]
    dq = deque()

    def mark(i, j):
        if not vis[i][j]:
            vis[i][j] = True
            dq.append((i, j))

    for j in range(n):
        mark(0, j)
    for i in range(1, p + 1):
        mark(i, n - 1)
    while dq:
        i, j = dq.popleft()
        if a[i][j] <= ans1:
            continue
        for di in (-1, 0, 1):
            for dj in (-1, 0, 1):
                ii, jj = i + di, j + dj
                if 0 <= ii < n and 0 <= jj < n:
                    mark(ii, jj)

    def check(m):
        b = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if a[i][j] < m:
                    b[i][j] = (m - a[i][j]) if s[i][j] == "1" else INF
                else:
                    b[i][j] = 0
                if m > ans1 and vis[i][j]:
                    b[i][j] = INF
        dist2 = [[INF] * n for _ in range(n)]
        pq2 = []

        def push2(d, i, j):
            nd = d + b[i][j]
            if nd < dist2[i][j]:
                dist2[i][j] = nd
                heapq.heappush(pq2, (nd, i, j))

        for j in range(n):
            push2(0, 0, j)
        for i in range(1, n):
            push2(0, i, 0)
        for i in range(1, p + 1):
            push2(0, i, n - 1)
        while pq2:
            d, i, j = heapq.heappop(pq2)
            if d > k:
                break
            if i == n - 1 or (j == n - 1 and i >= p):
                return True
            if d > dist2[i][j]:
                continue
            for di in (-1, 0, 1):
                for dj in (-1, 0, 1):
                    ii, jj = i + di, j + dj
                    if 0 <= ii < n and 0 <= jj < n:
                        push2(d, ii, jj)
        return False

    lo, hi = ans2, 2_000_000
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if check(mid):
            lo = mid
        else:
            hi = mid - 1
    print(ans1, lo)


def main():
    input = sys.stdin.readline
    t = int(input())
    for _ in range(t):
        runcase()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/