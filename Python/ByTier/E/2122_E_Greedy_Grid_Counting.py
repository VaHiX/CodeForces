# Contest 2122, Problem E: Greedy Grid Counting
# URL: https://codeforces.com/contest/2122/problem/E

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

from collections import defaultdict, deque
from heapq import heappop, heappush
from bisect import bisect_left, bisect_right

DD = defaultdict
BSL = bisect_left
BSR = bisect_right

from itertools import product


def calc(n, k):
    res = 0
    for p in product(range(1, k + 1), repeat=2 * n):
        # 最大値
        ans = 0
        for i in range(n):
            tmp = 0
            for j in range(n):
                if j <= i:
                    tmp += p[j]
                if i <= j:
                    tmp += p[j + n]
            ans = max(ans, tmp)

        ans2 = p[0] + p[-1]
        f = False
        for i in range(n - 1):
            if f:
                ans2 += p[i + n]
            else:
                if p[i + 1] < p[i + n]:
                    f = True
                    ans2 += p[i + n]
                else:
                    ans2 += p[i + 1]

        if ans == ans2:
            res += 1
    return res


# k = 10
# for n in range(2, 5):
# print(calc(n, k))


def solve():
    n, k = MI()
    a1 = LI()
    a2 = LI()
    # 欲張りな経路で最大値を取るものが存在する通り数
    # たて2マスのみ考えればよい

    # 1 から開始して いま (1 or 2)
    # dp[i][]
    c = [0] * n  # 上が最大値の通り数
    dp = [[0] * (k + 1) for i in range(n)]  # dp[d] = 下 - 上
    # これが負になってはいけない

    # p >= q の数は？
    coef = k * (k + 1) // 2

    c[0] = 1
    s = 100
    for i in range(n - 1):
        p = a1[i + 1]
        q = a2[i]
        # if p >= q なのであれば、
        # 上が最大値は変更なし、
        # 下は q - p 下がる。これが0以下は見捨てる
        # if p < q なのであれば、
        # 下 - 上はすべてこれになる いま大丈夫もこれになる
        if p == -1 and q == -1:
            # 上の遷移
            c[i + 1] = c[i] * coef % mod
            s = 0
            ds = 0
            for j in reversed(range(0, k + 1)):  #
                s += k * dp[i][j] % mod
                s -= ds % mod
                ds += dp[i][j] % mod
                dp[i + 1][j] += s % mod

            # 下の遷移
            s = (c[i] + sum(dp[i])) % mod  # 現状可能な通り数
            for j in range(1, k):
                dp[i + 1][j] += s * (k - j) % mod
        elif q == -1:
            s = (c[i] + sum(dp[i])) % mod
            for q in range(p + 1, k + 1):
                dp[i + 1][q - p] = s
            # q <= p
            c[i + 1] += c[i] * p % mod

            # dpへの寄与 下がる
            d = p
            s = 0
            for j in reversed(range(k + 1)):
                s += dp[i][j]
                if j + d <= k:
                    s -= dp[i][j + d]
                dp[i + 1][j] += s % mod

        elif p == -1:
            s = (c[i] + sum(dp[i])) % mod
            # p < q
            for p in range(1, q):
                dp[i + 1][q - p] = s

            # q <= p
            c[i + 1] += c[i] * (k + 1 - q) % mod
            d = k + 1 - q
            s = 0
            for j in reversed(range(k + 1)):
                s += dp[i][j]
                if j + d <= k:
                    s -= dp[i][j + d]
                dp[i + 1][j] += s % mod
        else:
            if p >= q:
                c[i + 1] = c[i]
                for j in range(p - q, k + 1):
                    dp[i + 1][j - (p - q)] = dp[i][j] % mod
            else:
                s = (c[i] + sum(dp[i])) % mod
                dp[i + 1][q - p] = s

        # print("pq", p, q)
        # print(c[i+1])
        # print(dp[i+1])

    ans = (c[n - 1] + sum(dp[n - 1])) % mod
    if a1[0] == -1:
        ans *= k
        ans %= mod
    if a2[-1] == -1:
        ans *= k
        ans %= mod

    # print("ans")
    print(ans % mod)
    return


for i in range(II()):
    solve()
