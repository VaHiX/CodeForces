# Problem: CF 1829 G - Hits Different
# https://codeforces.com/contest/1829/problem/G

"""
Code Purpose:
This code computes the sum of squared labels of all cans that fall when a single can labeled n^2 is hit in a pyramid of cans.
The pyramid has 2023 rows, and when a can is hit, all cans directly above it (and above those) fall, following a specific pattern.

Algorithms/Techniques:
- Dynamic Programming with precomputation of sums for each position in the pyramid.
- The pyramid is built row by row, and for each cell, we compute the sum of all falling cans that would result from hitting that cell.

Time Complexity: O(K^2) where K = 2024, since we compute dp for all positions up to K*K.
Space Complexity: O(K^2) for storing the dp array.

"""
import sys

input = sys.stdin.readline

K = 2024
dp = [0] * (K * K)
dp[1] = 1
dp[2] = 5
dp[3] = 10
cnt = 3
for row in range(3, K):
    cnt += 1
    # Compute the sum for the first can in the row
    dp[cnt] = cnt * cnt + dp[cnt - row + 1]

    # Compute sums for the middle cans in the row
    for _ in range(row - 2):
        cnt += 1
        dp[cnt] = (
            cnt * cnt + dp[cnt - row] + dp[cnt - row + 1] + -dp[cnt - 2 * (row - 1)]
        )

    # Compute the sum for the last can in the row
    cnt += 1
    dp[cnt] = cnt * cnt + dp[cnt - row]


T = int(input())
out = []
for _ in range(T):
    n = int(input())
    ans = dp[n]
    out.append(ans)

print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/