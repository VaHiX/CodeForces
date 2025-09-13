# Contest 2077, Problem A: Breach of Faith
# URL: https://codeforces.com/contest/2077/problem/A

for test_case in range(int(input())):
    n = int(input())
    b = sorted([int(_) for _ in input().split()])

    a = [0 for _ in range(2 * n + 1)]

    for i in range(0, n + 1):
        a[2 * i] = b[n + i - 1]

    for i in range(0, n - 1):
        a[2 * i + 1] = b[i]

    a[2 * n - 1] = sum(b[n - 1 :]) - sum(b[: n - 1])
    print(*a)
