# Problem: CF 1753 E - N Machines
# https://codeforces.com/contest/1753/problem/E

# Purpose: Optimize the order of machines in a production chain to maximize the final output value
# Algorithms: 
#   1. Group machines into additive and multiplicative groups
#   2. Use dynamic programming with bitmasking to try different combinations of moving multiplicative machines
#   3. For each combination, use binary search to find optimal number of additive machines to move
#   4. Calculate maximum possible value for each valid configuration
# Time Complexity: O(2^k * log(max_val) * n * log(n)) where k is number of unique multiplicative values
# Space Complexity: O(n)

import sys
from bisect import bisect

input = sys.stdin.readline

n, b, p, m = map(int, input().split())

# Store additive and multiplicative machines separately
adds = []  # Each element is a list of additive values in a group
curr = []  # Current additive machines being processed
mults = []  # Multiplicative machine values

i = 0
for _ in range(n):
    t, v = input().split()
    v = int(v)

    if t == "*":
        # If multiplicative machine with value 1, skip (no effect)
        if v == 1:
            continue
        # Sort current additive machines and add to adds list
        curr.sort()
        adds.append(curr)
        mults.append(v)
        curr = []
    else:
        # Add additive machine to current group
        curr.append(v)

# Don't forget the last group of additive machines
curr.sort()
adds.append(curr)

# Precompute prefix sums for additive groups
pref = []
for l in adds:
    np = [0]
    for v in l[::-1]:  # Reverse iteration to compute suffix sums
        np.append(v + np[-1])
    pref.append(np)

y = len(mults)  # Number of multiplicative machines
un_m = sorted(set(mults))  # Unique multiplicative values
z = len(un_m)  # Number of unique multiplicative values
ct_m = [0] * z  # Count of each unique multiplicative value
for v in mults:
    for i in range(z):
        if un_m[i] == v:
            ct_m[i] += 1

from itertools import product

poss = []

assert len(adds) == y + 1  # Verify grouping is correct

# Try all combinations of moving multiplicative machines
for tup in product(*[range(ct + 1) for ct in ct_m]):
    # Calculate coins remaining after moving multiplicative machines
    rem_adds = (b - m * sum(tup)) // p

    if rem_adds < 0:
        continue

    # Create mapping from unique multiplicative values to how many we're moving
    d = {}
    for i in range(z):
        d[un_m[i]] = tup[i]

    # Calculate the result of applying multiplicative machines that we're not moving
    end = 1
    used = [0] * y  # Track which multiplicative machines are moved/used

    for i in range(y):
        if d[mults[i]]:
            used[i] = 1
            d[mults[i]] -= 1
            end *= mults[i]

    # Precompute which parts of chain would be affected by moved machines
    seg_mult = [1]
    for i in range(y - 1, -1, -1):
        if used[i] == 0:
            seg_mult.append(seg_mult[-1] * mults[i])
        else:
            seg_mult.append(seg_mult[-1])
    seg_mult.reverse()

    # Calculates the additional effect of moving machines in current configuration
    exc = [seg_mult[0] - v for v in seg_mult]

    # Count number of additive machines affected by moving machines
    init_tot = 0
    for j in range(y + 1):
        if exc[j] != 0:
            init_tot += len(adds[j])

    # Binary search to find maximum number of additive machines that can be moved
    lo = 0
    hi = 10**18 + 100
    while hi - lo > 1:
        mid = lo + (hi - lo) // 2

        tot = init_tot
        for j in range(y + 1):
            if exc[j] == 0:
                continue

            limit = (mid - 1) // exc[j]

            diff = bisect(adds[j], limit)
            tot -= diff

        if tot >= rem_adds:
            lo = mid
        else:
            hi = mid

    # Calculate final value for this configuration
    tot = seg_mult[0]
    ct = 0
    for j in range(y + 1):
        tot += pref[j][-1] * seg_mult[j]

        if exc[j] == 0:
            continue

        limit = (lo - 1) // exc[j]

        s_ct = len(adds[j]) - bisect(adds[j], limit)

        tot += pref[j][s_ct] * exc[j]
        ct += s_ct

    if lo != 0:
        assert ct >= rem_adds
        tot -= lo * (ct - rem_adds)

    poss.append(tot * end)

# Output maximum possible value
print(max(poss))


# https://github.com/VaHiX/CodeForces/