# Contest 2047, Problem E: Adventurers
# URL: https://codeforces.com/contest/2047/problem/E

import sys
import re

# region fastio
from collections import Counter, deque
from heapq import heappop, heappush
from math import inf, gcd, sqrt, log2, factorial
from random import getrandbits
from types import GeneratorType
from typing import List
from collections import defaultdict
from bisect import bisect_left, bisect_right
from itertools import accumulate, permutations

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


MOD = 10**9 + 7


#
# mx = 2 * 10 ** 5
# f = [0] * MX
# f[0] = f[1] = 1
# for i in range(2, MX):
#     f[i] = f[i - 1] + 2 * (i - 1) * f[i - 2]
#     f[i] %= MOD
# 阶乘
# fac = [1] * (mx + 1)
# for i in range(1, mx + 1):
#     fac[i] = fac[i - 1] * i % MOD
# # 逆元
# ifac = [0] * (mx + 1)
# ifac[mx] = pow(fac[mx], MOD - 2, MOD)
# for i in range(mx, 0, -1):
#     ifac[i - 1] = ifac[i] * i % MOD
#
#
# # 组合数
# def comb(n: int, m: int, MOD=MOD) -> int:
#     if m < 0 or m > n:
#         return 0
#     return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD


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


# endregion fastio


# MOD = 998_244_353
# MOD = 10 ** 9 + 7
# DIR4 = ((-1, 0), (0, 1), (1, 0), (0, -1)) #URDL
# DIR8 = ((-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1))
def kmp(pattern: str) -> List[int]:
    m = len(pattern)
    pi = [0] * m
    c = 0
    for i in range(1, m):
        v = pattern[i]
        while c and pattern[c] != v:
            c = pi[c - 1]
        if pattern[c] == v:
            c += 1
        pi[i] = c

    return pi


class TARJAN:
    def __init__(self, n: int, g: List[List[int]]):
        # 记录结点的当前时间戳和最早时间戳,dfn 严格递增，low 严格非降
        self.dfn = [-1] * n
        self.low = [-1] * n
        self.bridge = []  # 桥
        self.flag = [False] * n  # 是否是割点
        self.g = g
        self.n = n

    def find_SCC(self):
        SCC, S, P = [], [], []
        depth = [0] * self.n

        stack = list(range(self.n))
        while stack:
            node = stack.pop()
            if node < 0:
                d = depth[~node] - 1
                if P[-1] > d:
                    SCC.append(S[d:])
                    del S[d:], P[-1]
                    for node in SCC[-1]:
                        depth[node] = -1
            elif depth[node] > 0:
                while P[-1] > depth[node]:
                    P.pop()
            elif depth[node] == 0:
                S.append(node)
                P.append(len(S))
                depth[node] = len(S)
                stack.append(~node)
                stack.extend(self.g[node])
        return SCC[::-1]

    @bootstrap
    def tarjan(self, o: int, f: int, t: int) -> None:
        self.dfn[o] = t
        self.low[o] = t
        c = 0
        for child in self.g[o]:
            if child != f:
                if self.dfn[child] == -1:
                    c += 1
                    yield self.tarjan(child, o, t + 1)
                    self.low[o] = min(self.low[o], self.low[child])
                    # 找到割点, 非root,有儿子
                    if self.dfn[o] <= self.low[child] and f != -1 and not self.flag[o]:
                        self.flag[o] = True
                    # 找到桥
                    if self.dfn[o] < self.low[child]:
                        self.bridge.append([o, child])
                else:
                    self.low[o] = min(self.low[o], self.dfn[child])
        # root点 儿子数大于等于2
        if f == -1 and c >= 2 and not self.flag[o]:
            self.flag[o] = True
        yield


# ans = [0] * (5 * 10 ** 6 + 1)
# for i in range(2, 5 * 10 ** 6 + 1):
#     if ans[i] == 0:
#         for j in range(i, 5 * 10 ** 6 + 1, i):
#             v = j
#             while v % i == 0:
#                 v //= i
#                 ans[j] += 1
#
# for i in range(2, 5 * 10 ** 6 + 1):
#     ans[i] += ans[i - 1]
# 标准并查集
class UnionFind:
    def __init__(self, n):
        self.root = [i for i in range(n)]
        self.size = [1] * n
        self.part = n

    def find(self, x):
        if x != self.root[x]:
            # 在查询的时候合并到顺带直接根节点
            root_x = self.find(self.root[x])
            self.root[x] = root_x
            return root_x
        return x

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if root_x < root_y:
            root_x, root_y = root_y, root_x
        self.root[root_x] = root_y
        self.size[root_y] += self.size[root_x]
        # 将非根节点的秩赋0
        self.size[root_x] = 0
        self.part -= 1
        return True

    def is_connected(self, x, y):
        return self.find(x) == self.find(y)

    def get_root_part(self):
        # 获取每个根节点对应的组
        part = defaultdict(list)
        n = len(self.root)
        for i in range(n):
            part[self.find(i)].append(i)
        return part

    def get_root_size(self):
        # 获取每个根节点对应的组大小
        size = defaultdict(int)
        n = len(self.root)
        for i in range(n):
            size[self.find(i)] = self.size[self.find(i)]
        return size


class SparseTable:
    def __init__(self, nums: list, op) -> None:
        self.pow2 = [1]
        for _ in range(20):
            self.pow2.append(2 * self.pow2[-1])
        self.op = op
        self.st = []
        s, l = nums, 1
        self.st.append(s)
        while l * 2 <= len(nums):
            ns = []
            for i in range(len(s) - l):
                ns.append(gcd(s[i], s[i + l]))
            s = ns
            self.st.append(s)
            l *= 2

    def query(self, l: int, r: int):
        # s = log2(r - l + 1)
        s = len(bin(r - l + 1)) - 3
        res = self.op(self.st[s][l], self.st[s][r - self.pow2[s] + 1])
        return res


def phi(x: int) -> int:
    res = x
    d = 2
    while d * d <= x:
        if x % d == 0:
            res -= res // d
            while x % d == 0:
                x //= d
        if x == 1:
            break
        d += 1
    if x > 1:
        res -= res // x
    return res


class PrimeTable:
    def __init__(self, n: int) -> None:
        self.n = n
        self.primes = []
        self.max_div = list(range(n + 1))
        self.max_div[1] = 1
        self.phi = list(range(n + 1))

        for i in range(2, n + 1):
            if self.max_div[i] == i:
                self.primes.append(i)
                for j in range(i, n + 1, i):
                    self.max_div[j] = i
                    self.phi[j] = self.phi[j] // i * (i - 1)

    def is_prime(self, x: int):
        if x < 2:
            return False
        if x <= self.n:
            return self.max_div[x] == x
        for p in self.primes:
            if p * p > x:
                break
            if x % p == 0:
                return False
        return True

    def prime_factorization(self, x: int):
        if x > self.n:
            for p in self.primes:
                if p * p > x:
                    break
                if x <= self.n:
                    break
                if x % p == 0:
                    cnt = 0
                    while x % p == 0:
                        cnt += 1
                        x //= p
                    yield p, cnt
        while 1 < x <= self.n:
            p, cnt = self.max_div[x], 0
            while x % p == 0:
                cnt += 1
                x //= p
            yield p, cnt
        if x >= self.n and x > 1:
            yield x, 1

    def get_factors(self, x: int):
        factors = [1]
        for p, b in self.prime_factorization(x):
            n = len(factors)
            for j in range(1, b + 1):
                for d in factors[:n]:
                    factors.append(d * (p**j))
        return factors


class Factorial:
    def __init__(self, N, mod) -> None:
        N += 1
        self.mod = mod
        self.f = [1 for _ in range(N)]
        self.g = [1 for _ in range(N)]
        for i in range(1, N):
            self.f[i] = self.f[i - 1] * i % self.mod
        self.g[-1] = pow(self.f[-1], mod - 2, mod)
        for i in range(N - 2, -1, -1):
            self.g[i] = self.g[i + 1] * (i + 1) % self.mod

    def fac(self, n):
        return self.f[n]

    def fac_inv(self, n):
        return self.g[n]

    def combi(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[m] % self.mod * self.g[n - m] % self.mod

    def permu(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[n - m] % self.mod

    def catalan(self, n):
        return (self.combi(2 * n, n) - self.combi(2 * n, n - 1)) % self.mod

    def inv(self, n):
        return self.f[n - 1] * self.g[n] % self.mod


def query(x, y) -> None:
    print("?", x, y, flush=True)


def answer(x) -> None:
    print("!", *x, flush=True)


class SortedList:
    def __init__(self, iterable=None, _load=200):
        """Initialize sorted list instance."""
        if iterable is None:
            iterable = []
        values = sorted(iterable)
        self._len = _len = len(values)
        self._load = _load
        self._lists = _lists = [values[i : i + _load] for i in range(0, _len, _load)]
        self._list_lens = [len(_list) for _list in _lists]
        self._mins = [_list[0] for _list in _lists]
        self._fen_tree = []
        self._rebuild = True

    def _fen_build(self):
        """Build a fenwick tree instance."""
        self._fen_tree[:] = self._list_lens
        _fen_tree = self._fen_tree
        for i in range(len(_fen_tree)):
            if i | i + 1 < len(_fen_tree):
                _fen_tree[i | i + 1] += _fen_tree[i]
        self._rebuild = False

    def _fen_update(self, index, value):
        """Update `fen_tree[index] += value`."""
        if not self._rebuild:
            _fen_tree = self._fen_tree
            while index < len(_fen_tree):
                _fen_tree[index] += value
                index |= index + 1

    def _fen_query(self, end):
        """Return `sum(_fen_tree[:end])`."""
        if self._rebuild:
            self._fen_build()

        _fen_tree = self._fen_tree
        x = 0
        while end:
            x += _fen_tree[end - 1]
            end &= end - 1
        return x

    def _fen_findkth(self, k):
        """Return a pair of (the largest `idx` such that `sum(_fen_tree[:idx]) <= k`, `k - sum(_fen_tree[:idx])`)."""
        _list_lens = self._list_lens
        if k < _list_lens[0]:
            return 0, k
        if k >= self._len - _list_lens[-1]:
            return len(_list_lens) - 1, k + _list_lens[-1] - self._len
        if self._rebuild:
            self._fen_build()

        _fen_tree = self._fen_tree
        idx = -1
        for d in reversed(range(len(_fen_tree).bit_length())):
            right_idx = idx + (1 << d)
            if right_idx < len(_fen_tree) and k >= _fen_tree[right_idx]:
                idx = right_idx
                k -= _fen_tree[idx]
        return idx + 1, k

    def _delete(self, pos, idx):
        """Delete value at the given `(pos, idx)`."""
        _lists = self._lists
        _mins = self._mins
        _list_lens = self._list_lens

        self._len -= 1
        self._fen_update(pos, -1)
        del _lists[pos][idx]
        _list_lens[pos] -= 1

        if _list_lens[pos]:
            _mins[pos] = _lists[pos][0]
        else:
            del _lists[pos]
            del _list_lens[pos]
            del _mins[pos]
            self._rebuild = True

    def _loc_left(self, value):
        """Return an index pair that corresponds to the first position of `value` in the sorted list."""
        if not self._len:
            return 0, 0

        _lists = self._lists
        _mins = self._mins

        lo, pos = -1, len(_lists) - 1
        while lo + 1 < pos:
            mi = (lo + pos) >> 1
            if value <= _mins[mi]:
                pos = mi
            else:
                lo = mi

        if pos and value <= _lists[pos - 1][-1]:
            pos -= 1

        _list = _lists[pos]
        lo, idx = -1, len(_list)
        while lo + 1 < idx:
            mi = (lo + idx) >> 1
            if value <= _list[mi]:
                idx = mi
            else:
                lo = mi

        return pos, idx

    def _loc_right(self, value):
        """Return an index pair that corresponds to the last position of `value` in the sorted list."""
        if not self._len:
            return 0, 0

        _lists = self._lists
        _mins = self._mins

        pos, hi = 0, len(_lists)
        while pos + 1 < hi:
            mi = (pos + hi) >> 1
            if value < _mins[mi]:
                hi = mi
            else:
                pos = mi

        _list = _lists[pos]
        lo, idx = -1, len(_list)
        while lo + 1 < idx:
            mi = (lo + idx) >> 1
            if value < _list[mi]:
                idx = mi
            else:
                lo = mi

        return pos, idx

    def add(self, value):
        """Add `value` to sorted list."""
        _load = self._load
        _lists = self._lists
        _mins = self._mins
        _list_lens = self._list_lens

        self._len += 1
        if _lists:
            pos, idx = self._loc_right(value)
            self._fen_update(pos, 1)
            _list = _lists[pos]
            _list.insert(idx, value)
            _list_lens[pos] += 1
            _mins[pos] = _list[0]
            if _load + _load < len(_list):
                _lists.insert(pos + 1, _list[_load:])
                _list_lens.insert(pos + 1, len(_list) - _load)
                _mins.insert(pos + 1, _list[_load])
                _list_lens[pos] = _load
                del _list[_load:]
                self._rebuild = True
        else:
            _lists.append([value])
            _mins.append(value)
            _list_lens.append(1)
            self._rebuild = True

    def discard(self, value):
        """Remove `value` from sorted list if it is a member."""
        _lists = self._lists
        if _lists:
            pos, idx = self._loc_right(value)
            if idx and _lists[pos][idx - 1] == value:
                self._delete(pos, idx - 1)

    def remove(self, value):
        """Remove `value` from sorted list; `value` must be a member."""
        _len = self._len
        self.discard(value)
        if _len == self._len:
            raise ValueError("{0!r} not in list".format(value))

    def pop(self, index=-1):
        """Remove and return value at `index` in sorted list."""
        pos, idx = self._fen_findkth(self._len + index if index < 0 else index)
        value = self._lists[pos][idx]
        self._delete(pos, idx)
        return value

    def bisect_left(self, value):
        """Return the first index to insert `value` in the sorted list."""
        pos, idx = self._loc_left(value)
        return self._fen_query(pos) + idx

    def bisect_right(self, value):
        """Return the last index to insert `value` in the sorted list."""
        pos, idx = self._loc_right(value)
        return self._fen_query(pos) + idx

    def count(self, value):
        """Return number of occurrences of `value` in the sorted list."""
        return self.bisect_right(value) - self.bisect_left(value)

    def __len__(self):
        """Return the size of the sorted list."""
        return self._len

    def __getitem__(self, index):
        """Lookup value at `index` in sorted list."""
        pos, idx = self._fen_findkth(self._len + index if index < 0 else index)
        return self._lists[pos][idx]

    def __delitem__(self, index):
        """Remove value at `index` from sorted list."""
        pos, idx = self._fen_findkth(self._len + index if index < 0 else index)
        self._delete(pos, idx)

    def __contains__(self, value):
        """Return true if `value` is an element of the sorted list."""
        _lists = self._lists
        if _lists:
            pos, idx = self._loc_left(value)
            return idx < len(_lists[pos]) and _lists[pos][idx] == value
        return False

    def __iter__(self):
        """Return an iterator over the sorted list."""
        return (value for _list in self._lists for value in _list)

    def __reversed__(self):
        """Return a reverse iterator over the sorted list."""
        return (value for _list in reversed(self._lists) for value in reversed(_list))

    def __repr__(self):
        """Return string representation of sorted list."""
        return "SortedList({0})".format(list(self))


def cf1572A():
    n = sint()
    a = []
    for _ in range(n):
        u, v = mint()
        a.append((u, v))
    a.sort()
    dt = defaultdict(list)
    sl = SortedList()
    sr = SortedList()
    for x, y in a:
        dt[x].append(y)
        sr.add(y)

    ans = 0
    pos = (0, 0)
    for x in sorted(dt.keys()):
        for y in dt[x]:
            sl.add(y)
            sr.remove(y)
        if (ans + 1) * 2 > len(sr):
            break
        while max(sl[ans], sr[ans]) < min(sl[-ans - 1], sr[-ans - 1]):
            ans += 1
            pos = (x + 1, min(sl[-ans], sr[-ans]))
    print(ans)
    print(*pos)
    # n = sint()
    # a = []
    # st = set()
    # for _ in range(n):
    #     u, v = mint()
    #     a.append((u, v))
    #     st.add(v)
    # a.sort(key=lambda p: p[1])
    # res = list(st)
    # res.sort()
    # m = len(res)
    # x0 = 0
    # y0 = 0
    # # 按y值排好序了
    # # 二分加扫描线
    # def check(k: int) -> bool:
    #     nonlocal x0
    #     nonlocal y0
    #     if k == 0:
    #         return True
    #     dt1 = defaultdict()
    #     st1 = SortedList()
    #     h = getrandbits(30)
    #     c1 = 0
    #     ll = 0
    #     for x in res:
    #         while ll < n and a[ll][1] < x:
    #             c1 += 1
    #             st1.add(a[ll][0])
    #             ll += 1
    #         if c1 < 2 * k:
    #             continue
    #         v1 = st1[k - 1]
    #         # idl = st1.bisect_left(v1 + 1)
    #         # if c1 - idl < k:
    #         #     continue
    #         v2 = st1[len(st1) - k]
    #         if v1 + 1 > v2:
    #             continue
    #         dt1[x ^ h] = (v1 + 1, v2)
    #
    #     dt2 = defaultdict()
    #     st1 = SortedList()
    #     c2 = 0
    #     rr = n - 1
    #     for i in range(m - 1, -1, -1):
    #         x = res[i]
    #         while rr >= 0 and a[rr][1] >= x:
    #             c2 += 1
    #             st1.add(a[rr][0])
    #             rr -= 1
    #         if c2 < 2 * k:
    #             continue
    #         v1 = st1[k - 1]
    #         # idl = st2.bisect_left(v1 + 1)
    #         # if c2 - idl < k:
    #         #     continue
    #         v2 = st1[len(st1) - k]
    #         if v1 + 1 > v2:
    #             continue
    #         dt2[x ^ h] = (v1 + 1, v2)
    #     for x in res:
    #         if x ^ h in dt1.keys() and x ^ h in dt2.keys():
    #             l1, r1 = dt1[x ^ h]
    #             l2, r2 = dt2[x ^ h]
    #             if l2 > r1 or l1 > r2:
    #                 continue
    #             y0 = x
    #             if l2 < l1:
    #                 if r2 <= r1:
    #                     x0 = r2
    #                 else:
    #                     x0 = r1
    #             else:
    #                 x0 = l2
    #             return True
    #     return False
    #
    # l = 0
    # r = n // 4
    # while l < r:
    #     mid = (l + r) >> 1
    #     if check(mid):
    #         l = mid + 1
    #     else:
    #         r = mid - 1
    # ans = l if check(l) else l - 1
    # print(ans)
    # print(x0, y0)
    return


if __name__ == "__main__":
    t_ = sint()
    for _ in range(t_):
        cf1572A()
