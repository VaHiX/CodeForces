# Contest 2094, Problem H: La Vaca Saturno Saturnita
# URL: https://codeforces.com/contest/2094/problem/H

import sys

input = sys.stdin.readline

from collections import defaultdict

N = int(1e5) + 10
next_pos = [N] * N
factors = [[] for _ in range(N)]

# Precompute all factors for numbers up to N
for i in range(2, N):
    for j in range(i, N, i):
        factors[j].append(i)


def solve_testcase():
    n, nq = map(int, input().split())
    a = list(map(int, input().split()))

    q = [[] for _ in range(n)]
    for i in range(nq):
        k, l, r = map(int, input().split())
        l -= 1
        r -= 1
        q[l].append((r, k, i))

    ans = [0] * nq

    for i in range(n - 1, -1, -1):
        next_pos[a[i]] = i
        for r, k, idx in q[i]:
            l = i
            while True:
                p = N
                for v in factors[k]:
                    p = min(p, next_pos[v])
                if p > r:
                    ans[idx] += (r - l + 1) * k
                    break
                ans[idx] += (p - l) * k
                while k % a[p] == 0:
                    k //= a[p]
                l = p

    for x in ans:
        print(x)

    for i in a:
        next_pos[i] = N


# Run test cases
T = int(input())
for _ in range(T):
    solve_testcase()
