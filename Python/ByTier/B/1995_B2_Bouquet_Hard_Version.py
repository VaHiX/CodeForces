# Problem: CF 1995 B2 - Bouquet (Hard Version)
# https://codeforces.com/contest/1995/problem/B2

"""
B2. Bouquet (Hard Version)

Purpose:
    This code solves a variant of the knapsack-like problem where the goal is to maximize the number of petals in a bouquet under certain constraints:
    - All flowers used must differ by at most 1 petal count.
    - The total cost (number of petals) must not exceed m coins.
    - Each flower type has a given number of petals and quantity available.

Algorithms/Techniques:
    - Greedy with enumeration of valid "petal difference = 1" pairs
    - For each possible pair (t, t+1), compute the maximum total petals that can be formed using at most m coins.
    - Uses dictionary mapping to store petal counts and quantities.

Time Complexity:
    O(n * log n) per test case due to sorting in input processing and linear iteration over unique petal types.

Space Complexity:
    O(n) for storing flower data in a dictionary.

"""

for _ in range(int(input())):
    n, m = map(int, input().split())
    # Create a dictionary mapping petal count to quantity of flowers available
    cnt = {t: v for t, v in zip(map(int, input().split()), map(int, input().split()))}
    mx = 0
    
    # Iterate through all unique petal counts
    for t, v in cnt.items():
        w = cnt.get(t + 1, 0)  # Get quantity of flowers with (t+1) petals
        
        # Determine how many flowers of type 't' we can afford
        countA = min(m // t, v)
        a = t * countA  # Total petals from type 't' flowers
        diff = m - a    # Remaining coins after buying 'countA' flowers of type 't'

        # Determine how many flowers of type 't+1' we can afford with remaining coins
        countB = min(diff // (t + 1), w)
        b = (t + 1) * countB  # Total petals from type 't+1' flowers

        # Add leftover petals that can be obtained by possibly swapping some flowers
        # Ensuring no more than available quantity of either flower type is used
        mx = max(mx, a + b + min((m - a - b), w - countB, countA))

    print(mx)


# https://github.com/VaHiX/codeForces/