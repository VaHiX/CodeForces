# Problem: CF 1945 F - Kirill and Mushrooms
# https://codeforces.com/contest/1945/problem/F

"""
算法思路：
- 本题的关键在于理解蘑菇采摘的约束条件：当采摘k个蘑菇时，前k-1个蘑菇的魔法值会变为0。
- 我们可以通过预处理，将蘑菇按照采摘顺序重新编号，得到一个新数组nums，其中nums[i]表示第i个被采摘的蘑菇的魔法值。
- 然后我们从后往前枚举采摘的蘑菇数量length，维护一个大小为length的最大堆，每次取出堆顶元素作为当前最小值，计算strength = min_value * length。
- 由于要求最大strength，我们更新ans[0]；同时如果strength相同，我们要选择最少的蘑菇数，即ans[1]。

时间复杂度：O(n log n)，因为每个元素最多进入堆和弹出堆一次，堆操作时间复杂度为O(log n)。
空间复杂度：O(n)，用于存储数组nums和堆。
"""

import os
import sys
from heapq import heappop, heappush
from io import BytesIO, IOBase


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


BUFSIZE = 5096


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

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

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()


sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


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


"""
1.考虑约束条件
2.枚举采摘的蘑菇数量
    (1)此时可以得到能够采摘哪些蘑菇 从这些蘑菇中有优先采摘最大的即可 
"""


def main():
    n = II()
    tmp = LII()
    nums = [-1] * n
    p = LGMI()
    for i in range(n):
        nums[i] = tmp[p[i]]

    ans = [0, 0]
    heap = []

    for length in range(n, 0, -1):
        heappush(heap, nums[length - 1])

        if n - length + 1 < length or len(heap) < length:
            continue

        while len(heap) > length:
            heappop(heap)
        if heap[0] * length >= ans[0]:
            ans[0] = heap[0] * length
            ans[1] = length
    print(*ans)


t = II()
for _ in range(t):

    main()


# https://github.com/VaHiX/CodeForces/