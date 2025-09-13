# Contest 2137, Problem G: Cry Me a River
# URL: https://codeforces.com/contest/2137/problem/G

# https://codeforces.com/contest/2137

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


def solve_case():
    n, m, q = map(int, input().split())
    out_degree = [0] * n
    in_edges = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(lambda x: int(x) - 1, input().split())
        out_degree[u] += 1
        in_edges[v].append(u)

    red = [False] * n
    cry_wins = [True] * n
    n_cry_wins_next = out_degree[:]
    river_wins = [False] * n
    n_river_wins_next = [0] * n

    ans = []
    for _ in range(q):
        t, u = map(lambda x: int(x) - 1, input().split())

        if t == 0:
            if red[u]:
                continue
            red[u] = True
            q = []
            if cry_wins[u]:
                cry_wins[u] = False
                for v in in_edges[u]:
                    n_cry_wins_next[v] -= 1
                    q.append(v)
            if not river_wins[u]:
                river_wins[u] = True
                for v in in_edges[u]:
                    n_river_wins_next[v] += 1
                    q.append(~v)

            for u in q:
                if u >= 0:
                    if river_wins[u]:
                        continue
                    if n_cry_wins_next[u] < out_degree[u]:
                        river_wins[u] = True
                        for v in in_edges[u]:
                            n_river_wins_next[v] += 1
                            q.append(~v)
                else:
                    u = ~u
                    if not cry_wins[u]:
                        continue
                    if n_river_wins_next[u] == out_degree[u]:
                        cry_wins[u] = False
                        for v in in_edges[u]:
                            n_cry_wins_next[v] -= 1
                            q.append(v)

        elif t == 1:
            ans.append("YES" if cry_wins[u] else "NO")

    return "\n".join(ans)


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))
