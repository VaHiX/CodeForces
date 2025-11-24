# Problem: CF 1267 K - Key Storage
# https://codeforces.com/contest/1267/problem/K

"""
Algorithm: Key Storage
Approach: 
- For each key, compute its fingerprint by iteratively dividing by 2, 3, 4, ... until the result is 0
- The fingerprint is the multiset of remainders from these divisions
- To count how many other keys produce the same fingerprint:
  - Calculate the total permutations of the multiset of remainders
  - Subtract 1 (since we don't count the original key)
  - Handle special case of 0 remainders (can't be first in sequence)

Time Complexity: O(n * log(k)) where n is the number of keys and k is max key value
Space Complexity: O(1) since we only store fixed size arrays for remainders and factorials
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
            return input().split()

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

        def bootstrap(f, stk=[]):
            def wrappedfunc(*args, **kwargs):
                if stk:
                    return f(*args, **kwargs)
                else:
                    to = f(*args, **kwargs)
                    while True:
                        if type(to) is GeneratorType:
                            stk.append(to)
                            to = next(to)
                        else:
                            stk.pop()
                            if not stk:
                                break
                            to = stk[-1].send(to)
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

    fmax = lambda x, y: x if x > y else y
    fmin = lambda x, y: x if x < y else y

    class lst_lst:
        def __init__(self, n) -> None:
            self.n = n
            self.pre = []
            self.cur = []
            self.lst = [-1] * n

        def append(self, i, j):
            self.pre.append(self.lst[i])
            self.lst[i] = len(self.cur)
            self.cur.append(j)

        def iterate(self, i):
            tmp = self.lst[i]
            while tmp != -1:
                yield self.cur[tmp]
                tmp = self.pre[tmp]


t = II()
outs = []
fac = [1] * 20
for i in range(1, 20):
    fac[i] = fac[i - 1] * i
for _ in range(t):
    k = II()
    cnt = [0] * 20
    length = 0
    # Compute remainders by dividing by 2,3,4,... until result is 0
    for i in range(1, 21):
        cnt[k % i] += 1
        length = i
        k //= i
        if k == 0:
            break
    ans = 0
    to_divide = 1
    res = 1
    cur = 0
    # Calculate total permutations using multinomial coefficient
    for i in range(length):
        to_divide *= fac[cnt[i]]
        cur += cnt[i]
        res *= cur
        cur -= 1
    ans += res // to_divide
    # Handle case when 0 is in remainder sequence (can't be first)
    if cnt[0]:
        cnt[0] -= 1
        length -= 1
        to_divide = 1
        res = 1
        cur = 0
        # Recalculate permutations excluding 0s at beginning
        for i in range(length):
            to_divide *= fac[cnt[i]]
            cur += cnt[i]
            res *= cur
            cur -= 1
        ans -= res // to_divide
    outs.append(ans - 1)
print("\n".join(map(str, outs)))


# https://github.com/VaHiX/CodeForces/