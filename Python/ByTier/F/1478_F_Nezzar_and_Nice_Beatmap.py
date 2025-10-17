# Contest 1478, Problem F: Nezzar and Nice Beatmap
# URL: https://codeforces.com/contest/1478/problem/F


def dist(p, q):
    return (p[0] - q[0]) ** 2 + (p[1] - q[1]) ** 2


n = int(input())
points = []
for i in range(n):
    x, y = map(int, input().split())
    points.append((x, y))

ans = [0]
seen = [0] * n
seen[0] = 1
for i in range(1, n):
    mx = -1
    idx = -1
    for j in range(n):
        if seen[j] == 0:
            if mx < dist(points[j], points[ans[-1]]):
                mx = dist(points[j], points[ans[-1]])
                idx = j
    ans.append(idx)
    seen[idx] = 1

print(*[i + 1 for i in ans])
