# Problem: CF 1889 C2 - Doremy's Drying Plan (Hard Version)
# https://codeforces.com/contest/1889/problem/C2

"""
Algorithm: Dynamic Programming with Bitmask Optimization
Time Complexity: O(n * k * log(n))
Space Complexity: O(n * k)

The problem involves finding the maximum number of dry cities after preventing rain on k out of m days.
The approach uses dynamic programming with a bitmask-like state representation to track:
- The rightmost city that has been affected by rain (right_border)
- The number of days we have already prevented rain (delete)

We iterate through cities and for each city interval, we update our DP states.
The key is to maintain the maximum number of dry cities possible at each step.
"""

standard_input, packages, output_together = 1, 1, 1
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


rnd = random.getrandbits(20)


def main():
    n, m, k = MII()
    intervals = [[] for _ in range(n)]
    for _ in range(m):
        l, r = GMI()
        intervals[l].append(r)

    def f(right_border, delete):
        """Encode the state (right_border, delete) into a number"""
        return (right_border * 16 + delete) ^ rnd

    def revf(msk):
        """Decode the number back to (right_border, delete)"""
        return divmod(msk ^ rnd, 16)

    dp = [Counter(), Counter()]
    last = 0
    dp[last][f(0, 0)] = 0

    for l in range(n):
        for r in intervals[l]:
            cur = last ^ 1
            dp[cur].clear()  # Clear old state
            for msk in dp[last]:
                right_border, delete = revf(msk)
                v = 0 if right_border > l else l - right_border
                if delete < k:
                    # Case 1: We take the current day to prevent rain
                    n_right = right_border if right_border > l else l
                    nmsk = f(n_right, delete + 1)
                    dp[cur][nmsk] = max(dp[cur][nmsk], dp[last][msk] + v)
                # Case 2: We do not prevent rain on the current day
                n_right = right_border if right_border > r + 1 else r + 1
                nmsk = f(n_right, delete)
                dp[cur][nmsk] = max(dp[cur][nmsk], dp[last][msk] + v)
            last = cur

    ans = 0
    for x in dp[cur]:
        # Calculate final answer by considering the remaining dry cities
        ans = max(ans, dp[cur][x] + n - revf(x)[0])
    print(ans)
    return


t = II()
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/