# Contest 2028, Problem D: Alice's Adventures in Cards
# URL: https://codeforces.com/contest/2028/problem/D

import sys

input = sys.stdin.readline
W = ["q", "k", "j"]


def solve():
    n = int(input())
    P = []
    for _ in range(3):
        P.append(list(map(int, input().split())))

    min_to_reach = [n - 1] * 3
    nxt = [-1] * n
    ans = [-1] * n

    for i in range(n - 2, -1, -1):
        for j in range(3):
            if P[j][i] > P[j][min_to_reach[j]]:
                # Trade card i with player j
                ans[i] = j
                nxt[i] = min_to_reach[j]
                for k in range(3):
                    if P[k][min_to_reach[k]] > P[k][i]:
                        min_to_reach[k] = i
                break

    if ans[0] == -1:
        return "NO"

    res = []
    curr = 0

    while curr != n - 1:
        res.append(f"{W[ans[curr]]} {nxt[curr] + 1}")
        curr = nxt[curr]

    return f"YES\n{len(res)}\n" + "\n".join(res)


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))
