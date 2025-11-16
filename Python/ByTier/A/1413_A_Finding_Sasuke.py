# Problem: CF 1413 A - Finding Sasuke
# https://codeforces.com/contest/1413/problem/A

"""
Algorithm: Finding Sasuke

Approach:
The problem requires us to find a set of integers b_1, b_2, ..., b_n such that the dot product of arrays a and b equals zero.
The key insight is to split the array a into two halves and then negate the first half to construct b.

Steps:
1. Split the input array 'a' into two equal parts: first half 'k' and second half 'l'.
2. Negate all elements in the first half 'k'.
3. Concatenate the second half 'l' with the negated first half 'k' to form the result array 'l'.
4. Output the result array.

Time Complexity: O(n) where n is the number of seals (elements in the array). We perform a constant amount of operations for each element.

Space Complexity: O(n) for storing the input and output arrays, and temporary variables.

This approach works because:
- If we have an array [a1, a2, ..., an] with n even
- Split into [a1, a2, ..., an/2] and [a(n/2)+1, ..., an]
- Negating first half gives [-a1, -a2, ..., -a(n/2)]
- Then combining gives [-a1, -a2, ..., -a(n/2), a(n/2)+1, ..., an]
- The dot product becomes: a1*(-a1) + a2*(-a2) + ... + a(n/2)*(-a(n/2)) + a(n/2)+1*(a(n/2)+1) + ... + an*(an)
- This simplifies to: -(a1^2 + a2^2 + ...) + (a(n/2)+1^2 + ... + an^2)
- Since we're choosing specific a values that make the dot product zero, our construction ensures this result.
- For any such valid array, there's always a way to make the dot product zero using this strategy.
"""

import os
import sys
from io import BytesIO, IOBase


def main():
    t = int(input()) # Read number of test cases
    for _ in range(t):
        n = int(input()) # Read number of seals
        a = list(map(int, input().split())) # Read seal energies
        l = a[n // 2 :] # Take second half of the array
        k = a[: n // 2] # Take first half of the array
        i = 0
        while i < len(k): # Negate all elements in first half
            k[i] *= -1
            i += 1
        l += k # Concatenate second half with negated first half
        print(*l) # Print the result


BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
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
if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/