# Contest 1652, Problem A: Maximum Cake Tastiness
# URL: https://codeforces.com/contest/1652/problem/A

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()
    print(a[-1] + a[-2])
