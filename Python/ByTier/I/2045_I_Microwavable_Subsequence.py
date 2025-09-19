# Contest 2045, Problem I: Microwavable Subsequence
# URL: https://codeforces.com/contest/2045/problem/I


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

# RSI = lambda: int(sys.stdin.buffer.readline())
SI = lambda: int(sys.stdin.buffer.readline())
RI = lambda: list(map(int, sys.stdin.buffer.readline().strip().split()))
SS = lambda: sys.stdin.buffer.readline().strip().decode("ascii")
RS = lambda: sys.stdin.buffer.readline().strip().decode("ascii").split()
DEBUG = lambda *x: sys.stderr.write(f"{str(x)}\n")
# print = lambda d: sys.stdout.write(str(d) + "\n")

if sys.hexversion == 51053040:
    sys.stdin = open(sys.path[0] + "/data")
"""
参考样例
输入
5 4
3 2 1 3 2
输出 13

输入
3 3
1 1 1
输出 2

题意简述：

https://codeforces.com/problemset/problem/2045/I

输入 n(1≤n≤3e5) m(1≤m≤3e5) 和长为 n 的数组 a(1≤a[i]≤m)。

定义振荡序列为形如 [3,1,3]，[3,2,3,2]，[1] 这种最多由两种元素组成的，相邻元素不同的序列。
定义 f(x,y) 为 a 中最长振荡子序列的长度，其中子序列的每个数要么是 x，要么是 y。
注：子序列不一定连续。

输出所有 f(x,y) 的和，其中 1≤x<y≤m。

思路：
    遍历数列a：
        1. ai是首次出现：贡献为 (m - 1)
            ai与所有不在a中的数 贡献为 c
            ai与所有在a中的数 贡献为 m - 1 - c
        2. ai不是首次出现：
            设上一次 ai 出现的位置为 pi
            pi 到 i 之间有 k个数，对于这k个数，ai都可以拼在后面：贡献为 k
    核心在于计算ai上次的位置到当前位置的不同的数有多少个。
        用树状数组维护每个数的最新下标，查询区间内下标的个数，即为区间内不同的数的个数。
"""


def solve():
    n, m = RI()
    a = RI()
    pi = [-1] * (m + 1)  # 记录上一次坐标
    ftl = n + 5
    ft = [0] * ftl

    def ad(i, x):
        i += 1
        while i < ftl:
            ft[i] += x
            i += i & -i

    def ps(i):
        r = 0
        i += 1
        while i:
            r += ft[i]
            i &= i - 1
        return r

    ans = 0
    for i, v in enumerate(a):
        if pi[v] == -1:
            ans += m - 1
        else:
            ans += ps(i) - ps(pi[v])
            ad(pi[v], -1)
        pi[v] = i
        ad(i, 1)
    print(ans)

    return 0


# for t in range(SI() - 1):
#     solve()
solve()
