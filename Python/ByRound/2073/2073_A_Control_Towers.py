# Contest 2073, Problem A: Control Towers
# URL: https://codeforces.com/contest/2073/problem/A

r, c = map(int, input().split())
g = [input().strip() for _ in range(r)]
rcnt = [0] * r
ccnt = [0] * c
for i in range(r):
    for j in range(c):
        if g[i][j] == ".":
            rcnt[i] += 1
            ccnt[j] += 1
ans = 0
for i in range(r):
    R = rcnt[i]
    if R < 2:
        continue
    s = 0
    s2 = 0
    for j in range(c):
        if g[i][j] == ".":
            f = R + ccnt[j] - 3
            s += f
            s2 += f**2
    ans += s * s - s2 - R * (R - 1) * (R - 2)
for j in range(c):
    C = ccnt[j]
    if C < 2:
        continue
    s = 0
    s2 = 0
    for i in range(r):
        if g[i][j] == ".":
            f = C + rcnt[i] - 3
            s += f
            s2 += f**2
    ans += s * s - s2 - C * (C - 1) * (C - 2)
print(ans)
