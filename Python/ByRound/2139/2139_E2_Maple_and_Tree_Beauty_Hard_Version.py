# Contest 2139, Problem E2: Maple and Tree Beauty (Hard Version)
# URL: https://codeforces.com/contest/2139/problem/E2


import functools
import sys

# sys.setrecursionlimit(2000000)
from collections import defaultdict
import collections

# from sortedcontainers import SortedList
import math
import heapq
from collections import deque
import bisect
import sys

input = sys.stdin.readline
import itertools
from math import gcd

fmin = lambda x, y: x if x < y else y
fmax = lambda x, y: x if x > y else y
rint = lambda: int(input())
rlist = lambda: list(map(int, input().split()))
rgrid = lambda n: [rlist() for _ in range(n)]


def solve(N, K, arr):
    queue = collections.deque()
    graph = [[] for _ in range(N)]
    arr = [-1] + arr
    for i in range(1, len(arr)):
        graph[arr[i]].append(i)

    queue.append(0)
    levels = []
    condition = True
    while queue:
        if not condition:
            break
        to_add = len(queue)
        # levels.append(len(queue))
        if not condition:
            break
        for _ in range(len(queue)):
            node = queue.popleft()
            if not graph[node]:
                condition = False
                break
            else:
                for child in graph[node]:
                    queue.append(child)
        levels.append(to_add)
    # print(levels)
    # return 0
    ones = N - K
    zeros = K
    # print(levels,ones,zeros)
    l = 0
    r = len(levels) - 1
    best_ans = -1

    def check(mid, ones, zeros):
        # print(levels,ones,zeros)
        # levels= list(levels)
        A, B = min(ones, zeros), max(ones, zeros)
        for j in range(mid, -1, -1):
            x = levels[j]
            if A > B:
                A, B = B, A
            if x <= A:
                A -= x
            elif x <= B:
                B -= x
            else:
                return False
        return True

    while l <= r:
        mid = l + (r - l) // 2
        if check(mid, ones, zeros):
            best_ans = mid
            l = mid + 1
        else:
            r = mid - 1

    return best_ans + 1


t = int(input())
for j in range(1, t + 1):
    # S = input()
    # N = int(input())
    # A = input().strip()
    # mat = []
    # A,B = input().split(" ")
    N, K = rlist()
    arr = [x - 1 for x in rlist()]

    result = solve(N, K, arr)
    print(result)
    # print("Case #{}: {}".format(j, result))
    ## print('{:.8f}'.format(result))
