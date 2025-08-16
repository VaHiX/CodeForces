# Contest 2126, Problem G2: Big Wins! (hard version)
# URL: https://codeforces.com/contest/2126/problem/G2

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


def I():
    return map(int, input().split())


class SortedList:
    def __init__(self, iterable=None, _load=200):
        if iterable is None:
            iterable = []
        values = sorted(iterable)
        self._len = _len = len(values)
        self._load = _load
        self._lists = _lists = [values[i:i + _load]
                                for i in range(0, _len, _load)]
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
            raise ValueError('{0!r} not in list'.format(value))

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
        return (value for _list in reversed(self._lists)
                for value in reversed(_list))

    def __repr__(self):
        return f'SortedList({list(self)})'


class UnionFind:
    __slots__ = ['parents', 'sizes', 'id', 'cnt', 'val']

    def __init__(self, n: int):
        self.parents = list(range(n + 1)) + [-1]
        self.sizes = [1] * (n + 2)
        self.val = [n + 1] * (n + 2)

    def find(self, x: int) -> int:
        cur = x
        while cur != self.parents[cur]:
            cur = self.parents[cur]
        while self.parents[x] != cur:
            y = self.parents[x]
            self.parents[x] = cur
            x = y
        return cur

    def same(self, u, v):
        return self.find(u) == self.find(v)

    # y合并到x上
    def union(self, x: int, y: int) -> bool:
        x, y = self.find(x), self.find(y)
        if x == y:
            return False
        # 若要维护区间则不加启发合并(会打乱合并逻辑), 这里就是 y -> x 合并
        self.parents[y] = x
        self.sizes[x] += self.sizes[y]
        # 维护块中最小值
        self.val[x] = self.val[y] if self.val[y] < self.val[x] else self.val[x]
        return True

    def get(self, x):
        return self.val[self.find(x)]


# 不要用Counter, set,!!!!!!!!!!!!!!!!!!!!!!!!!
# 用default-dict(int)时要^rd !!!!!!!!!!!!!!!!!!!
# dij 要记录状态!!!!!!!!
def sol():
    n = int(input())
    a = list(I())
    fl = UnionFind(n)
    fr = UnionFind(n)
    for i in range(n):
        a[i] -= 1
        fl.val[i] = fr.val[i] = a[i]
    h = [0] * n
    p = [0] * n

    # 计数排序
    for x in a:
        h[x] += 1
    for i in range(1, n):
        h[i] += h[i - 1]
    for i in range(n):
        x = a[i]
        h[x] -= 1
        p[h[x]] = i

    ans = 0
    # 枚举med, 维护mi
    for i in p[::-1]:
        # 由于对于枚举到的 med = a[i], 若med不在某个块内(区间), 则说明它波及的范围[i - 1, i, i + 1]
        # 若med在某个块内(区间), 则说明它波及的范围为, 该块大小 + 2, (左右两种情况)
        # 所以我们要合并两次
        # 由于我们是从大到小枚举med, 所以对于当前 med, 不在块内的其他数都 <= med
        for _ in range(2):
            x = fl.find(i + 1)
            if x:
                fl.union(x - 1, x)
            x = fr.find(i - 1)
            if x < n:
                fr.union(x + 1, x)
        mi = min(fl.get(i), fr.get(i))
        ans = max(ans, a[i] - mi)
    print(ans)


T = int(input())


def main():
    for i in range(T):
        sol()


main()
