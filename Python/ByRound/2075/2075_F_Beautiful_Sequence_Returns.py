# Problem: CF 2075 F - Beautiful Sequence Returns
# https://codeforces.com/contest/2075/problem/F

"""
F. Beautiful Sequence Returns

Purpose:
This code finds the length of the longest beautiful subsequence in a given array.
A beautiful sequence satisfies:
1. Every element (except first) has a smaller element to its left.
2. Every element (except last) has a larger element to its right.

Approach:
- Uses a segment tree with range updates and queries to maintain count of valid elements.
- Preprocesses "bottom-left" indices to identify key elements.
- Processes elements in descending order while maintaining a sliding window.
- Efficiently tracks maximum value encountered for optimization.

Algorithms/Techniques:
- Segment Tree with Lazy Propagation
- Binary Search (bisect_right)
- Sliding Window Technique

Time Complexity: O(n log n) per test case due to sorting, binary search, and segment tree operations.
Space Complexity: O(n) for the segment tree, arrays, and auxiliary data structures.
"""

from bisect import bisect_right


class RURQ:
    def __init__(self, ln):
        self._sz = ln
        self.cache = [0] * ln
        self.data = [0] * (ln * 2)

    def _conv_index(self, i: int | None, is_r: bool = False) -> int:
        if i is None:
            i = self._sz if is_r else 0
        elif i < 0:
            i += self._sz
        return i + self._sz

    def _push1(self, i: int):
        if (val := self.cache[i]) == 0:
            return
        self.cache[i] = 0
        self.data[l := i * 2] += val
        self.data[r := l + 1] += val
        if l < self._sz:
            self.cache[l] += val
            self.cache[r] += val

    def _push(self, i: int):
        for s in reversed(range(1, i.bit_length())):
            self._push1(i >> s)

    def _pull(self, i: int):
        while i := i // 2:
            self.data[i] = max(self.data[2 * i], self.data[2 * i + 1]) + self.cache[i]

    def update(self, l: int | None, r: int | None, val: int):
        l = l0 = self._conv_index(l)
        r = r0 = self._conv_index(r, True)
        if l >= r:
            return
        while l < r:
            if l % 2:
                self.data[l] += val
                if l < self._sz:
                    self.cache[l] += val
                l += 1
            if r % 2:
                r -= 1
                self.data[r] += val
                if r < self._sz:
                    self.cache[r] += val
            l //= 2
            r //= 2
        self._pull(l0)
        self._pull(r0 - 1)

    def query(self, l: int | None, r: int | None) -> int:
        l, r = self._conv_index(l), self._conv_index(r, True)
        if l >= r:
            return 0
        self._push(l)
        self._push(r - 1)
        res = 0
        while l < r:
            if l % 2:
                res = max(res, self.data[l])
                l += 1
            if r % 2:
                r -= 1
                res = max(res, self.data[r])
            l //= 2
            r //= 2
        return res


def solve():
    N = read_int()
    y = list(read_ints())
    bot_lefts = [0]
    for x in range(1, N):
        if y[x] < y[bot_lefts[-1]]:
            bot_lefts.append(x)
    bot_left_ys_neg = [-y[i] for i in bot_lefts]
    bln = len(bot_lefts)
    containing_bls = []
    xr = 0
    for x in range(N):
        xl = bisect_right(bot_left_ys_neg, -y[x])
        while xr < bln and bot_lefts[xr] < x:
            xr += 1
        containing_bls.append((xl, xr))
    st = RURQ(N)
    x_sort = list(range(N))
    x_sort.sort(key=y.__getitem__)
    ans = 1
    mask = [False] * N
    idx = 0
    cur_max = -1
    for x in reversed(range(N)):
        while idx < N and y[x_ := x_sort[idx]] < y[x]:
            if x_ < x:
                mask[x_] = True
                st.update(*containing_bls[x_], 1)
            idx += 1
        l, r = containing_bls[x]
        if y[x] > cur_max and l < r:
            ans = max(ans, st.data[1] + st.cache[1] + 2)  # Add 2 for current element + count from segment tree
            cur_max = y[x]
        if mask[x]:
            st.update(l, r, -1)
            mask[x] = False
    write_int(ans)


from sys import stdin, stdout
from typing import Callable, Iterable, Iterator, Type, TypeVar

T = TypeVar("T")
srdl = stdin.readline
swrt = stdout.write


def read_ints(int_t: Type[int] = int) -> Iterator[int]:
    """Reads a line as space-separated integers"""
    return map(int_t, srdl().split())


def read_int(int_t: Type[int] = int) -> int:
    """Reads a line as a single integer"""
    return int_t(srdl())


def read_str() -> str:
    """Reads a line as-is"""
    return srdl().strip()


def write_ints(arr: Iterable[int]):
    """Writes a list of integers as a space-separated line"""
    swrt(" ".join(map(str, arr)))
    swrt("\n")


def write_int(val: int):
    """Writes a single integer as a line"""
    swrt(str(val))
    swrt("\n")


def write_str(val: str):
    """Writes a single string as a line"""
    swrt(val)
    swrt("\n")


def prompt(msg: str, prefix: str = "? ", reader: Callable[[], T] = read_str) -> T:
    """Writes a string as a line and reads a line. Flushes output buffer.
    Prepends a default prefix to output."""
    swrt(prefix)
    swrt(msg)
    swrt("\n")
    stdout.flush()
    return reader()


if __name__ == "__main__":
    for _ in range(read_int()):
        solve()



# https://github.com/VaHiX/codeForces/