# Contest 2036, Problem E: Reverse the Rivers
# URL: https://codeforces.com/contest/2036/problem/E

from bisect import bisect_left, bisect_right
import sys

input = sys.stdin.readline

n, k, q = map(int, input().split())
A = [list(map(int, input().split())) for _ in range(n)]
P = [[0] * (n + 1) for _ in range(k)]
for i in range(n):
    for j in range(k):
        P[j][i + 1] = P[j][i] | A[i][j]

res = []

for _ in range(q):
    m = int(input())
    L = 1
    R = n + 1

    for _ in range(m):
        r, o, c = input().split()
        r = int(r) - 1
        c = int(c)

        if o == "<":
            j = bisect_left(P[r], c)
            R = min(R, j)
        else:
            j = bisect_right(P[r], c)
            L = max(L, j)

    ans = L
    if L >= R:
        ans = -1

    res.append(ans)

print("\n".join(map(str, res)))
