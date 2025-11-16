# Problem: CF 1984 E - Shuffle
# https://codeforces.com/contest/1984/problem/E

"""
Rerooting algorithm to solve the maximum leaves in shuffled tree problem.

Approach:
- This implementation uses a rerooting technique to compute for each node as root,
  the maximum number of leaves that can be achieved in the resulting tree after one shuffle.
- The algorithm:
  1. Performs a DFS to build parent relationships and order
  2. Uses two passes (up-down and down-up) to compute dp values for each node
  3. In the final pass, computes the answer by considering all possible roots

Time Complexity: O(n) - Linear time due to two DFS traversals and constant operations per node
Space Complexity: O(n) - Space for adjacency list, parent array, order, and dp arrays
"""

def rerooting():

    dp1 = [E] * n
    for v in order[::-1]:
        dp1[v] = g(dp1[v], v)
        p = par[v]
        if p != -1:
            dp1[p] = merge(dp1[p], f(dp1[v], p, v))

    dp2 = [E] * n
    [E] * n
    ANS = [[] for i in range(n)]
    for v in order:
        s = len(edge[v])
        cumR = [E] * (s + 1)
        cumR[s] = E
        for i in range(s, 0, -1):
            u = edge[v][i - 1]
            if u == par[v]:
                cumR[i - 1] = merge(cumR[i], f(dp2[v], v, u))
            else:
                cumR[i - 1] = merge(cumR[i], f(dp1[u], v, u))

        cumL = E
        for i in range(s):
            u = edge[v][i]
            if u != par[v]:
                val = merge(cumL, cumR[i + 1])
                dp2[u] = g(val, v)
                cumL = merge(cumL, f(dp1[u], v, u))
                ANS[v].append(dp1[u])
            else:
                cumL = merge(cumL, f(dp2[v], v, u))
                ANS[v].append(dp2[v])

    return ANS


E = (0, 0)


def f(res, v, v_child):
    return res


def g(res, v):
    if res[1] == 0:
        return (res[0] + 1, 1)
    return (res[0], 0)


def merge(a, b):
    return (a[0] + b[0], a[1] | b[1])


def calc_ans(res, v):
    return g(res, v)


from sys import stdin

input = lambda: stdin.readline()[:-1]


for _ in range(int(input())):
    n = int(input())
    edge = [[] for i in range(n)]
    for i in range(n - 1):
        x, y = map(lambda x: int(x) - 1, input().split())
        edge[x].append(y)
        edge[y].append(x)

    order = []
    par = [-1] * n
    todo = [0]
    while todo:
        v = todo.pop()
        order.append(v)
        for u in edge[v]:
            if u != par[v]:
                par[u] = v
                todo.append(u)

    ans = rerooting()

    ANS = 0
    for v in range(n):
        tmp = 0
        if len(ans[v]) == 1:
            tmp += 1
        for x, y in ans[v]:
            tmp += x
        ANS = max(ANS, tmp)
    print(ANS)


# https://github.com/VaHiX/CodeForces/