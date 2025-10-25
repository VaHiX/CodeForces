# Contest 2009, Problem G3: Yunli's Subarray Queries (extreme version)
# URL: https://codeforces.com/contest/2009/problem/G3

import sys

# region fastio
from collections import Counter, defaultdict
from heapq import heappop, heappush
from itertools import accumulate
from math import inf
from random import getrandbits
from types import GeneratorType

import typing

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
class BIT:
    def __init__(self, n: int):
        self.tree = [0] * n  # 树状数组
        self.n = n
        self.m = len(bin(n)[2:])

    def add(self, x: int, val: int) -> None:
        while x < self.n:
            self.tree[x] += val
            x |= x + 1

    # 维护权值和
    def sm(self, x: int) -> int:
        res = 0
        while x > 0:
            res += self.tree[x - 1]
            x &= x - 1
        return res

    def range_sm(self, l: int, r: int) -> int:
        return self.sm(r) - self.sm(l)

    def select(self, k: int):
        x = 0
        cur = 0
        i = 1 << self.m
        while i > 0:
            if x + i <= self.n and cur + self.tree[x + i - 1] <= k:
                x += i
                cur += self.tree[x - 1]
            i //= 2
        return x


class SegTree:
    def __init__(self,
                 op: typing.Callable[[typing.Any, typing.Any], typing.Any],
                 e: typing.Any,
                 v: typing.Union[int, typing.List[typing.Any]]) -> None:
        self._op = op
        self._e = e

        if isinstance(v, int):
            v = [e] * v

        self._n = len(v)
        self._log = (self._n - 1).bit_length()
        self._size = 1 << self._log
        self._d = [e] * (2 * self._size)

        for i in range(self._n):
            self._d[self._size + i] = v[i]
        for i in range(self._size - 1, 0, -1):
            self._update(i)

    def set(self, p: int, x: typing.Any) -> None:
        assert 0 <= p < self._n

        p += self._size
        self._d[p] = x
        for i in range(1, self._log + 1):
            self._update(p >> i)

    def get(self, p: int) -> typing.Any:
        assert 0 <= p < self._n

        return self._d[p + self._size]

    def prod(self, left: int, right: int) -> typing.Any:
        assert 0 <= left <= right <= self._n
        sml = self._e
        smr = self._e
        left += self._size
        right += self._size

        while left < right:
            if left & 1:
                sml = self._op(sml, self._d[left])
                left += 1
            if right & 1:
                right -= 1
                smr = self._op(self._d[right], smr)
            left >>= 1
            right >>= 1

        return self._op(sml, smr)

    def all_prod(self) -> typing.Any:
        return self._d[1]

    def max_right(self, left: int,
                  f: typing.Callable[[typing.Any], bool]) -> int:
        assert 0 <= left <= self._n
        assert f(self._e)

        if left == self._n:
            return self._n

        left += self._size
        sm = self._e

        first = True
        while first or (left & -left) != left:
            first = False
            while left % 2 == 0:
                left >>= 1
            if not f(self._op(sm, self._d[left])):
                while left < self._size:
                    left *= 2
                    if f(self._op(sm, self._d[left])):
                        sm = self._op(sm, self._d[left])
                        left += 1
                return left - self._size
            sm = self._op(sm, self._d[left])
            left += 1

        return self._n

    def min_left(self, right: int,
                 f: typing.Callable[[typing.Any], bool]) -> int:
        assert 0 <= right <= self._n
        assert f(self._e)

        if right == 0:
            return 0

        right += self._size
        sm = self._e

        first = True
        while first or (right & -right) != right:
            first = False
            right -= 1
            while right > 1 and right % 2:
                right >>= 1
            if not f(self._op(self._d[right], sm)):
                while right < self._size:
                    right = 2 * right + 1
                    if f(self._op(self._d[right], sm)):
                        sm = self._op(self._d[right], sm)
                        right -= 1
                return right + 1 - self._size
            sm = self._op(self._d[right], sm)

        return 0

    def _update(self, k: int) -> None:
        self._d[k] = self._op(self._d[2 * k], self._d[2 * k + 1])


fmax = lambda x, y: x if x > y else y
fmin = lambda x, y: x if x < y else y


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

    m = len(res)
    # 前后缀分解， 找到每个元素左右第一个比他小的元素
    left = [-1] * m
    dq = [-1]
    for i in range(m):
        while dq[-1] != -1 and res[dq[-1]] > res[i]:
            dq.pop()
        left[i] = dq[-1] + 1
        dq.append(i)

    right = [m] * m
    dq = [m]
    for i in range(m - 1, -1, -1):
        while dq[-1] != m and res[dq[-1]] >= res[i]:
            dq.pop()
        right[i] = dq[-1]
        dq.append(i)
    # 线段树维护区间最小值的下标，相等取左边

    seg = SegTree(fmin, 10 ** 10, [res[i] * m + i for i in range(m)])
    # sum(ans[i] * (min(right[i], r + 1) - i) * (i + 1 - max(left[i], l)) for i in range(l, r + 1))

    acc_right = list(accumulate((res[i] * (right[i] - i) * (i + 1) for i in range(m)), initial=0))
    acc_left = list(accumulate((res[i] * (-i) * (i + 1 - left[i]) for i in range(m)), initial=0))
    ls = []
    rs = []
    queries_ls = [[] for _ in range(m + 1)]
    queries_rs = [[] for _ in range(m + 1)]

    ans = [0] * q
    for i in range(q):
        l, r = mint()
        l -= 1
        r -= 1
        r -= k - 1
        ls.append(l)
        rs.append(r)
        # 找到最小下标
        idx = seg.prod(l, r + 1) % m
        ans[i] = res[idx] * (fmin(right[idx], r + 1) - idx) * (idx + 1 - fmax(left[idx], l))
        # idx右边的区间左端点确定，右端点不确定，可能超过r，先待定不算，先计算左边部分
        ans[i] += acc_left[r + 1] - acc_left[idx + 1]
        # idx左边的区间右端点确定，左端点不确定，可能低于l，先待定不算，先计算右边部分
        ans[i] += acc_right[idx] - acc_right[l]
        # 待定的后续用树状数组求解
        if l < idx:
            queries_ls[l - 1].append(~i)
            queries_ls[idx - 1].append(i)
        if idx < r:
            queries_rs[r + 1].append(~i)
            queries_rs[idx + 1].append(i)

    fen_cnt = BIT(m + 1)
    fen_sum = BIT(m + 1)

    for i in range(m):
        fen_cnt.add(left[i], res[i] * (right[i] - i))
        fen_sum.add(left[i], res[i] * (right[i] - i) * left[i])
        for q_idx in queries_ls[i]:
            if q_idx < 0:
                q_idx = ~q_idx
                l = ls[q_idx]
                ans[q_idx] += fen_sum.range_sm(l, m+1) + fen_cnt.range_sm(0, l) * l
            else:
                l = ls[q_idx]
                ans[q_idx] -= fen_sum.range_sm(l, m+1) + fen_cnt.range_sm(0, l) * l

    fen_cnt = BIT(m + 1)
    fen_sum = BIT(m + 1)

    for i in range(m - 1, -1, -1):
        fen_cnt.add(right[i], res[i] * (i + 1 - left[i]))
        fen_sum.add(right[i], res[i] * (i + 1 - left[i]) * right[i])
        for q_idx in queries_rs[i]:
            if q_idx < 0:
                q_idx = ~q_idx
                r = rs[q_idx]
                ans[q_idx] -= fen_sum.range_sm(0, r+1) + fen_cnt.range_sm(r + 1, m+1) * (r + 1)
            else:
                r = rs[q_idx]
                ans[q_idx] += fen_sum.range_sm(0, r+1) + fen_cnt.range_sm(r + 1, m+1) * (r + 1)
    for x in ans:
        print(x)
    return


if __name__ == "__main__":
    t_ = sint()
    for _ in range(t_):
        cf2002A()
