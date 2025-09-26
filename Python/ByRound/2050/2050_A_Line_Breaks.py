# Contest 2050, Problem A: Line Breaks
# URL: https://codeforces.com/contest/2050/problem/A

a = int(input())
for i in range(a):
    n, m = input().split()
    l = 0
    c = 0
    for j in range(int(n)):
        s = input()
        l = l + len(s)
        if l <= int(m):
            c = c + 1
    print(c)
