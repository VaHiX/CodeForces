# Problem: CF 1805 F1 - Survival of the Weakest (easy version)
# https://codeforces.com/contest/1805/problem/F1

"""
Algorithm: Survival of the Weakest (easy version)
Purpose: This code solves a problem where we repeatedly compute the smallest sums of pairs from an array until only one element remains.
Approach:
- Repeatedly find the smallest n-1 pairwise sums using a heap-based approach
- Use a clever encoding technique to track indices efficiently
- Keep track of excess values that accumulate during the transformation
- Apply modulo arithmetic to handle large numbers
Time Complexity: O(n^2 * log n) where n is the size of the input array, due to heap operations and repeated pair processing
Space Complexity: O(n) for the arrays and heap structures used
"""

from __future__ import division, print_function

import os
import sys
from io import BytesIO, IOBase
from random import randrange

if sys.version_info[0] < 3:
    from __builtin__ import xrange as range

from bisect import bisect_left, bisect_right
from heapq import heappop, heappush
from math import log10

M = 1000000007


INF = 9223372036854775807
PI = 3.141592653589793
R = randrange(2, 1 << 32)


def main():
    TestCases = 1

    encode = lambda x, i: (x << 14) | i  # Encode value and index into single integer
    decode = lambda x: (x >> 14, x & ((1 << 14) - 1))  # Decode value and index from single integer
    for _ in range(TestCases):
        n = int(input())
        arr = [int(i) for i in input().split()]
        excess = []
        arr.sort()
        nxt = [-1] * n
        while n > 1:
            # Determine number of elements to check for minimum pair
            ii = min([int(n**0.5) + 2, n // 2, n - 1])
            if arr[min(ii + 1, n - 1)] == 0:  # If smallest element is 0, we can short circuit
                excess.extend([0] * (n - 1))
                break

            avg = arr[0]  # Use smallest element as base
            excess.append(avg)  # Record this base to apply later
            arr = [arr[i] - avg for i in range(n)]  # Subtract baseline from all elements
            newarr = []

            pq = []
            # Initialize heap with first few possible sums
            for i in range(min([int(n**0.5) + 2, n // 2, n - 1])):
                heappush(pq, encode(arr[i] + arr[i + 1], i))  # Push sum and index
                nxt[i] = i + 1

            # Extract minimum sums and build new array
            for i in range(n - 1):
                val, idx1 = decode(heappop(pq))  # Get smallest sum and corresponding index
                newarr.append(val)
                nxt[idx1] += 1  # Move index forward for next iteration
                if nxt[idx1] < n:  # Check bounds
                    newval = arr[idx1] + arr[nxt[idx1]]  # Compute next possible sum
                    heappush(pq, encode(newval, idx1))  # Push to heap

            arr = newarr
            n -= 1
        excess.reverse()  # Reverse to process in correct order

        # Compute final answer using accumulated excess values
        ans = arr[0]
        cur = 2
        for i in excess:
            ans += i * cur
            ans %= M
            cur <<= 1  # Left shift to multiply by 2
            while cur >= M:
                cur -= M
        print(ans)


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
    return -1


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

    if sys.version_info[0] < 3:
        sys.stdin, sys.stdout = FastIO(sys.stdin), FastIO(sys.stdout)
    else:
        sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

    input = lambda: sys.stdin.readline().rstrip("\r\n")


if __name__ == "__main__":

    main()


# https://github.com/VaHiX/CodeForces/