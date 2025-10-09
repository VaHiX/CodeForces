# Contest 1785, Problem A: Monsters (easy version)
# URL: https://codeforces.com/contest/1785/problem/A


import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    [n] = list(map(int, input().split()))
    arr = list(map(int, input().split()))
    tt1 = 0
    ans = 0
    arr.sort()
    for i in range(n):
        if arr[i] > tt1:
            tt1 += 1
        ans += arr[i] - tt1
    print(ans)


# solve()
for _ in range(int(input())):
    solve()
