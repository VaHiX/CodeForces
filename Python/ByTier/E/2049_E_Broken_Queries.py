# Contest 2049, Problem E: Broken Queries
# URL: https://codeforces.com/contest/2049/problem/E


def query(l, r):
    print("?", l + 1, r + 1, flush=True)
    return int(input())


def answer(n):
    print("!", n, flush=True)


def solve():
    n = int(input())
    a = query(0, (n >> 1) - 1)
    if a == 1:
        a1 = query(0, (n >> 2) - 1)
        a2 = query(n >> 2, (n >> 1) - 1)
        if a1 != a2:
            le = n >> 1
            ri = n - 1
            while le < ri:
                mid = (le + ri) >> 1
                if query(0, mid):
                    le = mid + 1
                else:
                    ri = mid
            answer(le + 1)
        else:
            le = 0
            ri = (n >> 1) - 1
            while le < ri:
                mid = (le + ri) >> 1

                if query(0, mid) == 0:
                    le = mid + 1
                else:
                    ri = mid
            answer(le + 1)
    else:
        a1 = query(n >> 1, (n >> 1) + (n >> 2) - 1)
        a2 = query((n >> 1) + (n >> 2), n - 1)
        if a1 != a2:
            le = 0
            ri = n >> 1
            while le < ri:
                mid = (le + ri + 1) >> 1
                if query(mid, n - 1) == 0:
                    le = mid
                else:
                    ri = mid - 1
            answer(n - le)
        else:
            le = n >> 1
            ri = n - 1
            while le < ri:
                mid = (le + ri) >> 1
                if query(n >> 1, mid) == 0:
                    le = mid + 1
                else:
                    ri = mid
            answer(le - (n >> 1) + 1)


import sys

input = lambda: sys.stdin.readline().rstrip()
for i in range(int(input())):
    solve()
