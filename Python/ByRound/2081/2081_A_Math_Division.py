# Contest 2081, Problem A: Math Division
# URL: https://codeforces.com/contest/2081/problem/A

if 1:
    import sys

    # sys.stdout.flush()   print('.....', flush = True)
    import random  # random.shuffle()
    from itertools import *
    from heapq import *
    from bisect import bisect_left, bisect_right
    from collections import Counter, deque, defaultdict

    input = lambda: sys.stdin.readline().strip()
    import math

    inf = math.inf
    rdm = random.getrandbits(30)

    # sys.set_int_max_str_digits(6000)
    def I():
        return input()

    def II():
        return int(input())

    def MII():
        return map(int, input().split())

    def LI():
        return list(input())

    def LII():
        return list(map(int, input().split()))

    def LFI():
        return list(map(float, input().split()))

    def LSI():
        return list(map(str, input().split()))

    mod = int(1e9 + 7)
    # mod = 998244353

inv = pow(2, mod - 2, mod)

for _ in range(II()):
    n = II()
    s = I()
    la = 0
    for i in range(len(s) - 1, 0, -1):
        if s[i] == "1":
            cur = la + (1 - la) * inv
            cur %= mod
        else:
            cur = la * inv
            cur %= mod
        la = cur
    print(la * len(s) + (1 - la) * (len(s) - 1))
