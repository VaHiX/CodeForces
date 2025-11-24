# Problem: CF 2023 D - Many Games
# https://codeforces.com/contest/2023/problem/D

"""
Algorithm: Dynamic Programming with Probability Optimization
Approach:
1. Separate games with 100% probability into a separate sum (as they always win).
2. Group other games by their probability values.
3. For each probability group, only take the top k games (where k = 100 // (100 - p)) to avoid excessive computation.
4. Use dynamic programming to compute maximum probability of achieving a given sum of winnings (w).
5. For each possible sum, calculate expected value as (sum_p100 + s) * dp[s] and keep track of maximum.

Time Complexity: O(n + C * W) where C is the maximum possible winnings and W is the number of groups.
Space Complexity: O(C + n) for the DP array and storing grouped games.
"""

import sys
from collections import defaultdict


def solve():
    n = int(sys.stdin.readline())
    games = []
    sum_p100 = 0
    for _ in range(n):
        p, w = map(int, sys.stdin.readline().split())
        if p == 100:
            sum_p100 += w
        else:
            games.append((p, w))
    # Define capacity limit based on problem constraints
    C = 200000 * 100 // 99
    if sum_p100 > C:
        print("{0:.8f}".format(sum_p100))
        return
    # Group games by their probability
    groups = defaultdict(list)
    for p, w in games:
        groups[p].append(w)
    # Process each group: Keep only necessary number of games
    processed = []
    for p in groups:
        lst = sorted(groups[p], reverse=True)
        denominator = 100 - p
        K = 100 // denominator
        take = min(K, len(lst))
        processed.extend((p, w) for w in lst[:take])
    # Set DP capacity
    C_DP = C
    dp = [0.0] * (C_DP + 1)
    dp[0] = 1.0
    # Dynamic programming to compute probabilities for each winnings sum
    for p, w in processed:
        q = p / 100.0
        # Traverse backwards to avoid using updated values in same iteration
        for s in range(C_DP, w - 1, -1):
            if dp[s - w] * q > dp[s]:
                dp[s] = dp[s - w] * q
    # Calculate maximum expected value
    max_expected = 0.0
    for s in range(C_DP + 1):
        if dp[s] == 0.0:
            continue
        current = (sum_p100 + s) * dp[s]
        if current > max_expected:
            max_expected = current
    print("{0:.8f}".format(max_expected))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/