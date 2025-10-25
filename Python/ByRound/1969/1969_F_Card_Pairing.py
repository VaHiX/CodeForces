# Problem: CF 1969 F - Card Pairing
# https://codeforces.com/contest/1969/problem/F

"""
Algorithm: Card Pairing
Purpose: To find the maximum number of coins that can be earned by pairing cards of the same type.
Approach: 
    1. Simulate initial draw from deck and calculate how many unmatched cards are in the hand.
    2. Process the remaining cards in the deck backwards to determine optimal pairing strategy.
    3. Use dynamic programming principles and combinatorics to determine the maximum number of coins.

Time Complexity: O(n^2 + n*k) where n is the number of cards and k is the number of types.
Space Complexity: O(n + k) for storing intermediate values and arrays.

Techniques Used:
    - Bit manipulation for tracking card counts (XOR operations)
    - Reverse iteration over deck to compute cost of continuing the game
    - Combination formulas for calculating max possible pairing configurations
    - Dynamic programming to track minimal cost to continue
"""

from math import comb
from sys import stdin


def max_pair_count(cards, k):
    n = len(cards)
    curr = [0] * k
    one_count = 0
    for i in range(0, n, 2):  # Process pairs of cards
        curr[cards[i]] ^= 1  # Toggle bit for card type
        one_count += 2 * curr[cards[i]] - 1  # Update count of odd occurrences
        curr[cards[i + 1]] ^= 1
        one_count += 2 * curr[cards[i + 1]] - 1
        if one_count == k:  # All types have even counts in hand
            first = i + 2   # Start point when all hand cards are even
            break
    else:
        # If we never hit an all-even state, return total possible pairs minus unmatched ones
        return n // 2 - one_count // 2

    # Track shadowing for continuation decisions (whether a turn can be skipped)
    is_shadowed = [False] * (n + 1)
    # Cost to continue from each position if we proceed the game further
    continue_cost = [n] * (n + 1)
    # Count of unique types that remain in tail (from current position to end)
    tail = [1] * k
    tail_ones = k  # Total number of odd counts initially

    # Iterate from last card backwards to compute optimal continuation
    for start in range(n, first - 1, -2):  # Go backward by pairs
        if start < n:  # Update tail if not at beginning
            tail[cards[start]] ^= 1
            tail_ones += 2 * tail[cards[start]] - 1
            tail[cards[start + 1]] ^= 1
            tail_ones += 2 * tail[cards[start + 1]] - 1

        curr = [0] * k  # Reset current card count
        excess_distr = [0] * (k + 1)  # Track how many excess card types there are
        one_count = 0  # Total odd occurrences in current window
        excess_ones = 0  # Odd occurrences not in tail

        # Process remaining cards from 'start' onward
        for i in range(start, n, 2):
            for card in cards[i : i + 2]:  # Process two cards
                curr[card] ^= 1  # Toggle bit for card type in current hand
                one_count += 2 * curr[card] - 1
                if not tail[card]:  # If card type is not in tail, it contributes to excess
                    excess_ones += 2 * curr[card] - 1
            if one_count == 0:  # If no unmatched cards remain
                is_shadowed[i + 2] = True  # Mark this turn as shadowed
            
            # Cost of continuing game from this position
            if not is_shadowed[i + 2]:
                continue_cost[start] = min(
                    continue_cost[start], continue_cost[i + 2] + (one_count >> 1)
                )
                excess_distr[excess_ones] += 1

        base_cost = tail_ones // 2  # Base cost to resolve tail cards
        for excess_ones in range(k - tail_ones + 1):  # Try each excess count
            if tail_ones == 0 and excess_ones == 0:
                continue
            if tail_ones == 0:
                max_cnt = comb(k, excess_ones) if excess_ones & 1 == 0 else 0
            else:
                max_cnt = comb(k - tail_ones, excess_ones) * (2 ** (tail_ones - 1))
                max_cnt -= excess_ones == 0
            if excess_distr[excess_ones] < max_cnt:
                continue_cost[start] = min(
                    continue_cost[start], base_cost + excess_ones
                )
                break

    return n // 2 - continue_cost[first]


n, k = map(int, stdin.readline().split())
cards = [int(w) - 1 for w in stdin.readline().split()]
print(max_pair_count(cards, k))


# https://github.com/VaHiX/CodeForces/