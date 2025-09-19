# Contest 1906, Problem A: Easy As ABC
# URL: https://codeforces.com/contest/1906/problem/A

arr = []
for i in range(3):
    arr.append(input())

dirs = [(0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1), (1, 0), (1, 1)]

ans = ["CCC"]


def solve(s, i, j, h):
    if len(s) != 3:
        for x, y in dirs:
            if -1 < x + i < 3 and -1 < y + j < 3 and (x + i, y + j) not in h:
                solve(s + arr[i + x][j + y], i + x, j + y, h + [(i + x, j + y)])
    else:
        if ans[0] > s:
            ans[0] = s


for i in range(3):
    for j in range(3):
        solve(arr[i][j], i, j, [(i, j)])

print(ans[0])
