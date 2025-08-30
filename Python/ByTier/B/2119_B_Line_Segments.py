# Contest 2119, Problem B: Line Segments
# URL: https://codeforces.com/contest/2119/problem/B

from math import sqrt

t = int(input())
for tc in range(t):
    n = int(input())
    x0, y0, x1, y1 = map(int, input().split())
    a = list(map(int, input().split()))
    dis = sqrt(((x0 - x1) ** 2 + (y0 - y1) ** 2))
    if max(0, 2 * max(a) - sum(a)) <= dis <= sum(a):
        print("YES")
    else:
        print("NO")
