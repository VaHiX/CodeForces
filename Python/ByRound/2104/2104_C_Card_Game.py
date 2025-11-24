# Problem: CF 2104 C - Card Game
# https://codeforces.com/contest/2104/problem/C

"""
C. Card Game

Algorithm/Techniques: Game Theory, Greedy Strategy, String Analysis

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) due to the input string storage.

The problem involves a game between Alice and Bob with cards numbered 1 to n,
where card i beats card j if i > j, except card 1 beats card n.
Both players play optimally and take turns playing cards from their hands.
The outcome is determined based on the initial distribution of cards (string of A/B).

This solution uses a greedy approach by examining the first and last characters
of the string to determine who will win without simulating the entire game.

Key Observations:
- If Alice starts with an 'A', and either:
  - The last card is also 'A', or
  - There's exactly one 'B' in the string,
  then Alice wins.
- Otherwise, if the first card is not 'A', we check the last two cards:
  - If both are 'A', Alice wins; otherwise Bob wins.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    s = input().rstrip("\n")
    if s[0] == "A":
        # If the first card is A, check if Alice can win based on:
        # 1. Last card is also A, or
        # 2. Only one B exists (Alice gets to play best cards)
        if s[-1] == "A" or s.count("B") == 1:
            print("Alice")
        else:
            print("Bob")
    else:
        # If Alice starts with B, check the last two cards:
        # If both are A, Alice wins; otherwise Bob wins
        print("Alice" if s[-2] == s[-1] == "A" else "Bob")


# https://github.com/VaHiX/codeForces/