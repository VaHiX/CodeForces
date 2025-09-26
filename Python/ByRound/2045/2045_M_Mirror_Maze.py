# Contest 2045, Problem M: Mirror Maze
# URL: https://codeforces.com/contest/2045/problem/M

n, m = map(int, input().split())
a, d = [input() for i in range(n)], []
k = n * m - sum(i.count(".") for i in a)
for i in "NESW":
    for j in range(n):
        b = set()
        x, y, dx, dy = {
            "N": (j, 0, 0, 1),
            "E": (m - 1, j, -1, 0),
            "S": (j, n - 1, 0, -1),
            "W": (0, j, 1, 0),
        }[i]
        while 0 <= x < m and 0 <= y < n:
            if a[y][x] in "/\\":
                dx, dy = [(-dy, -dx), (dy, dx)][a[y][x] != "/"]
                b.add((x, y))
            x += dx
            y += dy
        if len(b) == k:
            d += [f"{i}{j+1}"]
print(len(d))
if d:
    print(*d, sep=" ")
