# Contest 1713, Problem A: Traveling Salesman Problem
# URL: https://codeforces.com/contest/1713/problem/A

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    n = int(input())
    X = [0]
    Y = [0]
    for i in range(n):
        x, y = map(int, input().split())
        X.append(x)
        Y.append(y)

    ans = max(X) - min(X) + max(Y) - min(Y)
    print(2 * ans)


for _ in range(int(input())):
    solve()
