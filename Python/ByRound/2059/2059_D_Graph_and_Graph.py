# Contest 2059, Problem D: Graph and Graph
# URL: https://codeforces.com/contest/2059/problem/D

import sys
from collections import deque

# sys.setrecursionlimit(10000)


def input_general():
    return sys.stdin.readline().rstrip("\r\n")


def input_num():
    return int(sys.stdin.readline().rstrip("\r\n"))


def input_multi(x=int):
    return map(x, sys.stdin.readline().rstrip("\r\n").split())


def input_list(x=int):
    return list(input_multi(x))


def main():
    n, s1, s2 = input_multi()

    m1 = input_num()
    ed1 = [[] for _ in range(n + 1)]
    for _ in range(m1):
        u, v = input_multi()
        ed1[u].append(v)
        ed1[v].append(u)

    m2 = input_num()
    ed2 = [[] for _ in range(n + 1)]
    for _ in range(m2):
        u, v = input_multi()
        ed2[u].append(v)
        ed2[v].append(u)

    stop = set()
    for u in range(1, n + 1):
        if set(ed1[u]).intersection(set(ed2[u])):
            stop.add(u)

    seen = [[10**10 for _ in range(n + 1)] for _ in range(n + 1)]
    seen[s1][s2] = 0

    dq = deque([[(s1, s2)]])
    offset = 0
    in_stack = 1

    while in_stack:
        while len(dq[0]) == 0:
            offset += 1
            dq.popleft()

        v1, v2 = dq[0].pop()
        if v1 == v2 and v1 in stop:
            print(offset)
            return

        in_stack -= 1
        if offset > seen[v1][v2]:
            continue

        for u1 in ed1[v1]:
            for u2 in ed2[v2]:
                new = abs(u1 - u2)
                cost = offset + new

                if cost < seen[u1][u2]:
                    seen[u1][u2] = cost

                    while len(dq) <= new:
                        dq.append([])

                    dq[new].append((u1, u2))
                    in_stack += 1

    print(-1)


if __name__ == "__main__":
    cases = input_num()

    for _ in range(cases):
        main()
