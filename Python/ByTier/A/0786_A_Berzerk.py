# Problem: CF 786 A - Berzerk
# https://codeforces.com/contest/786/problem/A

"""
Algorithm: Game Theory with Dynamic Programming and BFS
Approach: 
- This problem is a game theory problem with states defined by (player, position).
- We use a dynamic programming approach where dp[person][pos] represents the outcome of the game:
  0: Unvisited, 1: Win, 2: Loop
- For each position and player, we simulate possible moves and use BFS to propagate results.
- The key idea is to identify which states lead to win (can force a win), loss (will lose), or loop (infinite game).

Time Complexity: O(n * (k1 + k2)) where n is the number of objects, k1 and k2 are sizes of Rick and Morty's sets respectively.
Space Complexity: O(n) for the dp and cnt arrays.

The code uses a reverse simulation (working backwards) to determine game outcomes by tracking how many moves are needed to make a decision, and when all moves are exhausted, if there's still no win, it's a loop.
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
            self.notest = [-1] * (n + 1)

        def append(self, i, j):
            self.pre.append(self.notest[i])
            self.notest[i] = len(self.cur)
            self.cur.append(j)

        def iterate(self, i):
            tmp = self.notest[i]
            while tmp != -1:
                yield self.cur[tmp]
                tmp = self.pre[tmp]


n = II()
k1, *s1 = MII()
k2, *s2 = MII()

dp = [[0] * n for _ in range(2)]
cnt = [[0] * n for _ in range(2)]


def f(person, pos):
    return person * n + pos


# Mark black hole (position 0) as loop for both players
dp[0][0] = 2
dp[1][0] = 2

stk = []
stk.append(f(0, 0))
stk.append(f(1, 0))

# BFS to compute all game states
while stk:
    person, pos = divmod(stk.pop(), n)

    if person:
        # Rick's turn: iterate over possible moves from his set
        for step in s1:
            last_pos = (pos - step) % n  # Calculate previous position before move
            if dp[0][last_pos] == 0:  # If not already determined
                if dp[person][pos] == 2:
                    # Current state is a loop, so previous state is a win for the opponent
                    dp[0][last_pos] = 1
                    stk.append(f(0, last_pos))
                else:
                    # Increment move count for previous state
                    cnt[0][last_pos] += 1
                    if cnt[0][last_pos] == k1:
                        # All moves exhausted, determine if it's a loop
                        dp[0][last_pos] = 2
                        stk.append(f(0, last_pos))
    else:
        # Morty's turn: iterate over possible moves from his set
        for step in s2:
            last_pos = (pos - step) % n  # Calculate previous position before move
            if dp[1][last_pos] == 0:  # If not already determined
                if dp[person][pos] == 2:
                    # Current state is a loop, so previous state is a win for the opponent
                    dp[1][last_pos] = 1
                    stk.append(f(1, last_pos))
                else:
                    # Increment move count for previous state
                    cnt[1][last_pos] += 1
                    if cnt[1][last_pos] == k2:
                        # All moves exhausted, determine if it's a loop
                        dp[1][last_pos] = 2
                        stk.append(f(1, last_pos))

strs = ["Loop", "Win", "Lose"]
# Print results for each starting position (excluding black hole)
print(" ".join(strs[dp[0][i]] for i in range(1, n)))
print(" ".join(strs[dp[1][i]] for i in range(1, n)))


# https://github.com/VaHiX/CodeForces/