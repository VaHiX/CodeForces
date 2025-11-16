# Problem: CF 1827 C - Palindrome Partition
# https://codeforces.com/contest/1827/problem/C

"""
Algorithm: Palindrome Partition
Techniques: Manacher's Algorithm, Union-Find, Dynamic Programming

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(n) for storing auxiliary arrays

This solution uses Manacher's algorithm to efficiently find all palindromic substrings,
then applies Union-Find to merge overlapping palindromes and Dynamic Programming to
count beautiful substrings.
"""

standard_input, packages, output_together = 1, 0, 0
dfs, hashing, read_from_file = 0, 0, 0
de = 1

if 1:

    if standard_input:
        import os
        import sys

        input = lambda: sys.stdin.readline().strip()

        import math

        inf = math.inf

        def I():
            return input()

        def II():
            return int(input())

        def MII():
            return map(int, input().split())

        def LI():
            return list(input().split())

        def LII():
            return list(map(int, input().split()))

        def LFI():
            return list(map(float, input().split()))

        def GMI():
            return map(lambda x: int(x) - 1, input().split())

        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))

    if packages:
        import os
        import random
        from io import BytesIO, IOBase


        BUFSIZE = 4096

    if output_together:

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

        sys.stdout = IOWrapper(sys.stdout)

    if dfs:
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

    if hashing:
        RANDOM = random.getrandbits(20)

        class Wrapper(int):
            def __init__(self, x):
                int.__init__(x)

            def __hash__(self):
                return super(Wrapper, self).__hash__() ^ RANDOM

    if read_from_file:
        file = open("input.txt", "r").readline().strip()[1:-1]
        fin = open(file, "r")
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")

        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)

    if de:

        def debug(*args, **kwargs):
            print("\033[92m", end="")
            print(*args, **kwargs)
            print("\033[0m", end="")


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, a):
        a = self.parent[a]
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def merge(self, a, b):
        pa, pb = self.find(a), self.find(b)
        if pa == pb:
            return False
        self.parent[pb] = pa
        return True


res = []


def main():
    n = II()
    s = I()

    # Transform the string to handle even-length palindromes uniformly
    tmp_s = "#" + "#".join(s) + "#"
    wing = [0] * len(tmp_s)  # Stores radius of palindrome centered at each position
    cur_ma = 0  # Center of the rightmost palindrome
    for i in range(2, len(tmp_s), 2):  # Only even indices (original string positions)
        # Use previously computed values when possible
        if cur_ma + wing[cur_ma] > i:
            wing[i] = min(wing[2 * cur_ma - i], cur_ma + wing[cur_ma] - i)
        # Expand palindrome centered at i
        while (
            i > wing[i]
            and i + wing[i] + 1 < len(tmp_s)
            and tmp_s[i - wing[i] - 1] == tmp_s[i + wing[i] + 1]
        ):
            wing[i] += 1
        # Update rightmost palindrome center if necessary
        if wing[i] + i > cur_ma + wing[cur_ma]:
            cur_ma = i

    # Initialize Union-Find structure for merging overlapping palindromes
    union = UnionFind(n + 1)

    right = [inf] * n  # Stores rightmost position where a palindrome ends
    for i in range(n - 1):
        idx = 2 * i + 2  # Convert to transformed string index
        if wing[idx]:  # If there's a palindrome centered at this position
            l = i - wing[idx] // 2 + 1  # Left bound of palindrome in original string
            x = 2 * i + 1  # Original index in transformed string
            # Use Union-Find to merge overlapping segments
            while union.find(l) <= i:
                l = union.find(l)
                right[l] = x - l  # Store extent of palindrome
                union.merge(l + 1, l)  # Mark that next index is connected

    # Dynamic Programming to count beautiful substrings
    dp = [1] * (n + 1)  # dp[i] = number of ways to partition s[0:i]
    for i in range(n):
        if right[i] < inf:
            dp[right[i] + 1] += dp[i]  # Add to next partition count

    # Add result to global res array (subtracting n+1 to exclude empty strings)
    res.append(sum(dp) - n - 1)
    return


t = II()
for _ in range(t):
    main()

print("\n".join(map(str, res)))


# https://github.com/VaHiX/CodeForces/