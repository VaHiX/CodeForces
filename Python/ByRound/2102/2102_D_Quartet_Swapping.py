# Contest 2102, Problem D: Quartet Swapping
# URL: https://codeforces.com/contest/2102/problem/D


def solve():
    n = int(input())
    lst = list(map(int, input().split()))

    used = [0] * n
    cnt = 0
    for i in range(n):
        if not used[i]:
            cnt += 1
            x = i
            while not used[x]:
                used[x] = 1
                x = lst[x] - 1

    ans = [0] * n
    a = []
    b = []
    for i in range(0, n, 2):
        a.append(lst[i])
    for i in range(1, n, 2):
        b.append(lst[i])

    a.sort()
    b.sort()
    for i in range(len(a)):
        ans[i * 2] = a[i]
    for i in range(len(b)):
        ans[i * 2 + 1] = b[i]

    used = [0] * n
    c2 = 0
    for i in range(n):
        if not used[i]:
            c2 += 1
            x = i
            while not used[x]:
                used[x] = 1
                x = ans[x] - 1

    if (n - cnt) % 2 != (n - c2) % 2:
        ans[n - 3], ans[n - 1] = ans[n - 1], ans[n - 3]

    print(" ".join(map(str, ans)))


t = int(input())
for _ in range(t):
    solve()
