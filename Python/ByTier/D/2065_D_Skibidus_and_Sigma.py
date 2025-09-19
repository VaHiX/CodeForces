# Contest 2065, Problem D: Skibidus and Sigma
# URL: https://codeforces.com/contest/2065/problem/D

for _ in range(int(input())):
    n, m = list(map(int, input().split()))
    s = 0
    b = []
    for i in range(n):
        x = list(map(int, input().split()))
        a = 0
        for i in x:
            a += i
            s += a
        b.append(a)
    b.sort()
    for i in range(n):
        s += b[i] * m * i
    print(s)
