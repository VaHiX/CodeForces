# Problem: CF 1809 C - Sum on Subarrays
# https://codeforces.com/contest/1809/problem/C

"""
Algorithm/Technique: Greedy Construction
Time Complexity: O(n)
Space Complexity: O(n)

The approach constructs the array greedily by filling positions such that 
we can control the number of positive subarray sums. We use a strategy where 
we place 2s in the beginning to contribute to the count of positive sums, 
and then adjust later elements to ensure that exactly k subarrays have positive sums.
"""

import io
import os
import sys

MOD = 998244353
inf = 1 << 60


def solve():
    n, k = read_int_tuple()

    A = []
    for t in range(1, n + 1):
        if k >= t:  # If we can still allocate 't' positive subarrays
            A.append(2)  # Add 2 to contribute to positive sums
            k -= t       # Reduce the remaining count
        else:
            # If k is less than t, we have to carefully choose the next value
            if A and A[-1] > 0:  # If last element is positive, we need to decrease it
                # This ensures that we don't over-count positive sums
                A.append(-(1 + 2 * (t - k - 1)))
            else:
                # If last is not positive, just add a negative number
                A.append(-1000)
            k = 0  # Stop processing further

    print(*A)


def main():

    T = read_int()
    for t in range(T):
        solve()


BUFSIZE = 8192


class FastIO(io.IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.buffer = io.BytesIO()
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


class IOWrapper(io.IOBase):
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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)


input = lambda: sys.stdin.readline().rstrip("\r\n")


def read_int_list():
    return list(map(int, input().split()))


def read_int_tuple():
    return map(int, input().split())


def read_int():
    return int(input())


read_str = input


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/