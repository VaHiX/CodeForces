# Problem: CF 1424 M - Ancient Language
# https://codeforces.com/contest/1424/problem/M

"""
Reconstructs the alphabet order of an ancient civilization from a dictionary.
Uses topological sorting to determine the order of characters based on the
ordering of words in the dictionary.

Algorithms/Techniques:
- Topological Sort using DFS-based approach
- Character comparison to infer ordering
- Graph representation for dependency tracking

Time Complexity: O(V + E + W) where V is number of unique characters (at most 26), 
E is number of edges in the dependency graph, W is the total length of all words
Space Complexity: O(V + E) for storing the graph and auxiliary data structures

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


def toposort(graph):
    res, found = [], [0] * len(graph)
    stack = list(range(len(graph)))
    while stack:
        node = stack.pop()
        if node < 0:
            res.append(~node)
        elif not found[node]:
            found[node] = 1
            stack.append(~node)
            stack += graph[node]
    for node in res:
        if any(found[nei] for nei in graph[node]):
            return None
        found[node] = 0
    return res[::-1]


def main():
    n, k = MII()  # Read number of pages and words per page
    tmp = [None] * n  # Store each page's data
    for _ in range(n):
        idx = II()  # Read page number
        tmp[idx] = [I() for _ in range(k)]  # Read k words from this page
    vis = [0] * 26  # Track which characters are present
    dict_lst = []  # Flatten all words
    for x in tmp:
        dict_lst.extend(x)  # Add all words to the list
        for w in x:
            for c in w:
                vis[ord(c) - ord("a")] = 1  # Mark character as present
    m = n * k  # Total number of words
    path = [[] for _ in range(26)]  # Graph to represent character dependencies
    # Compare consecutive words to infer ordering
    for i in range(1, m):
        for x, y in zip(dict_lst[i - 1], dict_lst[i]):  # Compare characters in same position
            if x != y:
                # Add edge from x to y, meaning x comes before y
                path[ord(x) - ord("a")].append(ord(y) - ord("a"))
                break  # Stop comparing when first different character is found
        else:
            # If all characters match up to min length, shorter word must come first
            if len(dict_lst[i - 1]) > len(dict_lst[i]):
                print("IMPOSSIBLE")
                return
    topo = toposort(path)  # Perform topological sort to get ordering
    # Output result or "IMPOSSIBLE" if cycle detected
    print(
        "IMPOSSIBLE"
        if topo is None
        else "".join(chr(ord("a") + x) for x in topo if vis[x])
    )
    return


t = 1
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/