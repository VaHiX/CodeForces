# Problem: CF 1980 F2 - Field Division (hard version)
# https://codeforces.com/contest/1980/problem/F2

"""
Algorithm: Dynamic Programming with Monotonic Stack
Time Complexity: O(k * log k)
Space Complexity: O(k)

This solution uses a dynamic programming approach with a monotonic stack to 
efficiently compute the maximum area Alice can obtain in a field divided by a path,
and calculates the gain from each fountain Bob gives Alice.
"""

standard_input, packages, output_together = 1, 1, 0
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
        from collections import Counter
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


t = II()
outs = []
rnd = random.getrandbits(20)

for _ in range(t):
    n, m, k = MII()
    d = Counter()
    d2 = Counter()
    notes = {}
    for i in range(k):
        r, c = MII()
        # Using XOR with random value to avoid hash collisions
        if m + 1 - c >= d[r ^ rnd]:
            d[r ^ rnd], d2[r ^ rnd] = m + 1 - c, d[r ^ rnd]
            notes[r ^ rnd] = i
        elif d2[r ^ rnd] < m + 1 - c:
            d2[r ^ rnd] = m + 1 - c

    vis = [0] * k

    rs = sorted(x ^ rnd for x in d)
    cs = [d[x ^ rnd] for x in rs]
    k = len(rs)
    rs = [0] + rs
    cs = [m] + cs

    # Precompute suffix maximums to avoid recomputation
    cs_acc = cs[:]
    for i in range(k - 1, -1, -1):
        cs_acc[i] = max(cs_acc[i], cs_acc[i + 1])

    ans = 0
    stack = [0]
    acc = [0]
    for i in range(k):
        # Compute the area using the accumulated prefix sums
        ans += cs_acc[i + 1] * (rs[i + 1] - rs[i])
        # Check if this is the last section or if next section has different height
        if i == k - 1 or cs_acc[i + 1] != cs_acc[i + 2]:
            l, r = 0, len(stack) - 1
            tmp = max(d2[rs[i + 1] ^ rnd], cs_acc[i + 2] if i + 2 <= k else 0)
            # Binary search to find the optimal previous segment
            while l <= r:
                mid = (l + r) // 2
                if cs[stack[mid]] > tmp:
                    l = mid + 1
                else:
                    r = mid - 1
            # Calculate gain from giving fountains to Alice (this is the difference in area)
            vis[notes[rs[i + 1] ^ rnd]] = ans - (
                acc[r] + (rs[i + 1] - rs[stack[r]]) * tmp
            )

        # Maintain monotonic stack (decreasing heights)
        while cs[stack[-1]] < cs[i + 1]:
            acc.pop()
            stack.pop()
        acc.append(acc[-1] + (rs[i + 1] - rs[stack[-1]]) * cs[i + 1])
        stack.append(i + 1)

    outs.append(str(n * m - ans))
    outs.append(" ".join(map(str, vis)))

print("\n".join(outs))


# https://github.com/VaHiX/CodeForces/