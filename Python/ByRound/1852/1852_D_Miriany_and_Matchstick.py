# Problem: CF 1852 D - Miriany and Matchstick
# https://codeforces.com/contest/1852/problem/D

"""
Problem: Fill a 2×n grid with characters A or B such that the number of adjacent pairs of cells with different characters equals k.

Approach:
- Use dynamic programming to track valid ranges of possible differences for each position in the second row.
- For each cell, calculate the contribution of previous state to current state.
- Use bit manipulation and modular arithmetic to optimize space.
- After DP, backtrack to construct the result string.

Time Complexity: O(n)
Space Complexity: O(n)

Algorithms/Techniques: Dynamic Programming with bit manipulation, backtracking.
"""

import sys

input = sys.stdin.readline

t = int(input())


P = 6

out = []

for _ in range(t):
    n, k = map(int, input().split())

    dp = [-1] * (n * 4 * P)

    s = list(map(ord, input().strip()))
    for i in range(n):
        s[i] -= 65

    # Adjust k based on adjacent pairs in first row
    for i in range(n - 1):
        k -= s[i] ^ s[i + 1]

    if k < 0:
        out.append("NO")
        continue

    # Add function to update dp table
    def add(i, t, l, r):
        x = l % P
        assert x == r % P

        ind = 4 * P * i + 2 * P * t + 2 * x

        if dp[ind] == -1:
            dp[ind] = l
            dp[ind + 1] = r
        else:
            dp[ind] = min(dp[ind], l)
            dp[ind + 1] = max(dp[ind + 1], r)

    # Initialize first column
    for i in range(n):
        if i == 0:
            add(i, 0, s[0], s[0])
            add(i, 1, 1 - s[0], 1 - s[0])
            continue

        # For each previous state, compute new states
        for t0 in range(2):
            for x in range(P):
                ind = 4 * P * (i - 1) + 2 * P * t0 + 2 * x
                if dp[ind] == -1:
                    continue

                l = dp[ind]
                r = dp[ind + 1]

                for t1 in range(2):
                    av = (t0 ^ t1) + (s[i] ^ t1)

                    add(i, t1, l + av, r + av)

    # Check if solution exists
    def poss(i, k, t):
        ind = 4 * P * i + 2 * P * t + 2 * (k % P)

        l0 = dp[ind]
        r0 = dp[ind + 1]

        return 0 <= l0 <= k <= r0

    if poss(n - 1, k, 0):
        out.append("YES")
        tc = 0
    elif poss(n - 1, k, 1):
        out.append("YES")
        tc = 1
    else:
        out.append("NO")
        continue

    # Backtrack to construct the result
    resb = []
    for i in range(n - 1, -1, -1):
        resb.append(tc)

        if i == 0:
            continue

        t1 = tc

        tn = -1

        for t0 in range(2):
            av = (t0 ^ t1) + (s[i] ^ t1)

            if poss(i - 1, k - av, t0):
                tn = t0
                k -= av
                break

        assert tn != -1

        tc = tn

    s = "AB"
    res = map(lambda x: s[x], resb[::-1])

    out.append("".join(res))


print("\n".join(out))


# https://github.com/VaHiX/CodeForces/