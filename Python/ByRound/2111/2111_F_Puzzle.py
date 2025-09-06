# Contest 2111, Problem F: Puzzle
# URL: https://codeforces.com/contest/2111/problem/F

import sys
from math import gcd

if 1:
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


MAX_RANGE = 201


def __Main__():
    p, s = MII()
    g = gcd(p, s)
    p, s = p // g, s // g
    for i in range(1, MAX_RANGE):
        for j in range(1, MAX_RANGE):
            np = (i + j) << 1

            if np % p != 0:
                continue

            MIN_S, MAX_S = i + j - 1, i * j
            S = np // p * s

            if S <= 50000 and MIN_S <= S <= MAX_S:
                outs = []
                outs.append(str(S))
                for ni in range(1, i + 1):
                    outs.append("{} {}".format(ni, 1))
                    S -= 1
                for nj in range(2, j + 1):
                    outs.append("{} {}".format(1, nj))
                    S -= 1
                for ni in range(2, i + 1):
                    for nj in range(2, j + 1):
                        if S > 0:
                            outs.append("{} {}".format(ni, nj))
                            S -= 1
                        else:
                            break
                    if S <= 0:
                        break
                print("\n".join(map(str, outs)))
                return
    print(-1)


t = II()
for _ in range(t):
    __Main__()
