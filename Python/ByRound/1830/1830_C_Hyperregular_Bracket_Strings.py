# Problem: CF 1830 C - Hyperregular Bracket Strings
# https://codeforces.com/contest/1830/problem/C

"""
Algorithm: Dynamic Programming with Segment Events and Catalan Numbers

This solution counts the number of hyperregular bracket sequences of length n,
where every given interval [l_i, r_i] must form a valid bracket subsequence.

Approach:
1. Use a "sweep line" technique with random hash values to detect active intervals at each position.
2. For each position i, determine which intervals are active and encode this state with a bitmask.
3. Count how many positions belong to each unique active interval configuration.
4. For each such configuration of length x, multiply by the number of valid bracket sequences of length x.
   This is computed using the Catalan number formula: C_n = (2n)! / ((n+1)! * n!) = (1/(n+1)) * C(2n, n).

Time Complexity: O(n + k) per test case, amortized due to hashing
Space Complexity: O(n + k) for storing events and interval lengths

Note: The usage of random hashes reduces the probability of collision,
but in this implementation it's acceptable for the problem constraints.
"""

import sys

input = sys.stdin.buffer.readline

from collections import defaultdict
from random import randrange

MAXN = 6 * 10**5 + 1
MOD = 998244353

# Precompute factorials and inverse factorials for combinations
fac = [1] * MAXN
ifac = [0] * MAXN

for i in range(2, MAXN):
    fac[i] = fac[i - 1] * i % MOD
ifac[MAXN - 1] = pow(fac[MAXN - 1], -1, MOD)
for i in range(MAXN - 2, -1, -1):
    ifac[i] = ifac[i + 1] * (i + 1) % MOD


# Function to calculate the number of valid bracket sequences of length n
def rbs(n):
    # If n is odd, there can't be a valid bracket sequence
    return (
        0
        if n & 1
        else fac[n] * (ifac[n // 2] ** 2 % MOD) % MOD * pow(n // 2 + 1, -1, MOD) % MOD
    )


for _ in range(int(input())):
    n, k = map(int, input().split())

    # Events array to mark start and end of intervals
    events = [[] for _ in range(n + 2)]

    for seg in range(k):
        l, r = map(int, input().split())
        x = randrange(1 << 64)
        events[l].append(x)      # Start of interval
        events[r + 1].append(x)  # End of interval (exclusive)

    length = defaultdict(int)

    active_hash = 0
    for i in range(1, n + 1):
        # Process events occurring at position i
        for x in events[i]:
            active_hash ^= x  # Toggle the bit for interval x

        # Count how many times each state occurs
        length[active_hash] += 1

    ans = 1

    # Multiply the result by the number of valid sequences for each group
    for x in length.values():
        ans = (ans * rbs(x)) % MOD

    print(ans)


# https://github.com/VaHiX/CodeForces/