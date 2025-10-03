# Contest 2021, Problem D: Boss, Thirsty
# URL: https://codeforces.com/contest/2021/problem/D

# https://codeforces.com/contest/2021
# approach by TOMATO_MAT_TO: https://codeforces.com/contest/2021/submission/284574074


import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!

INF = 1 << 63


def solve_case():
    n, m = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(n)]

    # first row
    dp_right = [0] * m  # dp_right[i]: max value of any sub-array with right border at position i
    total = 0
    for i in range(m):
        dp_right[i] = total = max(0, total) + a[0][i]

    dp_left = [0] * m  # dp_left[i]: max value of any sub-array with left border at position i
    total = 0
    for i in range(m - 1, -1, -1):
        dp_left[i] = total = max(0, total) + a[0][i]

    for r in range(1, n):
        dp_right_new = [0] * m
        dp_right_new[0] = -INF  # sub-array with right position 0 would only contain one cell
        total = a[r][0]
        for c in range(1, m):
            dp_right_new[c] = max(dp_right_new[c - 1], total + max(dp_right[c - 1], dp_left[c])) + a[r][c]
            total = max(0, total) + a[r][c]
        dp_left_new = [0] * m
        dp_left_new[m - 1] = -INF  # sub-array with left position m-1 would only contain one cell
        total = a[r][m - 1]
        for c in range(m - 2, -1, -1):
            dp_left_new[c] = max(dp_left_new[c + 1], total + max(dp_right[c], dp_left[c + 1])) + a[r][c]
            total = max(0, total) + a[r][c]
        dp_right = dp_right_new
        dp_left = dp_left_new

    ans = max(max(dp_left), max(dp_right))
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))
