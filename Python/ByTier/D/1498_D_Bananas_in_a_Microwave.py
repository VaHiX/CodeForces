# Problem: CF 1498 D - Bananas in a Microwave
# https://codeforces.com/contest/1498/problem/D

"""
Algorithm: Dynamic Programming with BFS-like Approach
Time Complexity: O(n * m * y_max) where y_max is the maximum value of y_i
Space Complexity: O(m)

This problem involves finding the earliest time-step to produce exactly j bananas for each j in [1, m].
We use a visited array to track which banana counts are reachable and an answer array to store the earliest time-step for each count.
For each timestep, we iterate through all currently reachable counts and apply the operation up to y_i times,
updating the answer array with the current timestep when a new count is reached.
"""

if 1:
    standard_input, packages, output_together = 1, 1, 1
    dfs, hashing, read_from_file = 0, 0, 0
    de = 1

    if standard_input:
        import os
        import sys

        input = lambda: sys.stdin.readline().strip()

        inf = float("inf")

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

        def debug(*args):
            print("\033[92m", end="")
            print(*args)
            print("\033[0m", end="")


def main():
    n, m = MII()
    vis = [0] * (m + 1)  # Visited array to track reachable banana counts
    vis[0] = 1  # Initially we have 0 bananas
    ans = [-1] * (m + 1)  # Answer array to store earliest time-step for each banana count
    ans[0] = 0  # 0 bananas can be achieved at timestep 0

    for tmstamp in range(1, n + 1):  # Process each timestep
        t, x, y = MII()  # Read operation type, x value (scaled), and max operations allowed

        def op():
            # Perform the operation based on type t
            # For type 1: add x (rounded up)
            # For type 2: multiply by x (rounded up)
            return (
                cur + (x + 99999) // 100000 if t == 1 else (cur * x + 99999) // 100000
            )

        vals = []
        # Iterate through all currently reachable banana counts
        for i in range(m + 1):
            if vis[i]:
                cur = i  # Current count
                # Apply the operation up to y times
                for _ in range(y):
                    cur = op()  # Update count using the operation
                    if cur > m or vis[cur]:  # If exceeds limit or already visited
                        break
                    vals.append(cur)  # Store newly reachable count
                    ans[cur] = tmstamp  # Mark the timestep when it was reached

        # Update visited array for all newly found values
        for idx in vals:
            vis[idx] = 1

    print(*ans[1:])  # Output the answers for banana counts 1 to m
    return


t = 1
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/