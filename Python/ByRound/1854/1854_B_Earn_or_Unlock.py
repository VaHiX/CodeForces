# Problem: CF 1854 B - Earn or Unlock
# https://codeforces.com/contest/1854/problem/B

"""
Algorithm: Dynamic Programming with Bit Manipulation
Time Complexity: O(n * log n)
Space Complexity: O(n)

This solution uses a bitmask-based dynamic programming approach to track which positions in the deck can be unlocked up to a certain point.
It simulates the game where each card's value determines how many locked cards can be unlocked, and the goal is to maximize points earned.
The key idea is to keep track of possible states using bitmasks and update them efficiently.
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n = int(input())
a = list(map(int, input().split()))
pow2 = [1]
l = 63
for _ in range(l - 1):
    pow2.append(2 * pow2[-1])
sp = list(pow2)
for i in range(1, l):
    sp[i] ^= sp[i - 1]
m = 2 * n // l + 2
dp = [0] * m
dp[0] = 1
s, t = 0, -1
ans = 0
mi = -1
c = -1
for i in a:
    s += i
    t += 1
    if s <= t:
        break
    u, v = i // l, i % l
    if i:
        for j in range(m - 1, c, -1):
            if not dp[j]:
                continue
            dpj = dp[j]
            if u + j < m:
                dp[u + j] |= (dpj & sp[l - v - 1]) << v  # Unlocking bits
                if u + j + 1 < m:
                    dp[u + j + 1] |= dpj >> (l - v)          # Handle overflow bits
    while not dp[mi // l] & pow2[mi % l]:
        mi += 1
    ans = max(ans, s - mi)
    dp[t // l] = min(dp[t // l], dp[t // l] ^ pow2[t % l])  # Mark current position as visited
    if not (t + 1) % l:
        c += 1
print(ans)


# https://github.com/VaHiX/CodeForces/