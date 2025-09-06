# Contest 2051, Problem F: Joker
# URL: https://codeforces.com/contest/2051/problem/F

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    N, M, Q = map(int, input().split())
    A = list(map(int, input().split()))

    a, b = 0, N + 1
    l, r = M, M
    Ans = []

    for n in A:
        if l != N + 1:
            if l <= n <= r:
                a += 1
                b -= 1
                if l == r:
                    l, r = N + 1, 0
            elif n > r:
                r = min(N, r + 1)
                if a != 0:
                    a += 1
                if b != N + 1 and n < b:
                    b -= 1
            else:
                l = max(l - 1, 1)
                if b != N + 1:
                    b -= 1
                if a != 0 and a < n:
                    a += 1

        else:
            if a < n:
                a += 1
            if b > n:
                b -= 1

        if l != N + 1:
            cnt = r - l + 1
            if a < l:
                cnt += a
            else:
                cnt += l - 1
            if b > r:
                cnt += N - b + 1
            else:
                cnt += N - r
        else:
            if a < b:
                cnt = a + N - b + 1
            else:
                cnt = N

        Ans.append(cnt)

    print(*Ans)
