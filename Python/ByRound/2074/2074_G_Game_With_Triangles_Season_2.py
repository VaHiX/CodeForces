# Contest 2074, Problem G: Game With Triangles: Season 2
# URL: https://codeforces.com/contest/2074/problem/G

import sys


def max_triangle_score(n, a):
    # DP table initialized to 0
    dp = [[0] * (n + 1) for _ in range(n)]

    # Iterating over segment lengths
    for k in range(3, n + 1):
        for l in range(n - k + 1):
            r = l + k
            cur = max(dp[l + 1][r], dp[l][r - 1])
            for m in range(l + 1, r):
                cur = max(cur, dp[l][m] + dp[m][r])
                if m < r - 1:
                    cur = max(
                        cur, dp[l + 1][m] + dp[m + 1][r - 1] + a[l] * a[m] * a[r - 1]
                    )
            dp[l][r] = cur

    return dp[0][n]


# Read input
t = int(sys.stdin.readline().strip())
results = []
for _ in range(t):
    n = int(sys.stdin.readline().strip())
    a = list(map(int, sys.stdin.readline().strip().split()))
    results.append(str(max_triangle_score(n, a)))

sys.stdout.write("\n".join(results) + "\n")
