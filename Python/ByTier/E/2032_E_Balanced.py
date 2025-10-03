# Contest 2032, Problem E: Balanced
# URL: https://codeforces.com/contest/2032/problem/E


def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    if n == 1:
        print(0)
        return
    if n == 3:
        m = max(arr)
        print(*[m - a for a in arr])
        return
    arr = [-arr[0] + arr[-1]] + [-arr[i] + arr[i - 1] for i in range(1, n)]
    ans1 = [0] * n
    for i in range(2, 2 * n, 2):
        ans1[i % n] = ans1[(i - 2) % n] + arr[i % n]
    ans = [0] * n
    m = 0
    f = 1
    for a in ans1:
        m += f * a
        f = -f
    if m % 2:
        for i in range(n):
            ans1[i] += 1
        m += 1
    ans[0] = m // 2
    for i in range(1, n):
        ans[i] = ans1[i - 1] - ans[i - 1]
    x = -min(ans)
    print(*[a + x for a in ans])


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    solve()
