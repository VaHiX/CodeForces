# Contest 2121, Problem A: Letter Home
# URL: https://codeforces.com/contest/2121/problem/A

t = int(input())
for i in range(t):
    n, s = map(int, input().split())
    a = list(map(int, input().split()))
    l, h = a[0], a[-1]
    r = (h - l) + min(abs(s - l), abs(s - h))
    print(r)
