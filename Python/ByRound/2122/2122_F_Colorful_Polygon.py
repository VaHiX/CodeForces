# Contest 2122, Problem F: Colorful Polygon
# URL: https://codeforces.com/contest/2122/problem/F

n = int(input())
a = [int(t) for t in input().split()]

low = []
high = []
x = y = 0
for i in range(n - 1):
    s, t = a[2 * i : 2 * (i + 1)]
    a.append(a[2 * i] + a[2 * i + 1])

    L = max(s, t)

    low.append((x, y))
    high.append((x, y + 2))
    for j in range(s - 1):
        low.append((x + 5 + j, y))
    for j in range(t - 1):
        high.append((x + 5 + j, y + 2))
    low.append((x + L + 10, y))
    high.append((x + L + 11, y + 2))
    if i < n - 2:
        low.append((x + L + 9, y - 1))
    x += L + 10
    y -= 4

print(len(low) + len(high))
for pt in low:
    print(*pt)
for pt in reversed(high):
    print(*pt)
