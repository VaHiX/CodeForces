# Problem: CF 1774 F2 - Magician and Pigs (Hard Version)
# https://codeforces.com/contest/1774/problem/F2

"""
Algorithm: Simulation with Lazy Propagation and Binary Search
Time Complexity: O(n * log n)
Space Complexity: O(n)

This solution simulates the given operations on pigs using a combination of
lazy propagation and binary search techniques to efficiently manage
the repeated operations. The key idea is to track how many times each operation
has been applied and use that to determine pig survival counts.

The core logic involves:
1. Tracking cumulative health reductions (s2, s3)
2. Storing operation history to support repeat operations
3. Using binary search via precomputed powers of 2 to efficiently count surviving pigs
"""

import sys

input = sys.stdin.readline

MOD = 998244353
INV2 = MOD // 2 + 1  # Modular inverse of 2
P2 = [pow(2, i, MOD) for i in range(31)]  # Precomputed powers of 2 mod MOD
X = 10**9  # A large value to mark end of operation sequence

s2 = 0  # Cumulative health reduction from type 2 operations
s3 = 0  # Another cumulative health reduction (used to track repetition)
s = []  # List to store cumulative health reductions in a way to simulate repeats
ipt = []  # Stores all the operations in a processed format

# Read number of operations
(n,) = map(int, input().strip().split())

# Process each operation
for _ in range(n):
    i = list(map(int, input().strip().split()))
    op = i[0]
    if op == 1:
        # Create pig with x health points
        ipt.append(i[1])
    elif op == 2:
        # Apply health reduction to all living pigs
        s2 += i[1]
        s3 += i[1]
        ipt.append(-i[1])
    elif op == 3 and s3 < X:
        # Repeat previous operations (simulate)
        s.append(s3)
        s3 *= 2
        ipt.append(0)

ans = 0
s.append(X + 1)  # Sentinel value to mark end
l = 0            # Index tracking of current repetition level
l0 = 0           # Index tracking of base repetition level
while l0 < len(s) and s[l0] == 0:
    l0 += 1
p2l0 = pow(2, l0, MOD)  # Modular power of 2 for base level

for i in ipt:
    if i == 0:
        # Operation was a repeat, update repetition level
        if l < l0:
            p2l0 = p2l0 * INV2 % MOD
        l += 1
    elif i < 0:
        # Health reduction applied, adjust s2
        s2 += i
    elif i > s2:
        # Create a pig and check how many pigs survive based on health
        t = 0
        i -= s2
        r = len(s) - 1
        while r > l and s[r] >= i:
            r -= 1
            if s[r] * 2 < i:
                # Use powers of 2 for fast computation of combinations
                t = (t + P2[r - max(l, l0) + 1]) % MOD
                break
            elif s[r] < i:
                # Add combinations for current level
                t = (t + P2[r - max(l, l0)]) % MOD
                i -= s[r]
        if not (s[r] * 2) < i:
            t += 1
        ans = (ans + t * p2l0) % MOD

print(ans)


# https://github.com/VaHiX/CodeForces/