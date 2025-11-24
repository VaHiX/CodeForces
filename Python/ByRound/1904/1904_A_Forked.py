# Problem: CF 1904 A - Forked!
# https://codeforces.com/contest/1904/problem/A

"""
Algorithm/Technique: 
- The problem is to find the number of positions where a knight can attack both the king and the queen.
- A knight in this modified version moves 'a' tiles in one direction and 'b' tiles in the other, in all 8 possible knight directions.
- For each piece (king and queen), we generate all possible knight moves (8 possible positions).
- Then we find the intersection of these sets of moves to get positions where the knight can attack both pieces.
- We use memoization to avoid recomputing the same cases.

Time Complexity: O(1) per test case, as there are a fixed number of moves (8) for each piece, so the set operations take constant time.
Space Complexity: O(1) for memoization as we only memoize the inputs which are fixed size, and the number of possible unique inputs is bounded.

"""
from __future__ import division, print_function

import os
import sys
from io import BytesIO, IOBase

if sys.version_info[0] < 3:
    from __builtin__ import xrange as range


def main():
    t = int(input())
    memo = {}

    def generate_moves(x, y, a, b):
        # Generate all 8 possible knight moves from position (x, y)
        return {
            (x - a, y + b),  # Move a in x, b in y
            (x + a, y + b),  # Move a in x, b in y
            (x + b, y + a),  # Move b in x, a in y
            (x + b, y - a),  # Move b in x, -a in y
            (x + a, y - b),  # Move a in x, -b in y
            (x - a, y - b),  # Move -a in x, -b in y
            (x - b, y - a),  # Move -b in x, -a in y
            (x - b, y + a),  # Move -b in x, a in y
        }

    for _ in range(t):
        input1 = input().split()
        input2 = input().split()
        input3 = input().split()
        a = int(input1[0])
        b = int(input1[1])
        xk = int(input2[0])
        yk = int(input2[1])
        xq = int(input3[0])
        yq = int(input3[1])
        # Check if we have already computed this case
        if (a, b, xk, yk, xq, yq) in memo:
            common_moves = memo[(a, b, xk, yk, xq, yq)]
        else:
            # Generate all moves possible for the knight from king and queen positions
            moves_knight = generate_moves(xk, yk, a, b)
            moves_queen = generate_moves(xq, yq, a, b)
            # Find common moves (positions where knight attacks both)
            common_moves = len(moves_knight.intersection(moves_queen))
            # Memoize the result
            memo[(a, b, xk, yk, xq, yq)] = common_moves
        print(common_moves)


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