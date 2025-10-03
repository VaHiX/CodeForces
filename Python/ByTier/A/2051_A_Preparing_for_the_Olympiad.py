# Contest 2051, Problem A: Preparing for the Olympiad
# URL: https://codeforces.com/contest/2051/problem/A

for _ in range(int(input())):
    t = int(input())
    c = 0
    a = [*map(int, input().split())]
    b = [*map(int, input().split())]
    for i in range(t - 1):
        if 0 < a[i] - b[i + 1]:
            c += a[i] - b[i + 1]
    print(c + a[-1])
