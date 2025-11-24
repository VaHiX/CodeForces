# Problem: CF 1808 C - Unlucky Numbers
# https://codeforces.com/contest/1808/problem/C

"""
Algorithm: Unlucky Numbers
Approach:
1. For small ranges (<= 100), brute force through all numbers to find the one with maximum luckiness
2. For larger ranges:
   - Find first differing digit position between l and r
   - Trim the numbers to that position and process smaller sub-range
   - Generate candidate numbers by replicating last digits for proper length
   - Check edge cases for original l and r values

Time Complexity: O(log(r)) per test case
Space Complexity: O(log(r)) for string operations and recursion stack
"""

from __future__ import division, print_function

import os
import sys
from io import BytesIO, IOBase
from random import randrange

if sys.version_info[0] < 3:
    from __builtin__ import xrange as range

from bisect import bisect_left, bisect_right
from math import log10

M = 1000000007


INF = 9223372036854775807
PI = 3.141592653589793
R = randrange(2, 1 << 32)


def calc(num):
    return int(max(str(num))) - int(min(str(num)))


def replicateLastDigit(num, n):
    return int(str(num) + str(num)[-1] * (n - len(str(num))))


def firstDifferentDigit(l, r):
    l, r = str(l), str(r)
    for i in range(len(l)):
        if l[i] != r[i]:
            return i


def solve(l, r):
    ans = (calc(r), r)
    if r - l <= 100:
        for i in range(l, r):
            ans = min(ans, (calc(i), i))
        return ans

    idx = firstDifferentDigit(l, r)
    n = len(str(l))

    d = 10 ** (n - idx - 2)
    l1, r1 = l // d, r // d
    diff, num = solve(l1 + 1, r1 - 1)
    num = replicateLastDigit(num, n)
    ans = min(ans, (diff, num))
    num1, num2 = replicateLastDigit(l1, n), replicateLastDigit(r1, n)
    if l <= num1 <= r:
        ans = min(ans, (calc(num1), num1))
    if l <= num2 <= r:
        ans = min(ans, (calc(num2), num2))
    return ans


def main():
    TestCases = 1
    TestCases = int(input())

    for _ in range(TestCases):
        l, r = [int(i) for i in input().split()]
        if len(str(l)) != len(str(r)):
            print("9" * len(str(l)))
            continue

        print(solve(l, r)[1])


abc = "abcdefghijklmnopqrstuvwxyz"
abd = {
    "a": 0,
    "b": 1,
    "c": 2,
    "d": 3,
    "e": 4,
    "f": 5,
    "g": 6,
    "h": 7,
    "i": 8,
    "j": 9,
    "k": 10,
    "l": 11,
    "m": 12,
    "n": 13,
    "o": 14,
    "p": 15,
    "q": 16,
    "r": 17,
    "s": 18,
    "t": 19,
    "u": 20,
    "v": 21,
    "w": 22,
    "x": 23,
    "y": 24,
    "z": 25,
}


def copy2d(lst):
    return [x[:] for x in lst]


def no_of_digits(num):
    return 0 if num <= 0 else int(log10(num)) + 1


def powm(num, power, mod=M):
    return pow(num, power, mod)


def isPowerOfTwo(x):
    return x and (not (x & (x - 1)))


def LSB(num):
    """Returns Least Significant Bit of a number (Rightmost bit) in O(1)"""
    return num & -num


def MSB(num):
    """Returns Most Significant Bit of a number (Leftmost bit) in O(logN)"""
    if num <= 0:
        return 0
    ans = 1
    num >>= 1
    while num:
        num >>= 1
        ans <<= 1
    return ans


LB = bisect_left
UB = bisect_right


def BS(a, x):
    i = bisect_left(a, x)
    if i != len(a) and a[i] == x:
        return i
    else:
        return -1


def gcd(x, y):
    while y:
        x, y = y, x % y
    return x


def lcm(x, y):
    return (x * y) // gcd(x, y)


class Wrapper(int):
    def __init__(self, x):
        int.__init__(x)

    def __hash__(self):
        return super(Wrapper, self).__hash__() ^ R


Int = lambda x: Wrapper(int(x))


class myDict:
    def __init__(self, func=int):

        self.RANDOM = R
        self.default = func
        self.dict = {}

    def __getitem__(self, key):
        myKey = self.RANDOM ^ key
        if myKey not in self.dict:
            self.dict[myKey] = self.default()
        return self.dict[myKey]

    def __setitem__(self, key, item):
        myKey = self.RANDOM ^ key
        self.dict[myKey] = item

    def __contains__(self, key):
        myKey = self.RANDOM ^ key
        return myKey in self.dict

    def __delitem__(self, key):
        myKey = self.RANDOM ^ key
        del self.dict[myKey]

    def keys(self):
        return [self.RANDOM ^ i for i in self.dict]


if not os.path.isdir("C:/users/acer"):
    BUFSIZE = 8192

    class FastIO(IOBase):
        newlines = 0

        def __init__(self, file):
            self._fd = file.fileno()
            self.buffer = BytesIO()
            self.writable = "x" in file.mode or "r" not in file.mode
            self.write = self.buffer.write if self.writable else None

        def read(self):
            while True:
                b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                if not b:
                    break
                ptr = self.buffer.tell()
                self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
            self.newlines = 0
            return self.buffer.read()

        def readline(self):
            while self.newlines == 0:
                b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                self.newlines = b.count(b"\n") + (not b)
                ptr = self.buffer.tell()
                self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
            self.newlines -= 1
            return self.buffer.readline()

        def flush(self):
            if self.writable:
                os.write(self._fd, self.buffer.getvalue())
                self.buffer.truncate(0), self.buffer.seek(0)

    class IOWrapper(IOBase):
        def __init__(self, file):
            self.buffer = FastIO(file)
            self.flush = self.buffer.flush
            self.writable = self.buffer.writable
            self.write = lambda s: self.buffer.write(s.encode("ascii"))
            self.read = lambda: self.buffer.read().decode("ascii")
            self.readline = lambda: self.buffer.readline().decode("ascii")

    def print(*args, **kwargs):
        """Prints the values to a stream, or to sys.stdout by default."""
        sep, file = kwargs.pop("sep", " "), kwargs.pop("file", sys.stdout)
        at_start = True
        for x in args:
            if not at_start:
                file.write(sep)
            file.write(str(x))
            at_start = False
        file.write(kwargs.pop("end", "\n"))
        if kwargs.pop("flush", False):
            file.flush()

    if sys.version_info[0] < 3:
        sys.stdin, sys.stdout = FastIO(sys.stdin), FastIO(sys.stdout)
    else:
        sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

    input = lambda: sys.stdin.readline().rstrip("\r\n")


if __name__ == "__main__":

    main()


# https://github.com/VaHiX/CodeForces/