# Contest 2067, Problem D: Object Identification
# URL: https://codeforces.com/contest/2067/problem/D

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()


def ask(x, y):
    print("?", x, y, flush=True)
    return int(input())


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    ans = "A"

    try:
        x, y = a.index(1) + 1, a.index(n) + 1
        d = ask(x, y)
        if d >= n - 1 and d == ask(y, x):
            ans = "B"

    except:
        a = set(a)
        for i in range(1, n + 1):
            if i not in a:
                if ask(i, i - 1 if i > 1 else i + 1):
                    ans = "B"
                break

    print("!", ans, flush=True)
