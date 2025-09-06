# Contest 2129, Problem B: Stay or Mirror
# URL: https://codeforces.com/contest/2129/problem/B

for i in range(int(input())):
    n, p, s = int(input()), list(map(int, input().split())), 0
    for j in range(n):
        x = 0
        for k in range(j):
            if p[k] > p[j]:
                x += 1
        s += min(x, n - p[j] - x)
    print(s)
