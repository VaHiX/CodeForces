# Contest 2019, Problem F: Max Plus Min Plus Size
# URL: https://codeforces.com/contest/2019/problem/F

import sys, re
from random import randint
from functools import reduce
from bisect import bisect_left
from operator import xor, add, itemgetter
from math import gcd, inf, atan2, pi, lcm
from collections import deque, defaultdict
from heapq import heappop, heappush, heapify

input = sys.stdin.readline

rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))


def solve():
    n, a = rn(), rl()
    b = sorted([(a[i], i) for i in range(n)], key=itemgetter(0), reverse=True)

    max_val = b[0][0]
    fa, node = list(range(n)), [None] * n
    get_size = lambda node: node[3] - node[2] + 1
    contain_even_count, current_cnt, res = 0, 0, 0

    def contain_even(node):
        even_max, odd_max, l, r, _ = node
        return (even_max and ~(l & r) & 1) or (odd_max and (l | r) & 1)

    def find(x):
        if fa[x] != x:
            fa[x] = find(fa[x])
            return fa[x]
        else:
            return x

    def merge(x, y):
        nonlocal contain_even_count, current_cnt
        fx, fy = find(x), find(y)
        if fx == fy:
            return
        if node[fx][4] > node[fy][4]:
            fx, fy = fy, fx

        fa[fx] = fy
        node_fx, node_fy = node[fx], node[fy]
        even_max_fx, odd_max_fx, l_fx, r_fx, res_fx = node_fx
        even_max_fy, odd_max_fy, l_fy, r_fy, res_fy = node_fy
        node[fy] = (
            even_max_fx or even_max_fy,
            odd_max_fx or odd_max_fy,
            min(l_fx, l_fy),
            max(r_fx, r_fy),
            (max(r_fx, r_fy) - min(l_fx, l_fy) + 2) >> 1,
        )
        contain_even_count += contain_even(node[fy]) - contain_even(node_fx) - contain_even(node_fy)
        current_cnt += node[fy][4] - res_fx - res_fy

    for v, i in b:
        if v == max_val:
            node[i] = (~i & 1, i & 1, i, i, 1)
            contain_even_count += 1
        else:
            node[i] = (False, False, i, i, 1)

        current_cnt += 1
        if i > 0 and a[i - 1] >= v and node[i - 1]:
            merge(i - 1, i)
        if i < n - 1 and a[i + 1] >= v and node[i + 1]:
            merge(i, i + 1)

        res = max(res, current_cnt + v + max_val - (contain_even_count == 0))
    print(res)


[solve() for _ in range(rn())]