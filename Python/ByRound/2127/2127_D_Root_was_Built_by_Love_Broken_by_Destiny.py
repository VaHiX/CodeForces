# Contest 2127, Problem D: Root was Built by Love, Broken by Destiny
# URL: https://codeforces.com/contest/2127/problem/D

import sys

MOD = 10**9 + 7
MAXN = 2 * 10**5 + 5

# precompute factorials up to max n
fact = [1] * MAXN
for i in range(1, MAXN):
    fact[i] = (fact[i - 1] * i) % MOD


def solve():
    it = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(it)
    out_lines = []
    for _ in range(t):
        n = next(it)
        m = next(it)

        # read graph
        adj = [[] for _ in range(n)]
        deg = [0] * n
        for _ in range(m):
            u = next(it) - 1
            v = next(it) - 1
            adj[u].append(v)
            adj[v].append(u)
            deg[u] += 1
            deg[v] += 1

        # must be a tree (connected is guaranteed)
        if m != n - 1:
            out_lines.append("0")
            continue

        ans = 2
        leaves = sum(1 for d in deg if d == 1)

        # check each non-leaf and multiply by (#leaf-neighbours)!
        ok = True
        for u in range(n):
            if deg[u] > 1:
                x = 0
                for v in adj[u]:
                    if deg[v] == 1:
                        x += 1
                # needs at most two non-leaf neighbours
                if x < deg[u] - 2:
                    ok = False
                    break
                ans = (ans * fact[x]) % MOD

        if not ok:
            out_lines.append("0")
            continue

        # if core length >= 2, multiply by 2; otherwise by 1
        if leaves < n - 1:
            ans = (ans * 2) % MOD

        out_lines.append(str(ans))

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()
