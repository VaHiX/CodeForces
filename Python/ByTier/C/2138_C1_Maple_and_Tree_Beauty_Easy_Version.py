# Contest 2138, Problem C1: Maple and Tree Beauty (Easy Version)
# URL: https://codeforces.com/contest/2138/problem/C1

import sys
from itertools import *

input = lambda: sys.stdin.readline().rstrip("\r\n")
rint = lambda: int(input())
rlist = lambda: list(map(int, input().split()))
rgrid = lambda n: [list(map(int, input().split())) for _ in range(n)]
fmax = lambda x, y: x if x > y else y
fmin = lambda x, y: x if x < y else y
inf = float("inf")


def prev_greater_left(A):
    # return left[i] = highest j < i with A[j] > A[i], or -1 if none
    N = len(A)
    left = [-1] * N
    stack = []
    for i in range(N):
        while stack and A[stack[-1]] <= A[i]:
            stack.pop()
        left[i] = stack[-1] if stack else -1
        stack.append(i)
    return left


def next_smaller_right(A):
    # return right[i] = lowest j > i with A[j] < A[i], or N if none
    N = len(A)
    right = [N] * N
    stack = []
    for i in range(N - 1, -1, -1):
        while stack and A[stack[-1]] >= A[i]:
            stack.pop()
        right[i] = stack[-1] if stack else N
        stack.append(i)
    return right


def solve():
    N, K = rlist()
    P2 = rlist()
    adj = [[] for _ in range(N)]
    for u, p in enumerate(P2, 1):
        p -= 1
        adj[p].append(u)

    lengths = []
    frontier = [0]
    while frontier:
        lengths.append(len(frontier))
        queue = frontier

        frontier = []
        saw_leaf = 0
        for u in queue:
            if not adj[u]:
                saw_leaf = 1
            for v in adj[u]:
                frontier.append(v)

        if saw_leaf:
            break

    dp = 0b1
    ans = T = 0
    for cur, L in enumerate(lengths, 1):
        dp |= dp << L
        T += L
        lo = max(0, T - N + K)
        hi = K
        for x in range(lo, hi + 1):
            if dp >> x & 1:
                ans = cur
                break

    return ans


TT = 1
TT = rint()
for tc in range(TT):
    ans = solve()
    print(ans)
