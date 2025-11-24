# Problem: CF 2151 G1 - Hidden Single (Version 1)
# https://codeforces.com/contest/2151/problem/G1

# Hidden Single Problem - Interactive Algorithm
# Purpose: Find the unique number in a hidden array of size 2n-1 where all numbers from 1 to n appear twice except one.
# Algorithm: Binary search with querying subsets for each number to determine its presence.
# Time Complexity: O(n * log(n) * log(2n)) - due to binary search and subset queries
# Space Complexity: O(n) - to store auxiliary data structures

import operator
import sys
from functools import reduce
from typing import Any, Callable, Optional

input = sys.stdin.readline
CONSTS = {}
INF = 100000000000
fINF = float("inf")


def csum(__iterable, start=None):
    if start is None:
        return reduce(operator.add, __iterable)
    else:
        return reduce(operator.add, __iterable, start)


def mul(__iterable, start=1):
    return reduce(operator.mul, __iterable, start)


def getPrefixSum(iter: list[Any]) -> list:
    if not iter:
        return []
    result = [iter[0]]
    for x in iter[1:]:
        result.append(x + result[-1])
    return result


def parametricSearch(low: int, high: int, check: Callable[[int], bool]) -> int:
    """Finds maximum integer x that makes check(x) True."""
    l, r = low, high
    while l + 1 < r:
        m = (l + r) // 2
        if check(m):
            l = m
        else:
            r = m - 1
    return r if check(r) else l


def init1D(n: int, default: Any = 0):
    return [default] * n


def init2D(n: int, m: Optional[int] = None, default: Any = 0):
    if m is None:
        m = n
    return [[default] * m for _ in range(n)]


def init3D(n, m: Optional[int] = None, k: Optional[int] = None, default: Any = 0):
    if m is None:
        m = n
    if k is None:
        k = m
    return [[[default] * k for _ in range(m)] for _ in range(n)]


def init4D(
    n,
    m: Optional[int] = None,
    k: Optional[int] = None,
    i: Optional[int] = None,
    default: Any = 0,
):
    if m is None:
        m = n
    if k is None:
        k = m
    if i is None:
        i = k
    return [[[[default] * i for _ in range(k)] for _ in range(m)] for _ in range(n)]


def yes(cond=True, ex: bool = False):
    print("YES" if cond else "NO")
    if ex:
        exit()


def no(cond=True, ex: bool = False):
    yes(not cond, ex)


def debug(*args, **kwargs):
    if DEBUG:
        print(*args, **kwargs)


def ask(x, *l):
    l = list(l)
    l.sort()
    print("?", x, len(l), *l)
    sys.stdout.flush()
    i = int(input())
    if i == -1:
        exit()
    return bool(i)


def answer(y):
    print("!", y)
    sys.stdout.flush()


DEBUG = False
if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        (n,) = map(int, input().split())
        l = 1
        r = 2 * n
        v = [None] + [2] * n  # 2 means unknown, 1 means appears in left half, 0 means appears in right half
        while l + 1 < r:
            m = (l + r) // 2
            a = [i for i in range(1, n + 1) if v[i] > 0]  # Active numbers only
            left = [None] + [False] * n  # left[x] = True if x appears in the range [l, m)
            right = [None] + [False] * n  # right[x] = True if x appears in the range [m, r)
            for x in a:
                al = ask(x, *range(l, m))  # Query if number x appears in left half
                left[x] = al
                if v[x] == 1 or not al:  # If x known to be in left OR not found in left
                    right[x] = not al  # then it must appear in the right half (complement)
                else:
                    right[x] = ask(x, *range(m, r))  # Check in right half only

            # Group numbers into "left", "right", or undetermined sets
            both = []  # Set of numbers appearing in both halves
            left_only = []  # Set of numbers appearing only in the left half
            right_only = []  # Set of numbers appearing only in the right half

            for x in a:
                if left[x] and right[x]:
                    both.append(x)
                elif left[x]:
                    left_only.append(x)
                elif right[x]:
                    right_only.append(x)

            cl = m-l
            cr = r-m
            cl -= len(both) - len([x for x in left_only if v[x]==1])
            cr -= len(both) - len([x for x in right_only if v[x]==1])
            # Update state based on new information
            if cl % 2 == 1:
                r = m
                for x in both:
                    v[x] = 1
                for x in right_only:
                    v[x] = 0 # Appears in right half
            else:
                l = m
                for x in both:
                    v[x] = 1
                for x in left_only:
                    v[x] = 0  # Appears in left half
            debug(*v)
        answer([i for i in range(1, n+1) if v[i]==2][0])

# https://github.com/VaHiX/CodeForces/