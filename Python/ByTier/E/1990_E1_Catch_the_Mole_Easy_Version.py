# Problem: CF 1990 E1 - Catch the Mole(Easy Version)
# https://codeforces.com/contest/1990/problem/E1

"""
Interactive problem to find the position of a hidden mole in a tree.
The mole starts in some node and moves to parent node when queried incorrectly.

Algorithms:
- Binary search approach on tree nodes to locate the mole
- BFS to traverse tree and find depths
- Queries to determine if mole is in subtree
- Move mole up the tree when query fails

Time Complexity: O(n * log(n)) per test case where n is number of nodes
Space Complexity: O(n) for storing tree structure and traversal information
"""

debug = 1


def solve():
    n = int(input())
    edge = [[] for i in range(n)]
    for i in range(n - 1):
        a, b = map(lambda x: int(x) - 1, input().split())
        edge[a].append(b)
        edge[b].append(a)
    par = [-1] * n
    todo = [(-1, 0)]
    order = []
    while todo:
        p, v = todo.pop()
        order.append(v)
        for u in edge[v]:
            if p != u:
                par[u] = v
                todo.append((v, u))

    res = [1] * n
    rem = 290
    while True:
        dp = [-1 << 30] * n
        for v in order[::-1]:
            if res[v]:
                dp[v] = max(dp[v], 0)
            if v != 0:
                dp[par[v]] = max(dp[v] + 1, dp[par[v]])
        ask_v = 0
        for v in range(n):
            if dp[v] == rem // 2:
                ask_v = v

        print("?", ask_v + 1, flush=True)
        rem -= 1
        f = int(input())
        if f == 0:
            todo = [ask_v]
            while todo:
                v = todo.pop()
                res[v] = 0
                for u in edge[v]:
                    if u != par[v]:
                        todo.append(u)
            nres = [0] * n
            for v in range(n):
                if v != 0:
                    nres[v] |= res[par[v]]
            res = nres
        else:
            top = ask_v
            assert dp[ask_v] <= rem // 2 + 2
            leaf = -1
            todo = [ask_v]
            while todo:
                v = todo.pop()
                leaf = v
                for u in edge[v]:
                    if u != par[v]:
                        todo.append(u)

            for i in range(rem // 2 + 2):
                print("?", leaf + 1, flush=True)
                f = int(input())
                if f == 1:
                    print("!", leaf + 1, flush=True)
                    return
                print("?", top + 1, flush=True)
                f = int(input())
                if f == 0:
                    v = par[top]
                    if v != 0:
                        v = par[v]
                    print("!", v + 1, flush=True)
                    return
            print("!", top + 1, flush=True)
            return


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/