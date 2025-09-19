# Contest 1240, Problem C: Paint the Tree
# URL: https://codeforces.com/contest/1240/problem/C

import sys

input = sys.stdin.readline
from collections import defaultdict, deque, Counter
from heapq import heappop, heappush
from bisect import bisect_left, bisect_right
from math import gcd


def dfs(root, n):
    par = [-1] * (n + 1)
    que = [~root, root]
    now = -1
    while que:
        crr = que.pop()
        now += 1
        if crr >= 0:
            # 入るときの処理なんか
            for nxt, w in graph[crr]:
                if par[crr] == nxt:
                    continue
                par[nxt] = crr
                que.append(~nxt)
                que.append(nxt)
        else:
            crr = ~crr
            # 出るときの処理なんか
            if len(graph[crr]) - 1 < k:
                tmp = 0
                for nxt, w in graph[crr]:
                    if par[crr] == nxt:
                        continue
                    tmp += max(dp[nxt * 2 + 1] + w, dp[nxt * 2 + 0])
                dp[crr * 2 + 1] = tmp
                dp[crr * 2 + 0] = tmp
            else:
                ds = []
                tmp = 0
                for nxt, w in graph[crr]:
                    if par[crr] == nxt:
                        continue
                    ds.append(max(0, dp[nxt * 2 + 1] + w - dp[nxt * 2 + 0]))
                    tmp += dp[nxt * 2 + 0]
                ds.sort()
                ds = [0] + ds[::-1]
                for i in range(1, len(ds)):
                    ds[i] += ds[i - 1]
                dp[crr * 2 + 1] = ds[k - 1] + tmp
                dp[crr * 2] = (ds[k]) + tmp
            if par[crr] == -1:
                continue
    return  # tour, in_time, out_time


def sol():
    global graph, dp, k
    n, k = map(int, input().split())
    graph = [[] for i in range(n + 1)]
    for i in range(n - 1):
        u, v, w = map(int, input().split())
        graph[u].append((v, w))
        graph[v].append((u, w))

    dp = [0] * (2 * (n + 1))
    dfs(1, n)
    print(max(dp[1 * 2 + 0], dp[1 * 2 + 1]))
    return


T = int(input())
for i in range(T):
    sol()
