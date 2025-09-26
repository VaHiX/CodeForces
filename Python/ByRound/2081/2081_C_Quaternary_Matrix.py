# Contest 2081, Problem C: Quaternary Matrix
# URL: https://codeforces.com/contest/2081/problem/C

# input
import sys

input = sys.stdin.readline
II = lambda: int(input())
MI = lambda: map(int, input().split())
LI = lambda: [int(a) for a in input().split()]
SI = lambda: input().rstrip()
LLI = lambda n: [[int(a) for a in input().split()] for _ in range(n)]
LSI = lambda n: [input().rstrip() for _ in range(n)]
MI_1 = lambda: map(lambda x: int(x) - 1, input().split())
LI_1 = lambda: [int(a) - 1 for a in input().split()]


def graph(n: int, m: int, dir: bool = False, index: int = -1) -> list[set[int]]:
    edge = [set() for i in range(n + 1 + index)]
    for _ in range(m):
        a, b = map(int, input().split())
        a += index
        b += index
        edge[a].add(b)
        if not dir:
            edge[b].add(a)
    return edge


def graph_w(n: int, m: int, dir: bool = False, index: int = -1) -> list[set[tuple]]:
    edge = [set() for i in range(n + 1 + index)]
    for _ in range(m):
        a, b, c = map(int, input().split())
        a += index
        b += index
        edge[a].add((b, c))
        if not dir:
            edge[b].add((a, c))
    return edge


mod = 998244353
inf = 1001001001001001001
ordalp = lambda s: ord(s) - 65 if s.isupper() else ord(s) - 97
ordallalp = lambda s: ord(s) - 39 if s.isupper() else ord(s) - 97
yes = lambda: print("Yes")
no = lambda: print("No")
yn = lambda flag: print("Yes" if flag else "No")


def acc(a: list[int]):
    sa = [0] * (len(a) + 1)
    for i in range(len(a)):
        sa[i + 1] = a[i] + sa[i]
    return sa


prinf = lambda ans: print(ans if ans < 1000001001001001001 else -1)
alplow = "abcdefghijklmnopqrstuvwxyz"
alpup = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alpall = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
URDL = {"U": (-1, 0), "R": (0, 1), "D": (1, 0), "L": (0, -1)}
DIR_4 = [[-1, 0], [0, 1], [1, 0], [0, -1]]
DIR_8 = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]]
DIR_BISHOP = [[-1, 1], [1, 1], [1, -1], [-1, -1]]
prime60 = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59]
sys.set_int_max_str_digits(0)
# sys.setrecursionlimit(10**6)
# import pypyjit
# pypyjit.set_param('max_unroll_recursion=-1')

from collections import defaultdict
from heapq import heappop, heappush
from bisect import bisect_left, bisect_right

DD = defaultdict
BSL = bisect_left
BSR = bisect_right


def solve():
    n, m = MI()
    a = []
    for i in range(n):
        a.append(list(map(int, SI())))

    r = [[], [], [], []]
    for i in range(n):
        t = 0
        for j in range(m):
            t ^= a[i][j]
        r[t].append(i)

    c = [[], [], [], []]
    for j in range(m):
        t = 0
        for i in range(n):
            t ^= a[i][j]
        c[t].append(j)

    ans = 0
    for x in range(1, 4):
        while r[x] and c[x]:
            i = r[x].pop()
            j = c[x].pop()
            a[i][j] ^= x
            ans += 1

    # それぞれどちらかは0となる
    def op(x, y1, y2):
        res = 0
        while r[x] and c[y1] and c[y2]:
            i = r[x].pop()
            j1 = c[y1].pop()
            j2 = c[y2].pop()
            res += 2
            a[i][j1] ^= y1
            a[i][j2] ^= y2
        return res

    def op2(x1, x2, y):
        res = 0
        while r[x1] and r[x2] and c[y]:
            i1 = r[x1].pop()
            i2 = r[x2].pop()
            j = c[y].pop()
            res += 2
            a[i1][j] ^= x1
            a[i2][j] ^= x2
        return res

    for i in range(1, 4):
        for j in range(i + 1, 4):
            k = i ^ j
            ans += op(k, i, j)
            ans += op2(i, j, k)

    def op3(x, y):
        res = 0
        while len(r[x]) >= 2 and len(c[y]) >= 2:
            i1 = r[x].pop()
            i2 = r[x].pop()
            j1 = c[y].pop()
            j2 = c[y].pop()
            a[i1][j1] ^= x ^ y
            a[i2][j1] ^= x
            a[i1][j2] ^= y
            res += 3
        return res

    # あとは同じ列にあるか、2つか
    for i in range(1, 4):
        for j in range(1, 4):
            ans += op3(i, j)

    for x in range(1, 4):
        while r[x]:
            i = r[x].pop()
            ans += 1
            a[i][0] ^= x
        while c[x]:
            j = c[x].pop()
            ans += 1
            a[0][j] ^= x

    print(ans)
    for i in a:
        print(*i, sep="")
    # print(r, c)

    for i in range(n):
        t = 0
        for j in range(m):
            t ^= a[i][j]
        assert t == 0

    for j in range(m):
        t = 0
        for i in range(n):
            t ^= a[i][j]
        assert t == 0

    return


t = II()
for _ in range(t):
    solve()
