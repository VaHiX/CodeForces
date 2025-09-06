# Contest 1016, Problem C: Vasya And The Mushrooms
# URL: https://codeforces.com/contest/1016/problem/C

R, G = lambda: map(int, input().split()), range
(n,) = R()
g = [[*R()] for _ in G(2)]
p = [0] * 2
s = sum(2 * j * g[j & 1][j] + (2 * j + 1) * g[(j + 1) & 1][j] for j in G(n))
z = s  # zigzag
for j in G(1, n):
    for i in G(2):
        p[i] += 2 * j * (g[1 ^ i][n - 1 - j] - g[i][n - j])
    s += p[j & 1 ^ (n + 1) & 1]
    z = max(z, s)
print(z)
