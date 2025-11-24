# Problem: CF 1715 E - Long Way Home
# https://codeforces.com/contest/1715/problem/E

"""
Algorithm: Shortest Path with Limited Flights
Techniques: Dijkstra's Algorithm, Convex Hull Trick (CHT), Bit Manipulation

Time Complexity: O((n + m) * log(n) + n * k)
Space Complexity: O(n)

The problem requires finding the shortest path from city 1 to all other cities,
where Stanley can take at most k flights. Each flight between cities u and v
takes (u - v)^2 time, while roads take their given weight.

Approach:
1. First, compute shortest distances using only roads (Dijkstra).
2. Then, for k iterations, apply Convex Hull Trick to optimize the
   cost of taking flights. Each flight from city u to v costs (u - v)^2,
   which can be represented as a quadratic function. By using CHT, we can
   efficiently query the minimum cost of such flights.
3. For each iteration:
   - Apply CHT to update distance array
   - Run Dijkstra again on updated distances to account for new roads
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]

n, m, k = map(int, input().split())
edge = [[] for i in range(n)]
for _ in range(m):
    a, b, c = map(int, input().split())
    a, b = a - 1, b - 1
    edge[a].append((b, c))
    edge[b].append((a, c))

from heapq import heappop, heappush


def dijkstra():
    hq = []
    for i in range(n):
        if dist[i] != inf:
            heappush(hq, (dist[i], i))
    seen = [0] * n
    while hq:
        w, v = heappop(hq)
        if dist[v] < w:
            continue
        seen[v] = True
        for to, cost in edge[v]:
            if seen[to] == False and dist[v] + cost < dist[to]:
                dist[to] = dist[v] + cost
                heappush(hq, (dist[to], to))


mask = (1 << 17) - 1


def dijkstra2():
    hq = []
    for i in range(n):
        if dist[i] != inf:
            heappush(hq, (dist[i] << 17) + i)
    seen = [0] * n
    while hq:
        x = heappop(hq)
        w, v = x >> 17, x & mask
        if dist[v] < w:
            continue
        seen[v] = True
        for to, cost in edge[v]:
            if seen[to] == False and dist[v] + cost < dist[to]:
                dist[to] = dist[v] + cost
                heappush(hq, (dist[to] << 17) + to)


from collections import deque


def CHT():
    def check(f1, f2, f3):
        return (f2[0] - f1[0]) * (f3[1] - f2[1]) >= (f2[1] - f1[1]) * (f3[0] - f2[0])

    def f(f1, x):
        return f1[0] * x + f1[1]

    def add_line(a, b):
        f1 = (a, b)
        while len(deq) >= 2 and check(deq[-2], deq[-1], f1):
            deq.pop()
        deq.append(f1)

    def query(x):
        while len(deq) >= 2 and f(deq[0], x) >= f(deq[1], x):
            deq.popleft()
        return f(deq[0], x)

    res = dist.copy()

    deq = deque()
    for i in range(n):
        add_line(-2 * i, dist[i] + i * i)

    for i in range(n):
        res[i] = query(i) + i * i
    return res


inf = 1 << 60
dist = [inf] * n
dist[0] = 0
dijkstra2()

for _ in range(k):
    dist = CHT()
    dijkstra2()

print(*dist)


# https://github.com/VaHiX/CodeForces/