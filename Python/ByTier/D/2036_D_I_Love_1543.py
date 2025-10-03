# Contest 2036, Problem D: I Love 1543
# URL: https://codeforces.com/contest/2036/problem/D

for _ in range(int(input())):
    n, m = map(int, input().split())
    g = [input() for _ in range(n)]
    t = 0
    L = min(n, m) // 2
    for i in range(L):
        p1 = g[i][i : m - i]
        p2 = "".join(g[j][m - i - 1] for j in range(i + 1, n - i - 1))
        p3 = g[n - i - 1][i : m - i][::-1]
        p4 = "".join(g[j][i] for j in range(i + 1, n - i - 1))[::-1]
        s = p1 + p2 + p3 + p4
        t += (s + s[:3]).count("1543")
    print(t)
