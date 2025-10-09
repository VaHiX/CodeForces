# Contest 2096, Problem G: Wonderful Guessing Game
# URL: https://codeforces.com/contest/2096/problem/G

# input
import sys

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

from collections import defaultdict, deque
from heapq import heappop, heappush
from bisect import bisect_left, bisect_right

DD = defaultdict
BSL = bisect_left
BSR = bisect_right

from functools import cache


@cache
def calc(a, p):
    m = len(a)
    a = list(a)
    if m == 1:
        return a[0]
    if p == 0:
        # min
        res = 0
        for i in range(m - 1):
            b = a.copy()
            x = b.pop(i)
            y = b.pop(i)
            b.insert(i, min(x, y))
            res = max(calc(tuple(b), p ^ 1), res)
    else:
        res = inf
        for i in range(m - 1):
            b = a.copy()
            x = b.pop(i)
            y = b.pop(i)
            b.insert(i, max(x, y))
            res = min(calc(tuple(b), p ^ 1), res)
    return res


def solve(n):
    m = n - 1
    c = 0
    while m:
        m //= 3
        c += 1

    ask = []
    sub = []

    def check(now):
        # print(now)
        if len(now[0]) == len(now[1]):
            ask.append(now[0] + now[1])
            sub.append((0, 1, 2))
        elif len(now[1]) == len(now[2]):
            ask.append(now[1] + now[2])
            sub.append((1, 2, 0))
        elif len(now[2]) == len(now[0]):
            ask.append(now[2] + now[0])
            sub.append((2, 0, 1))
        else:
            return False
        return True

    # 各桁ごとのものをいれる
    ss = [0] * n
    s = [0] * n
    for d in range(c):
        dd = 3**d  # この桁を確かめる
        now = [[], [], []]
        for i in range(n):
            f = (i // dd) % 3
            s[i] = (s[i] + f) % 3
            now[s[i]].append(i)
            ss[i] = (ss[i] + s[i]) % 3
        check(now)

    flag = False
    now = [[], [], []]
    for i in range(n):
        now[ss[i]].append(i)

    if check(now) == False:
        flag = True
        now = [[], [], []]
        for i in range(n):
            now[(ss[i] + s[i]) % 3].append(i)
        if check(now) == False:
            assert False

    print(c + 1)
    for a in ask:
        a = [i + 1 for i in a]
        print(len(a), *a)

    res = SI()

    t = [0] * c
    what = -1
    sgn = "LRN"
    for i in range(c):
        if res[i] == "?":
            what = i
        else:
            f = sgn.index(res[i])
            t[i] = sub[i][f]

    # print(t, sub)
    if what != -1:
        f = sgn.index(res[-1])
        if flag == False:
            ns = (sub[-1][f] - sum(t)) % 3
            t[what] = ns
        else:
            if what != c - 1:
                ns = (sub[-1][f] - sum(t) - t[-1]) % 3
                t[what] = ns
            else:
                # 最後の桁が不明のとき
                ns = (sub[-1][f] - sum(t)) % 3
                t[what] = ns * 2 % 3
    ans = 0
    p = 0
    k = 1
    for i in range(c):
        ans += k * ((t[i] - p) % 3)
        k *= 3
        p = t[i]
    ans += 1
    print(ans)
    return


t = II()
for i in range(t):
    n = II()
    solve(n)
