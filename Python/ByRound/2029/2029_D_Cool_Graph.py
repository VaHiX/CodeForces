# Contest 2029, Problem D: Cool Graph
# URL: https://codeforces.com/contest/2029/problem/D

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()


for _ in range(int(input())):
    n, m = map(int, input().split())
    conn = [0] * (n + 1)
    res = []

    for _ in range(m):
        u, v = map(int, input().split())
        if u > v:
            u, v = v, u
        if u != 1:
            res += ((1, u, v),)
            conn[u] ^= 1
        conn[v] ^= 1

    for u in range(2, n + 1):
        if conn[u]:
            for v in range(2, n + 1):
                if not conn[v]:
                    res += ((1, u, v),)
                    u = v
            break

    print(len(res))
    for x in res:
        print(*x)
