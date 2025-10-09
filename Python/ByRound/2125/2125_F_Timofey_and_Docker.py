# Problem: CF 2125 F - Timofey and Docker
# https://codeforces.com/contest/2125/problem/F

"""
F. Timofey and Docker

Purpose:
This code solves the problem of finding the minimum number of character changes needed to maximize the number of conference attendees who understand Timofey's report about Docker. The approach involves:

1. Preprocessing the input string `s` to compute a "mismatch vector" indicating how many characters differ from "docker" for each possible 6-character substring.
2. Using dynamic programming with optimization techniques (slope trick or binary search) to determine best coverage of intervals.
3. For each interval, we evaluate whether changing certain substrings improves coverage.
4. Ultimately, we find the best change strategy using a binary-search-like approach.

Algorithms/Techniques:
- Sliding window with suffix matching ("docker")
- Dynamic Programming with modulo indexing
- Slope trick (optimization of DP with slope changes)
- Binary search for optimal choice

Time Complexity: O(|s| + n * log(max_value)) where max_value is a large constant (~2^20).
Space Complexity: O(|s| + n)

"""

import sys

input = sys.stdin.readline
baku = []
for _ in range(int(input())):
    s = input().rstrip()
    n = int(input())
    intvs = [[int(t) for t in input().split()] for _ in range(n)]
    if len(s) < 6:
        baku.append(0)
        continue
    # v[i] stores the number of mismatches between s[i:i+6] and "docker"
    v = [0] * (len(s) - 5)
    for i in range(len(s) - 5):
        t = s[i : i + 6]
        v[i] = sum(c != d for c, d in zip(t, "docker"))
    BIG = 1 << 63

    # solve(bonus): minimum cost to make all substrings match the constraint with given bonus
    def solve(bonus):
        dp = [BIG] * 6
        dp[0] = 0
        for i in range(len(v)):
            dp[(i + 1) % 6] = min(dp[(i + 1) % 6], dp[i % 6])
            dp[i % 6] += v[i] - bonus
        return min(dp)

    # want(x): estimates the cost for a given threshold using slope trick
    def want(x):
        z = -1
        jump = 1 << 20
        while jump:
            if solve(z + jump - 1) - solve(z + jump) <= x:
                z += jump
            jump //= 2
        return solve(z) + x * z

    base = v.count(0)
    events = []
    for l, r in intvs:
        events.append(2 * l + 1)
        events.append(2 * (r + 1))
    cur = 0
    mintvs = []
    last = 0
    for ev in sorted(events):
        x = ev // 2
        if last < x:
            mintvs.append((last, x, cur))
        cur += 1 if ev & 1 else -1
        last = x
    best = 0
    for l, r, d in mintvs:
        if l > len(s) // 6:
            continue
        best = max(best, d)
    cost = BIG
    top = -1
    for l, r, d in mintvs:
        if l > len(s) // 6:
            continue
        if d < best:
            continue
        if l <= base < r:
            cost = 0
            break
        if r <= base:
            cost = min(cost, base - r + 1)
            continue
        top = l
        break
    if top > -1:
        cost = min(cost, want(top))
    baku.append(cost)
print(*baku)


# https://github.com/VaHiX/codeForces/