# Problem: CF 1852 B - Imbalanced Arrays
# https://codeforces.com/contest/1852/problem/B

"""
Algorithm: Construct an imbalanced array based on given count array 'a'
Approach:
1. Sort indices of array 'a' in ascending order of their values
2. Use two pointers (left and right) to assign values to the result array
3. For each step, assign negative values to indices with smaller 'a' values
   and positive values to indices with larger 'a' values
4. Ensure the constraints are met:
   - Each element in result array is between -n and n
   - No two elements sum to zero
   - Each element's count of positive sums equals its corresponding 'a' value

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing indices and result array
"""

import os
import sys
from io import BytesIO, IOBase

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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")

R = lambda: list(map(int, input().split()))
P = lambda x, y="\n": print(x, end=y)
I = lambda: int(input())
YES = "YES"
NO = "NO"


def gcd(a, b):

    rr = 1
    while rr:

        rr = a % b
        a = b
        b = rr
    return a


def solve():
    m = int(input())
    e = list(map(int, input().split()))
    s = list(range(m))

    s.sort(key=lambda i: e[i])

    l, o = 0, m - 1
    n = 0
    aNs = [0] * m
    for i in range(m, 0, -1):
        if e[s[l]] - n == 0:
            aNs[s[l]] = -i
            l += 1
        elif e[s[o]] - n == i:
            aNs[s[o]] = i
            n += 1
            o -= 1
        else:
            print("NO")
            return
    print("YES")
    print(*aNs)


for _ in range(I()):
    n = I()
    a = R()
    f = l = m = 0
    b = list(range(n))
    b.sort(key=lambda x: a[x])  # Sort indices by their corresponding 'a' values
    r = n - 1  # Right pointer
    c = [0] * n  # Result array
    for i in range(n, 0, -1):  # Start from largest value
        # If current smallest a value equals remaining count
        if a[b[l]] - m == 0:
            c[b[l]] = -i  # Assign negative value
            l += 1  # Move left pointer
        # If current largest a value equals remaining count
        elif a[b[r]] - m == i:
            c[b[r]] = i  # Assign positive value
            m += 1  # Increment count
            r -= 1  # Move right pointer
        else:
            print("NO")  # Impossible to construct
            f = 1
            break
    if not f:
        print("YES")
        print(*c)  # Print the constructed array


# https://github.com/VaHiX/CodeForces/