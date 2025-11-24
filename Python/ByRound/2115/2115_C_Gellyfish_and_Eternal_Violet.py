# Problem: CF 2115 C - Gellyfish and Eternal Violet
# https://codeforces.com/contest/2115/problem/C

# C. Gellyfish and Eternal Violet
# 
# Problem Description:
# Gellyfish wants to reduce all monster HPs to exactly 1 over m rounds.
# Each turn, a sword shines with probability p. If it shines, all monsters lose 1 HP.
# If it doesn't shine, she can choose one monster to lose 1 HP.
# The goal is to compute the maximum probability of achieving this using optimal strategy.
# 
# Algorithm:
# Uses dynamic programming combined with combinatorics and probability calculations.
# Precomputed log-factorials for efficient binomial coefficient computation.
# For each case:
# - Special handling for p=0 and p=100.
# - For general cases, uses a DP array to store probabilities of reaching certain states.
# - Combines these using the binomial distribution for the number of 'no-shine' rounds.
#
# Time Complexity: O(n * m * (n + m)) per test case in worst case
# Space Complexity: O(n * m) for dynamic programming table

import math

logf = [0]
for i in range(1, 10000):
    logf.append(logf[-1] + math.log(i))


def lcmb(n, k):
    return logf[n] - logf[n - k] - logf[k]


baku = []
for _ in range(int(input())):
    n, m, p = [int(t) for t in input().split()]
    h = [int(t) for t in input().split()]
    if p == 100:
        # If sword always shines, all monsters must be reduced perfectly
        if all(e == h[0] for e in h) and m >= h[0] - 1:
            baku.append(1)
        else:
            baku.append(0)
        continue
    if p == 0:
        # If sword never shines, check if can reduce total HP to n using m moves
        if m >= sum(h) - n:
            baku.append(1)
        else:
            baku.append(0)
        continue
    p /= 100
    mh = min(h)
    extra = sum(h) - mh * n  # excess HP beyond min level
    stair = (mh - 1) * n  # max steps required to reduce all monsters to 1
    v = [0] * (stair + 1 + n)
    v[stair] = 1  # Base case: all monsters at level 1
    save = [v[: stair + 1 : n]]  # Save states for DP
    for _ in range(m - extra):  # Run m - extra steps using dynamic programming
        for i in range(stair):
            v[i] = p * max(v[i], v[i + n]) + (1 - p) * max(v[i], v[i + 1])
        save.append(v[: stair + 1 : n])
    if extra == 0:  # No surplus HP
        baku.append(save[m][0])
        continue
    tot = 0
    for big in range(m - extra + 1):  # Try all valid number of shineless rounds
        x = lcmb(extra + big - 1, extra - 1)
        x += math.log(1 - p) * extra
        x += math.log(p) * big
        tot += math.exp(x) * save[m - big - extra][min(mh - 1, big)]  # Combine probabilities
    baku.append(tot)
print(*baku)


# https://github.com/VaHiX/codeForces/