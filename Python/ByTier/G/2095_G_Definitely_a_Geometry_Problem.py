# Contest 2095, Problem G: Definitely a Geometry Problem
# URL: https://codeforces.com/contest/2095/problem/G

pi = 3.141592653589793


n, k = map(int, input().split())
pts = []


for _ in range(n):
    xi, yi = map(int, input().split())
    pts.append((xi, yi))

x0, y0 = min(pts)


x = []

for xi, yi in pts:
    x.append(((x0 - xi) ** 2 + (y0 - yi) ** 2) ** 0.5)


x.sort()

poss = []
for i in range(n - k + 1):
    poss.append(x[i + k - 1] - x[i])

z = min(poss)
print(pi * z * z / 4)
