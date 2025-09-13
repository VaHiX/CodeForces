# Contest 2121, Problem F: Yamakasi
# URL: https://codeforces.com/contest/2121/problem/F

import sys
import math
from collections import defaultdict

MOD = 1e9 + 7


def input():
    return sys.stdin.readline().strip()


t = int(input())
for tcs in range(t):
    n, s, x = map(int, input().split())
    sums = [0] + list(map(int, input().split()))
    # sums = a.copy()
    for i in range(1, n + 1):
        sums[i] = sums[i - 1] + sums[i]

    # from collections import defaultdict
    # cnt = defaultdict(int)
    cnt = {}
    j = 0
    res = 0
    for i in range(1, n + 1):
        if sums[i] - sums[i - 1] == x:
            while j < i:
                if sums[j] not in cnt:
                    cnt[sums[j]] = 0
                cnt[sums[j]] += 1
                j += 1
        if sums[i] - sums[i - 1] > x:
            j = i
            cnt.clear()
        res += cnt.get(sums[i] - s, 0)
    # print('mvk')
    # print(a)
    print(res)
