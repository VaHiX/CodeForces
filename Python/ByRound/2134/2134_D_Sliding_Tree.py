# Contest 2134, Problem D: Sliding Tree
# URL: https://codeforces.com/contest/2134/problem/D

import math
import os
import random
import sys
from typing import *
from collections import defaultdict, Counter, deque
from functools import cache, reduce
from itertools import pairwise, combinations, permutations, groupby, accumulate
from bisect import bisect_left, bisect_right, insort_left, insort_right
from heapq import *
from math import gcd, lcm, isqrt
from operator import add, sub, mul, floordiv, truediv, and_, or_, xor

from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
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

    return wrappedfunc


input = sys.stdin.readline
output = lambda x: sys.stdout.write(str(x) + "\n")
outputL = lambda x: sys.stdout.write(" ".join(map(str, x)) + "\n")

rd = random.getrandbits(32)


def I(e=int):
    return map(e, input().split())


class SortedList:
    def __init__(self, iterable=None, _load=200):
        if iterable is None:
            iterable = []
        values = sorted(iterable)
        self._len = _len = len(values)
        self._load = _load
        self._lists = _lists = [values[i : i + _load] for i in range(0, _len, _load)]
        self._list_lens = [len(_list) for _list in _lists]
        self._min_s = [_list[0] for _list in _lists]
        self._fen_tree = []
        self._rebuild = True

    def _fen_build(self):
        self._fen_tree[:] = self._list_lens
        _fen_tree = self._fen_tree
        for i in range(len(_fen_tree)):
            if i | i + 1 < len(_fen_tree):
                _fen_tree[i | i + 1] += _fen_tree[i]
        self._rebuild = False

    def _fen_update(self, index, value):
        if not self._rebuild:
            _fen_tree = self._fen_tree
            while index < len(_fen_tree):
                _fen_tree[index] += value
                index |= index + 1

    def _fen_query(self, end):
        if self._rebuild:
            self._fen_build()

        _fen_tree = self._fen_tree
        x = 0
        while end:
            x += _fen_tree[end - 1]
            end &= end - 1
        return x

    def _fen_findkth(self, k):
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
        _lists = self._lists
        _mins = self._min_s
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
        if not self._len:
            return 0, 0

        _lists = self._lists
        _mins = self._min_s

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
        if not self._len:
            return 0, 0

        _lists = self._lists
        _mins = self._min_s

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
        _load = self._load
        _lists = self._lists
        _mins = self._min_s
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
        _lists = self._lists
        if _lists:
            pos, idx = self._loc_right(value)
            if idx and _lists[pos][idx - 1] == value:
                self._delete(pos, idx - 1)

    def remove(self, value):
        _len = self._len
        self.discard(value)
        if _len == self._len:
            raise ValueError("{0!r} not in list".format(value))

    def pop(self, index=-1):
        pos, idx = self._fen_findkth(self._len + index if index < 0 else index)
        value = self._lists[pos][idx]
        self._delete(pos, idx)
        return value

    def bisect_left(self, value):
        pos, idx = self._loc_left(value)
        return self._fen_query(pos) + idx

    def bisect_right(self, value):
        pos, idx = self._loc_right(value)
        return self._fen_query(pos) + idx

    def count(self, value):
        return self.bisect_right(value) - self.bisect_left(value)

    def __len__(self):
        return self._len

    def __getitem__(self, index):
        pos, idx = self._fen_findkth(self._len + index if index < 0 else index)
        return self._lists[pos][idx]

    def __delitem__(self, index):
        pos, idx = self._fen_findkth(self._len + index if index < 0 else index)
        self._delete(pos, idx)

    def __contains__(self, value):
        _lists = self._lists
        if _lists:
            pos, idx = self._loc_left(value)
            return idx < len(_lists[pos]) and _lists[pos][idx] == value
        return False

    def __iter__(self):
        return (value for _list in self._lists for value in _list)

    def __reversed__(self):
        return (value for _list in reversed(self._lists) for value in reversed(_list))

    def __repr__(self):
        return f"SortedList({list(self)})"


inf = int(1e18)


def func(g):
    n = len(g)
    rt = 0
    dis = [0] * n
    fa = [-1] * n

    def bfs(x):
        st = [(x, -1)]
        dis[x] = 0
        t = x
        while st:
            u, p = st.pop()
            for v in g[u]:
                if v == p:
                    continue
                dis[v] = dis[u] + 1
                if dis[v] > dis[t]:
                    t = v
                fa[v] = u
                st.append((v, u))
        return t

    a = bfs(rt)
    b = bfs(a)
    L = dis[b]
    return L, a, b, fa


# 不要用Counter, set,!!!!!!!!!!!!!!!!!!!!!!!!!
# 用default-dict(int)时要^rd !!!!!!!!!!!!!!!!!!!
# dij 要记录状态!!!!!!!!
def sol():
    n = int(input())
    g = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = I()
        u -= 1
        v -= 1
        g[u].append(v)
        g[v].append(u)
    L, a, b, fa = func(g)
    if L == n - 1:
        print(-1)
        return
    last = -1
    u = b
    while len(g[u]) <= 2:
        last = u
        u = fa[u]
    for v in g[u]:
        if v != fa[u] and v != last:
            print(last + 1, u + 1, v + 1)
            return


T = int(input())


def main():
    for i in range(T):
        sol()


main()
