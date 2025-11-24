# Problem: CF 1808 D - Petya, Petya, Petr, and Palindromes
# https://codeforces.com/contest/1808/problem/D

"""
Problem: Petya, Petya, Petr, and Palindromes

This problem involves calculating the "palindromicity" of all subarrays of a given length k.
Palindromicity is the minimum number of elements that need to be replaced to make a sequence palindromic.

Algorithm:
- Use a sliding window approach with two counters (even_cnt and odd_cnt) to track frequency of elements at even and odd indices.
- For each subarray of length k, compute palindromicity by comparing pairs from the center outward.
- The key insight is that for a palindrome, elements at symmetric positions must be equal.
- For odd-length arrays, the middle element doesn't need to be matched and contributes 0 to palindromicity.
- Use counters to efficiently calculate how many mismatches exist for each element.

Time Complexity: O(n * k)
Space Complexity: O(n)

This solution uses a two-pointer sliding window approach where we maintain counters for even and odd indexed elements.
"""

import os
import sys
from collections import Counter
from io import BytesIO, IOBase


def main():
    n, k = map(int, input().split())
    a = [int(ai) for ai in input().split()]

    start, end = 0, 0
    even_cnt, odd_cnt = Counter(), Counter()

    sol = 0
    for i in range(n):
        # Early breaking condition based on window size
        if i >= min(i + k, n) - k + k // 2:
            break

        # Update the start pointer for the current window
        new_start = 2 * max(0, (i + 2) - (k // 2) - 1) + k - i - 1
        # Adjust counters for elements going out of window from the left
        for j in range(start, new_start):
            if j % 2:
                odd_cnt[a[j]] -= 1
            else:
                even_cnt[a[j]] -= 1
        # Adjust counters for elements entering window from the left
        for j in range(new_start, start):
            if j % 2:
                odd_cnt[a[j]] += 1
            else:
                even_cnt[a[j]] += 1
        start = new_start

        # Update the end pointer for the current window
        new_end = min(i + k, n) - (i - (min(i + k, n) - k))
        # Adjust counters for elements entering window from the right
        for j in range(end, new_end):
            if j % 2:
                odd_cnt[a[j]] += 1
            else:
                even_cnt[a[j]] += 1
        # Adjust counters for elements going out of window from the right
        for j in range(new_end, end):
            if j % 2:
                odd_cnt[a[j]] -= 1
            else:
                even_cnt[a[j]] -= 1
        end = new_end

        # Calculate palindromicity for current window
        if i % 2:
            # If i is odd, use odd counter to avoid double-counting
            sol += (end - start) // 2 + (start % 2 == (end - start) % 2) - odd_cnt[a[i]]
        else:
            # If i is even, use even counter
            sol += (
                (end - start) // 2 + (start % 2 != (end - start) % 2) - even_cnt[a[i]]
            )

    print(sol)


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