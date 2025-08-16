# Contest 2121, Problem E: Sponsor of Your Problems
# URL: https://codeforces.com/contest/2121/problem/E

import sys
import math
from collections import defaultdict

MOD = 1e9+7

def input():
    return sys.stdin.readline().strip()
    
t = int(input())
for tcs in range(t):
    l, r = input().split()
    res = 0
    for i in range(1, len(l) + 1):
        res += 2 * (int(l[:i]) == int(r[:i])) + (int(l[:i]) + 1 == int(r[:i]))
    # print('mvk')
    print(res)
    