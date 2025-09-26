# Contest 2043, Problem B: Digits
# URL: https://codeforces.com/contest/2043/problem/B

for s in [*open(0)][1:]:
    n, d = map(int, s.split())
    print(
        1,
        *[3] * (n > 2 or d % 3 < 1)
        + [5] * (d == 5)
        + [7] * (n > 2 or d == 7)
        + [9] * (d > 8 or d % 3 < 1 < n - 1 or n > 5)
    )
