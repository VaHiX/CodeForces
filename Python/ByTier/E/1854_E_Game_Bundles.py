# Problem: CF 1854 E - Game Bundles
# https://codeforces.com/contest/1854/problem/E

"""
Purpose: 
This code solves the problem of constructing a set of games with specific enjoyment values such that exactly m distinct game bundles can be formed, where each bundle sums to exactly 60.

Approach:
- Start with a random set of small game values.
- Iteratively add new game values to increase the number of bundles that sum to 60.
- The key data structure is an array `curr` where `curr[i]` represents the number of ways to form a sum of `i` using the current games.
- A greedy strategy is used to choose which new value to add in order to approach the target number `m` of bundles.

Time Complexity: O(60 * log(60) * 60) ~ O(1) due to constant limits
Space Complexity: O(60) ~ O(1) due to constant limits

Algorithms/Techniques:
- Dynamic Programming (for counting subsets that sum to a target)
- Greedy selection heuristic
- Randomized generation with iterative refinement
"""

import sys
from random import randint

m = int(input())


def add(x):
    # Update the dp array to include the new value x
    # This simulates adding x to all previous possible sums
    for i in range(60 - x, -1, -1):
        curr[i + x] += curr[i]

    # Add the game value to the list of games
    l.append(x)


while True:
    # curr[i] stores the number of ways to reach sum i
    curr = [1] + [0] * 60
    l = []

    # Randomly initialize with a small number of games (between 20 and 40)
    zz = randint(20, 40)

    for i in range(zz):
        add(randint(1, 2))  # Add random small values (1 or 2)

    # Keep adding games until the number of bundles reaches or exceeds m
    while m > curr[60] and (len(l)) <= 60:
        want = m - curr[60]  # Difference between desired and current bundles

        # Generate possible sums and sort by their counts in descending order
        poss = list(range(30))
        poss.sort(key=lambda x: curr[x], reverse=True)

        # Greedily choose the best next value to add
        for i in poss:
            if curr[i] <= want:
                add(60 - i)  # Add a value that will help achieve the desired count
                break

    # If we have not exceeded 60 games, output the result
    if (len(l)) <= 60:
        print(len(l))
        print(" ".join(map(str, l)))
        sys.exit()


# https://github.com/VaHiX/CodeForces/