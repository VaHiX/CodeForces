# Contest 2026, Problem A: Perpendicular Segments
# URL: https://codeforces.com/contest/2026/problem/A


for _ in range(int(input())):
    x, y, k = map(int, input().split())
    m = min(x, y)
    print(0, 0, m, m)
    print(m, 0, 0, m)
