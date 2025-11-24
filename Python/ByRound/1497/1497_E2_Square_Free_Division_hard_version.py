# Problem: CF 1497 E2 - Square-Free Division (hard version)
# https://codeforces.com/contest/1497/problem/E2

"""
Algorithm: Dynamic Programming with Sliding Window

This solution addresses the problem of dividing an array into the minimum number of continuous segments such that no two numbers in the same segment have a product that is a perfect square. We are allowed to change at most k elements in the array to achieve this.

Key ideas:
1. For each number, reduce it to its square-free form (remove all square factors).
2. Use a sliding window technique to determine the minimum number of segments needed for a fixed number of changes.
3. Apply dynamic programming to find the optimal number of segments considering up to k changes.

Time Complexity: O(n * k * log(max(a_i)) + n * k^2)
Space Complexity: O(n * k)

The algorithm works by:
- Precomputing the square-free representation of numbers
- Using sliding window to find optimal segment boundaries for varying numbers of changes
- Using DP to combine results optimally

"""

MAXN = 10**7 + 5
INF = 10**18

# Precompute the square-free representation of each number up to MAXN
to = [i for i in range(MAXN)]
for i in range(2, 10**4):
    for j in range(i * i, MAXN, i * i):
        while to[j] % (i * i) == 0:
            to[j] //= i * i

_t = int(input())


def read():
    return [int(x) for x in input().split()]


s = [0] * MAXN
for __ in range(_t):
    n, k = read()
    a = [0] + read()
    # Transform array elements to their square-free forms
    a = [to[a[i]] for i in range(0, n + 1)]

    # f[i][ct]: minimum starting index for a segment ending at i with ct changes allowed
    f = [[0] * (k + 1) for _ in range(n + 2)]
    for ct in range(k + 1):
        j, now = 1, 0
        for i in range(1, n + 1):
            s[a[i]] += 1
            if s[a[i]] >= 2:
                now += 1
                if now > ct:
                    # Shrink window until we're within allowed changes
                    while now > ct:
                        now -= s[a[j]] >= 2
                        s[a[j]] -= 1
                        j += 1
            f[i][ct] = j
        for x in a:
            s[x] = 0

    # dp[i][j]: minimum segments for first i elements with j changes used
    dp = [[INF] * (k + 1) for _ in range(n + 2)]
    for j in range(0, k + 1):
        dp[0][j] = 0
    for i in range(1, n + 1):
        for j in range(k + 1):
            for p in range(j + 1):
                # Try using p changes for previous segment
                dp[i][j] = min(dp[i][j], dp[f[i][p] - 1][j - p] + 1)

    print(min(dp[n][0:]))


# https://github.com/VaHiX/CodeForces/