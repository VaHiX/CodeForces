# Contest 1990, Problem E1: Catch the Mole(Easy Version)
# URL: https://codeforces.com/contest/1990/problem/E1

from sys import stdin, stdout
from collections import deque

t = int(stdin.readline())

for _ in range(t):
    n = int(stdin.readline())
    edges = {i: [] for i in range(n)}
    degree = [0] * n
    for bar in range(n - 1):
        u, v = [int(x) - 1 for x in stdin.readline().split()]
        edges[u].append(v)
        edges[v].append(u)
        degree[u] += 1
        degree[v] += 1

    parent = [-1] * n

    queue = deque()
    queue.append(0)

    while len(queue) > 0:
        v = queue.popleft()
        for w in edges[v]:
            if w != parent[v]:
                queue.append(w)
                parent[w] = v

    active = []
    for v in range(1, n):
        if degree[v] == 1:
            active.append(v)

    floor = -1
    ceiling = -1
    while floor == -1:
        if len(active) == 1:
            floor = active[0]
            ceiling = 0

        else:
            v = active[0]
            pointer = v
            while parent[pointer] > 0 and degree[parent[pointer]] < 3:
                pointer = parent[pointer]

            stdout.write("? {}\n".format(pointer + 1))
            stdout.flush()
            result = int(stdin.readline())

            if result == 1:
                floor = v
                ceiling = pointer

            else:
                degree[parent[pointer]] -= 1

                active2 = set()

                for i in range(1, len(active)):
                    w = active[i]
                    degree[parent[w]] -= 1

                for i in range(1, len(active)):
                    w = active[i]
                    if parent[w] == 0:
                        if degree[0] == 0:
                            active2.add(0)

                    else:
                        if degree[parent[w]] == 1:
                            active2.add(parent[w])

                active = list(active2)

    path = [floor]
    pointer = floor
    while pointer != 0:
        pointer = parent[pointer]
        path.append(pointer)
    path = path[::-1]

    for i in range(len(path)):
        if path[i] == ceiling:
            lower = i
        if path[i] == floor:
            upper = i + 1

    while upper - lower > 1:
        candidate = (upper + lower) // 2

        stdout.write("? {}\n".format(path[candidate] + 1))
        stdout.flush()
        result = int(stdin.readline())

        if result == 1:
            lower = candidate

        else:
            upper = max(1, candidate - 1)
            lower = max(0, lower - 1)

    stdout.write("! {}\n".format(path[lower] + 1))
    stdout.flush()
