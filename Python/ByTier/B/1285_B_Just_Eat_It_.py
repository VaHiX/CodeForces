# Contest 1285, Problem B: Just Eat It!
# URL: https://codeforces.com/contest/1285/problem/B

from sys import stdin

input = lambda: stdin.readline().strip()
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s1, s2 = 0, 0
    for i in range(n):
        s1 += a[i]
        s2 += a[-i - 1]
        if s1 <= 0 or s2 <= 0:
            print("NO")
            break
    else:
        print("YES")
