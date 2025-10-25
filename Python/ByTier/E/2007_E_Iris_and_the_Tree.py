# Contest 2007, Problem E: Iris and the Tree
# URL: https://codeforces.com/contest/2007/problem/E

import sys
import os
from io import BytesIO, IOBase

# region fastio
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

if sys.version_info[0] < 3:
    sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

file = sys.stdin
if os.environ.get('USER') == "loic":
    file = open("data.in")
    
line = lambda: file.readline().split()
ui = lambda: int(line()[0])
mi = lambda: map(int,line())
li = lambda: list(mi())
lsi = lambda: list(map(int,line()[0]))
#######################################################################

class FenwickTreeSum:
    def __init__(self, sz, arr = []):
        self.sz = sz
        self.fen = self._build(arr)
 
    def _build(self,arr):
        fen = [0] * self.sz
        if arr:
            for i in range(self.sz):
                fen[i] += arr[i]
                n = i | (i + 1)
                if n < self.sz:
                    fen[n] += fen[i]
        return fen
 
    def increase(self, pos, x):
        while pos < self.sz:
            self.fen[pos] += x
            pos |= pos + 1
            
    def _query(self, r):
        s = 0
        r += 1
        while r > 0:
            s += self.fen[r - 1]
            r &= r - 1
        return s
    
    def query(self,l,r):
        assert(l <= r)
        return self._query(r) - self._query(l-1)
    
    def __repr__(self):
        res = []
        for i in range(self.sz):
            res.append(self.query(i,i))
        return " ".join(str(v) for v in res)


def solve():
    
    res = []

    par.append(0)

    p = [[] for _ in range(N + 1)]
    cnt = [0] * (N + 1)
    ft = FenwickTreeSum(N)
    
    c = 0
    stack = [0]
    n = 1
    while n < N + 1:
        while stack[-1] != par[n]:
            cur = stack.pop()
            p[cur].append(c)
            cnt[c] += 1
        stack.append(n)
        p[n].append(c)
        cnt[c] += 1
        c += 1
        n += 1
        
    last = p.pop()[0]
    cnt[last] -= 1

    s = 0
    c = 0

    for _ in range(N-1):
        t,w = mi()
        t -= 1
        
        a,b = p[t]
        ft.increase(a, w)
        ft.increase(b, w)
        cnt[a] -= 1
        cnt[b] -= 1
        if cnt[a] == 0:
            c += 1
        if cnt[b] == 0:
            c += 1
        s += w
        
        res.append(ft.query(0, N-1) + (N - c) * (K - s))
    
    return " ".join(str(v) for v in res)


for test in range(1,ui()+1):
    N,K = mi()
    A = li()
    par = [None] + [p-1 for i,p in enumerate(A,1)]
    
    print(solve())
    
file.close()