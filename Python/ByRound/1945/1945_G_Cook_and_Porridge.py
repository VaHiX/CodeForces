# Problem: CF 1945 G - Cook and Porridge
# https://codeforces.com/contest/1945/problem/G

"""
Problem: G. Cook and Porridge
Algorithm: Simulation with Priority Queue (Heap) and Queue management
Time Complexity: O(n * log(n) + D * log(n))
Space Complexity: O(n + D)

This problem simulates a queue of schoolchildren getting porridge served over D minutes.
Each child has a priority and a time to eat one portion. Children are served in priority order
and return to the queue after eating, with special handling for priority-based queue positioning.
The simulation tracks when children are served and when they return, maintaining a queue
with proper priority ordering.

Key points:
1. Children are served in order of priority (higher priority first)
2. When a child returns after eating, they position themselves in queue based on priority
3. Children returning at same time are ordered by their eating time (ascending)
4. Need to track when each child gets served for first time within D minutes
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
        from heapq import heappop, heappush
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

for _ in range(t):
    n, d = MII()
    priority = []
    waiting_time = []
    for i in range(n):
        k, s = MII()
        priority.append(k)
        waiting_time.append(s)

    # Normalize priorities for efficient heap operations
    mapping = {v: i for i, v in enumerate(sorted(set(sorted(priority)), reverse=True))}
    priority = [mapping[x] for x in priority]

    # Preprocess return times in time order to ensure proper placement
    return_priority = [-1] * n
    for i, v in enumerate(sorted(range(n), key=lambda x: waiting_time[x])):
        return_priority[v] = i

    # Precompute minimum priority from current position onwards for efficient queue operations
    tmp_priority = priority[:]
    for i in range(n - 1, 0, -1):
        tmp_priority[i - 1] = min(tmp_priority[i - 1], tmp_priority[i])

    pt = 0  # Current position in queue

    new_queue = []  # Queue of people waiting to be served
    waiting_queue = []  # Heap of people who have finished eating and will return at certain times

    cur_join = 0  # Counter for ordering when people return to queue
    for i in range(1, d + 1):

        # Process people who are returning at time i
        to_join = []
        while len(waiting_queue) and waiting_queue[0] // n == i:
            to_join.append(heappop(waiting_queue) % n)

        # Sort returning people first by their eating time then by their original index
        to_join.sort(key=lambda x: return_priority[x])
        for person in to_join:
            # Push returning people to new queue with special ordering
            heappush(new_queue, priority[person] * d * n + cur_join * n + person)
            cur_join += 1

        # Determine who to serve next:
        # If queue is empty or next person in queue is lower priority than current one, 
        # serve from the main queue (pt)
        if len(new_queue) == 0 or tmp_priority[pt] <= priority[new_queue[0] % n]:
            person = pt
            pt += 1
        else:
            # Otherwise serve from new_queue (higher priority returning person)
            person = heappop(new_queue) % n

        # Schedule person to return after eating
        if i + waiting_time[person] + 1 <= d:
            heappush(waiting_queue, (i + waiting_time[person] + 1) * n + person)

        if pt == n:  # Everyone has been served
            outs.append(i)
            break
    else:
        outs.append(-1)

print("\n".join(map(str, outs)))


# https://github.com/VaHiX/CodeForces/