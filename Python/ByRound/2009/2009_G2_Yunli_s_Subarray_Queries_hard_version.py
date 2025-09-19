# Contest 2009, Problem G2: Yunli's Subarray Queries (hard version)
# URL: https://codeforces.com/contest/2009/problem/G2

import sys

# region fastio
from collections import Counter
from heapq import heappop, heappush
from math import inf
from random import getrandbits
from types import GeneratorType

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def bootstrap(f, stack=None):
    if stack is None:
        stack = []

    def func(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return func


MOD = 10 ** 9 + 7

mx = 2 * 10 ** 5
# f = [0] * MX
# f[0] = f[1] = 1
# for i in range(2, MX):
#     f[i] = f[i - 1] + 2 * (i - 1) * f[i - 2]
#     f[i] %= MOD
# 阶乘
fac = [1] * (mx + 1)
for i in range(1, mx + 1):
    fac[i] = fac[i - 1] * i % MOD
# 逆元
ifac = [0] * (mx + 1)
ifac[mx] = pow(fac[mx], MOD - 2, MOD)
for i in range(mx, 0, -1):
    ifac[i - 1] = ifac[i] * i % MOD


# 组合数
def comb(n: int, m: int, MOD=MOD) -> int:
    if m < 0 or m > n:
        return 0
    return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD


# endregion fastio

# MOD = 998_244_353
# MOD = 10 ** 9 + 7
# DIR4 = ((-1, 0), (0, 1), (1, 0), (0, -1)) #URDL
# DIR8 = ((-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1))
def cf2002A():
    n, k, q = mint()
    a = ints()
    for i in range(n):
        a[i] -= i

    h = getrandbits(30)
    cnt = Counter()
    cnt_mx = Counter()
    mx = 0
    for i in range(k):
        x = a[i]
        cnt[x ^ h] += 1
        cnt_mx[cnt[x ^ h]] += 1
        if cnt[x ^ h] > 1:
            cnt_mx[cnt[x ^ h] - 1] -= 1
        mx = max(mx, cnt[x ^ h])

    res = [k - mx]

    l = 0
    for r in range(k, n):
        x = a[r]
        cnt[x ^ h] += 1
        cnt_mx[cnt[x ^ h]] += 1
        if cnt[x ^ h] > 1:
            cnt_mx[cnt[x ^ h] - 1] -= 1
        mx = max(mx, cnt[x ^ h])
        x = a[l]
        cnt[x ^ h] -= 1
        cnt_mx[cnt[x ^ h]] += 1
        cnt_mx[cnt[x ^ h] + 1] -= 1
        if cnt[x ^ h] + 1 == mx and cnt_mx[cnt[x ^ h] + 1] == 0:
            mx -= 1
        l += 1
        res.append(k - mx)


    queries = [[] for _ in range(n)]
    for i in range(q):
        l, r = mint()
        l -= 1
        r -= 1
        r -= k - 1
        queries[l].append(r * q + i)


    # 单点栈
    # 若res[i-1] < res[i],显然后面的不如前面,用前面的结果即可
    res.append(0) # 加入哨兵，方便判断
    m = len(res)
    dq = [m-1]
    acc = [0]
    ans = [-1] * q

    def check(x: int, y: int) -> bool:
        return dq[x] <= y

    for i in range(m-2,-1,-1):
        while res[i] < res[dq[-1]]:
            dq.pop()
            acc.pop()

        acc.append(acc[-1] + res[i] * (dq[-1] - i))
        dq.append(i)

        for query in queries[i]:
            r, idx = divmod(query, q)

            # 在单调栈中 找到<=r的最近位置，左边直接用acc的前缀和计算，右边用单调栈中该索引对应的值计算
            left = 0
            right = len(dq) - 1
            while left < right:
                mid = (left + right) >> 1
                if check(mid, r):
                    right = mid - 1
                else:
                    left = mid + 1
            left = left if check(left, r) else left + 1
            ans[idx] = acc[-1] - acc[left] + res[dq[left]] * (r - dq[left] + 1)
    for x in ans:
        print(x)

    return


if __name__ == "__main__":
    t_ = sint()
    for _ in range(t_):
        cf2002A()