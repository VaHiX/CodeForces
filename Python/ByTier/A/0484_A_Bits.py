# Contest 484, Problem A: Bits
# URL: https://codeforces.com/contest/484/problem/A


def solve():
    import sys

    input = sys.stdin.readline
    q = int(input())
    for _ in range(q):
        l, r = map(int, input().split())
        x = l
        for b in range(60):
            if not (x >> b) & 1:
                candidate = x | (1 << b)
                if candidate <= r:
                    x = candidate
                    # print(x)
        print(x)


solve()
