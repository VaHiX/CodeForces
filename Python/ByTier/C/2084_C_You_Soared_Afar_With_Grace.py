# Contest 2084, Problem C: You Soared Afar With Grace
# URL: https://codeforces.com/contest/2084/problem/C

# https://codeforces.com/contest/2084

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


def solve_case():
    n = int(input())
    a = list(map(lambda x: int(x) - 1, input().split()))
    b = list(map(lambda x: int(x) - 1, input().split()))

    ans = []

    if n & 1:
        i = next((i for i in range(n) if a[i] == b[i]), None)
        if i is None:
            print(-1)
            return
        j = n // 2
        if i != j:
            a[i], a[j] = a[j], a[i]
            b[i], b[j] = b[j], b[i]
            ans += [(i + 1, j + 1)]

    pos = [0] * n
    for i, x in enumerate(a):
        pos[x] = i

    for k in range(n // 2):
        if a[k] == b[k]:
            print(-1)
            return
        i = pos[b[k]]
        if b[i] != a[k]:
            print(-1)
            return
        j = n - 1 - k
        if i == j:
            continue
        pos[a[i]], pos[a[j]] = j, i
        a[i], a[j] = a[j], a[i]
        b[i], b[j] = b[j], b[i]
        ans += [(i + 1, j + 1)]

    print(len(ans))
    for swap in ans:
        print(f"{swap[0]} {swap[1]}")


for _ in range(int(input())):
    solve_case()
