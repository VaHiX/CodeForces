# Problem: CF 1161 A - Hide and Seek
# https://codeforces.com/contest/1161/problem/A

"""
Problem: Hide and Seek

Alice and Bob are playing a game on a line with n cells. Bob asks k questions about Alice's token position.
Alice can move her token to an adjacent cell at most once during the process. 
All answers must be "NO" to Bob's questions.

Approach:
- We simulate the process from the last question backward
- For each query, we determine if Alice can still make a valid move
- At each step, we maintain a set of positions that have been queried
- We compute possible starting and ending positions based on constraints

Time Complexity: O(n + k)
Space Complexity: O(n + k)

Algorithms/Techniques: 
- Simulation from back to front
- Set-based tracking of visited positions
- Dynamic programming with reverse iteration

"""
import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 8192


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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def solve():
    n, k = map(int, input().split())  # Read n (cells) and k (questions)
    queries = list(map(int, input().split()))  # Read Bob's questions
    
    if n == 1 and k > 0:  # Special case: only one cell, but there are queries
        print(0)  # No valid scenario possible
        return
    
    # Initialize ways array - each cell can have at most 2 possible moves 
    # (1 means Alice could start at this cell and stay, 2 means she could move)
    ways = [2 for _ in range(n)]  
    # First and last cells have only one way (can't move further outward)
    ways[0] = ways[-1] = 1
    
    S = set()  # Set to keep track of queried positions
    
    # Process queries in reverse order (from last to first)
    for q in queries[::-1]:
        q -= 1  # Convert to 0-indexed
        
        # If query is at the first cell
        if q == 0:
            # If the next cell (q+1) was already queried, then Alice can't be at position 0
            if (q + 1) in S:
                ways[q] = 0
        # If query is at the last cell
        elif q == n - 1:
            # If the previous cell (q-1) was already queried, then Alice can't be at the last cell
            if (q - 1) in S:
                ways[q] = 0
        else:
            # For interior cells, check both neighbors
            if (q + 1) in S and (q - 1) in S:
                # Both adjacent cells were queried, position is forbidden
                ways[q] = 0  
            elif (q - 1) in S:
                # Only left neighbor was queried
                ways[q] = 1
            elif (q + 1) in S:
                # Only right neighbor was queried
                ways[q] = 1
            else:
                # Neither neighboring cell was queried, so all moves are possible
                pass
        
        # Mark current query position as visited 
        S.add(q)
    
    # Sum up all valid positions and add n - len(S) for unvisited cells
    print(sum(ways) + n - len(S))


solve()


# https://github.com/VaHiX/codeForces/