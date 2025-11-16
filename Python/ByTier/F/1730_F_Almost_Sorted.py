# Problem: CF 1730 F - Almost Sorted
# https://codeforces.com/contest/1730/problem/F

"""
Algorithm: Dynamic Programming with Bitmask
Time Complexity: O(n * k * 2^k)
Space Complexity: O(k * 2^k)

This problem involves finding the minimum number of inversions in a permutation q
that satisfies a constraint related to the original permutation p and parameter k.
The key idea is to use dynamic programming with bitmask representation to track
valid configurations and minimize inversions.

The DP state tracks:
- Position in the permutation (p)
- Current "window" size (x)
- Bitmask representing which values are currently in use (mask)

The constraint p_{q_i} <= p_{q_j} + k ensures that elements in q maintain a relative order
based on their values in p.

The solution processes elements and builds valid sequences while tracking minimum inversions.
"""

import sys
import time

start_time = time.process_time()

INF = int(1e8)
N = 5050
K = 10
M = (1 << 8) + 3

n, k = map(int, sys.stdin.readline().strip().split())
a = list(map(int, sys.stdin.readline().strip().split()))
a = [x - 1 for x in a]  # Convert to 0-indexed
b = [0] * N
dp = [[[INF] * (1 << K) for _ in range(K + 1)] for _ in range(2)]
ppc = [0] * ((1 << 17) + 3)
I = 0

# Precompute population count for all masks
for mask in range(1, (1 << 17)):
    ppc[mask] = ppc[mask >> 1] + (mask & 1)

# Build transition matrix b based on constraints
for i in range(n):
    for j in range(i + 1, n):
        if abs(a[i] - a[j]) <= k:
            # Set bits in b[j] to represent valid transitions
            b[a[j]] ^= 1 << (k + a[i] - a[j])
        elif a[i] > a[j]:
            # Count initial inversions
            I += 1

# Precompute valid transitions for first k elements
for i in range(min(n, k)):
    for j in range(i + 1, k + 1):
        b[i] ^= 1 << (k - j)

# Initialize DP with base case (I inversions)
dp[0][0][(1 << k) - 1] = 2 * I

# Main DP loop over all positions
for p in range(n):
    # Reset next DP state
    for i in range(K + 1):
        for j in range(1 << K):
            dp[1][i][j] = INF

    # Process current state
    for x in range(K + 1):
        for mask in range(1 << K):
            if dp[0][x][mask] == INF:
                continue

            # Try all possible next positions (within k distance)
            for y in range(-k, k + 1):
                if p + y < 0 or p + y >= n:
                    continue

                w = dp[0][x][mask]  # Current weight/cost
                nx = x - 1         # New window size
                nmask = 0          # New mask

                # Case 1: Current element comes before next element
                if p - 1 + x < p + y:
                    nx = y
                    nmask = mask | (1 << k)
                    d = (p + y) - (p - 1 + x)
                    nmask += 1

                    if ((nmask >> d) << d) != nmask:
                        continue

                    nmask >>= d
                    nmask -= 1
                    w += ppc[nmask ^ b[p + y]]  # Add contribution of new element
                    dp[1][nx][nmask] = min(dp[1][nx][nmask], w)

                # Case 2: Current element comes after next element
                elif p - 1 + x > p + y:
                    d = (p - 1 + x) - (p + y)
                    if d > k:
                        continue

                    d = k - d
                    if (mask >> d) & 1:
                        continue

                    nmask = mask | (1 << d)
                    nx = x - 1
                    z = mask | (1 << k)
                    z += 1
                    z <<= k - d
                    z -= 1
                    w += ppc[z ^ b[p + y]]
                    dp[1][nx][nmask] = min(dp[1][nx][nmask], w)

    # Swap DP states
    for i in range(K + 1):
        for mask in range(1 << K):
            dp[0][i][mask] = dp[1][i][mask]

# Find minimum among all valid states
ans = INF
for i in range(K + 1):
    for mask in range(1 << K):
        ans = min(ans, dp[0][i][mask])

print(ans // 2)


# https://github.com/VaHiX/CodeForces/