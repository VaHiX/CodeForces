# Contest 1776, Problem A: Walking Boy
# URL: https://codeforces.com/contest/1776/problem/A

for _ in range(int(input())):
    n = int(input())
    l = [0] + list(map(int, input().split())) + [1440]
    c = 0
    for i in range(n + 1):
        c += (l[i + 1] - l[i]) // 120
    if c >= 2:
        print("YES")
    else:
        print("NO")
