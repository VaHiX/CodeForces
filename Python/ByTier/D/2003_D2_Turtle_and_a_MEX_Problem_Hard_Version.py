# Problem: CF 2003 D2 - Turtle and a MEX Problem (Hard Version)
# https://codeforces.com/contest/2003/problem/D2

"""
D2. Turtle and a MEX Problem (Hard Version)

Algorithm:
- For each test case, we compute the maximum value of mex(x, S) where S is a sequence,
  starting from x=0 to m.
- Use bitmasking with XOR operations to encode pairs of integers efficiently.
- Build an array dp such that dp[i] stores the highest reachable mex value when starting at i.
- Process all sequences and find for each position the max mex reachable.
- Sum up dp values in a sliding window fashion.

Time Complexity: O(sum(n) * log(max_value))
Space Complexity: O(max_value) where max_value ~ 1e9, but constrained to ~2*10^5

"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Encode two integers (u,v) into one integer for fast lookup
    return u << 20 ^ v


t = int(input())
ans = []
l = 2 * pow(10, 5) + 5
color, c = [0] * l, 1
for _ in range(t):
    n, m = map(int, input().split())
    ma, z = 0, [0] * n
    # Traverse each sequence and mark presence of numbers in 'color' array
    for j in range(n):
        a = list(map(int, input().split()))[1:]
        for i in a:
            if i < l:
                color[i] = c
        x, u, v = 0, 2, [0] * 2
        # Find last two unique unmarked indices
        while color[x] == c or u:
            if color[x] ^ c:
                u -= 1
                v[u] = x
            x += 1
        z[j] = f(v[1], v[0])  # Encode these two values into one
        ma = max(ma, v[0])
        c += 1
    # Initialize DP array
    dp = [i for i in range(ma + 1)]
    cnt = [0] * (ma + 1)
    # Process encoded pairs and update dp accordingly
    for i in sorted(z, reverse=True):
        j, k = i >> 20, i & 0xFFFFF  # Extract first and second value from encoded form
        dp[j] = max(dp[j], dp[k])   # Update with the maximum possible mex
        cnt[j] += 1                 # Count how many times this state arises
    m0 = max(z) >> 20
    for i in range(ma + 1):
        if cnt[i] > 1:
            m0 = max(m0, dp[i])      # Adjust based on repeated entries

    v = min(ma, m)
    ans0 = (m * (m + 1) - v * (v + 1)) >> 1  # Arithmetic sum from 0 to m minus 0 to v
    for i in range(v + 1):
        ans0 += max(m0, dp[i])   # Add the computed maximum values up to v
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/