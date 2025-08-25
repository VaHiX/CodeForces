# Contest 811, Problem C: Vladik and Memorable Trip
# URL: https://codeforces.com/contest/811/problem/C

import sys
from bisect import bisect_left
from collections import *
from itertools import *
from math import *
from array import *
from functools import lru_cache
import heapq
import bisect
import random
import io, os

if sys.hexversion == 50923504:
    sys.stdin = open("cfinput.txt")

RI = lambda: map(int, sys.stdin.buffer.readline().split())
RS = lambda: map(bytes.decode, sys.stdin.buffer.readline().strip().split())
RILST = lambda: list(RI())

MOD = 10**9 + 7
"""https://codeforces.com/problemset/problem/811/C

输入 n(≤5000) 和一个长为 n 的数组 a (0≤a[i]≤5000)。
你需要从 a 中选取若干个互不相交的子数组，且对于每个子数组 b，b 中的元素不会出现在 b 外面。
对每个子数组去重，求异或和，然后把所有异或和相加，输出相加后的最大值。

注：子数组是连续的。
注：你不需要把每个 a[i] 都选上，见样例二。
输入
6
4 4 2 5 2 3
输出 14
解释 选择 [4,4] [2,5,2] [3]，4+(2^5)+3=14

输入
9
5 1 3 1 5 2 4 2 5
输出 9
解释 选择 [3] [2,4,2]，3+(2^4)=9
左右位置：https://codeforces.com/contest/811/submission/174568758
元素个数（代码更短）：https://codeforces.com/contest/811/submission/174568255

dp[i] = dp[j-1] + xor(unique(j..i)) if a[j..i] is valid.
判断合法有两种写法，见上面的代码。
"""


# 	 ms
def solve(n, a):
    f = [0] * (n + 1)
    mx = max(a)
    first = [n] * (mx + 1)  # 每个数字第一次出现的位置
    last = [0] * (mx + 1)
    for i, v in enumerate(a):
        first[v] = min(first[v], i)
        last[v] = i
    vis = [-1] * (mx + 1)
    for i, v in enumerate(a):
        f[i + 1] = f[i]
        ft = first[v]  # 当前区间所有数字最早出现的位置
        s = 0
        for j in range(i, -1, -1):
            if last[a[j]] > i:  # 如果存在任意数字最后出现在i后边，说明这个区间不合法
                break
            ft = min(ft, first[a[j]])
            if vis[a[j]] != i:  # 每个数值只异或一次
                vis[a[j]] = i
                s ^= a[j]
            if j <= ft:  # 只有当j在ft左边，才说明包含了这个区间内所有数字的所有范围
                f[i + 1] = max(f[i + 1], f[j] + s)
        # f[i + 1] = max(f[i + 1], f[i])
    # print(f)
    print(f[n])


if __name__ == "__main__":
    (n,) = RI()
    a = RILST()

    solve(n, a)
