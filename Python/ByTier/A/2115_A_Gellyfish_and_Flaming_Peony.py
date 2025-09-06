# Contest 2115, Problem A: Gellyfish and Flaming Peony
# URL: https://codeforces.com/contest/2115/problem/A

testcasenumber = int(input())
# from random import *
# from sys import stdout
# from collections import deque
import math

for counter in range(testcasenumber):
    n = input()
    seg = list(map(int, input().split()))
    u = seg[0]
    dp = [set()]
    dp[-1].add(seg[0])
    for i in range(1, len(seg)):
        u = math.gcd(u, seg[i])
        dp[-1].add(seg[i])
    while u not in dp[-1]:
        dp.append(set())
        for j in dp[0]:
            for k in dp[len(dp) - 2]:
                p = math.gcd(j, k)
                if len(dp) == 1 or p not in dp[-2]:
                    dp[-1].add(p)
                if p == u:
                    break
                # print(i,j,k,dp)
    if u in dp[0]:
        print(len(seg) - seg.count(u))
    else:
        print(len(dp) + len(seg) - 2)
