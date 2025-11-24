# Problem: CF 1739 C - Card Game
# https://codeforces.com/contest/1739/problem/C

"""
Card Game Solution

This problem involves determining the number of ways to distribute n cards 
( numbered 1 to n ) between two players Alex and Boris such that each gets n/2 cards,
and calculating the outcomes (Alex wins, Boris wins, or draw) based on optimal play.

Key insights:
- The game is about optimal card playing where each player plays the strongest 
  available card that can beat the opponent's card.
- The problem can be reduced to counting valid distributions based on 
  a recurrence relation.
- The solution uses dynamic programming to compute:
    - Alex's winning configurations (A[i])
    - Boris's winning configurations (B[i])
    - Draw configurations (1 for all cases, as the recurrence is designed to 
      capture all valid distributions in terms of win/loss)

Time Complexity: O(n^2) due to combination calculations and recurrence building
Space Complexity: O(n) for storing precomputed values up to n/2

Algorithms/Techniques:
- Binomial Coefficients for distribution counting
- Dynamic Programming to compute win/loss scenarios
"""

from math import comb as c

p = 998244353
# Precompute results for all possible n/2 values up to 30
# a[i] = (Alex_wins, Boris_wins) for n=2*i
a = [(0, 0), (1, 0)]
for i in range(2, 31):
    # Calculate total ways to choose i cards from 2*i cards (divided by 2)
    total_ways = (c(i * 2, i) // 2) % p
    # Alex wins = total_ways + previous Boris wins (recursive structure)
    alex_wins = (total_ways + a[-1][1]) % p
    # Boris wins = total_ways - Alex wins - 1 (accounted for draw)
    boris_wins = (total_ways - a[-1][1] - 1 + p) % p
    a += [(alex_wins, boris_wins)]

# Process input and output the result for each test case
for _ in range(int(input())):
    # Get n, divide by 2 to index into precomputed array
    n = int(input()) // 2
    print(*a[n], 1)


# https://github.com/VaHiX/CodeForces/