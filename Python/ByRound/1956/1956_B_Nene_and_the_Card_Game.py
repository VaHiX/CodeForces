# Problem: CF 1956 B - Nene and the Card Game
# https://codeforces.com/contest/1956/problem/B

"""
Code Purpose:
This code solves the problem of finding the maximum points a player can score in a card game where:
- There are 2n cards, each with integers from 1 to n appearing exactly twice.
- The player and Nene take turns picking cards from their respective hands.
- A player gets a point if they pick a card that has a matching integer on the table already.
- Nene plays optimally to maximize her score, and then minimize the opponent's score.
- The goal is to compute the maximum points the player can achieve when playing optimally.

Algorithm:
- For each test case, the player's hand is given as a list of integers.
- The approach is to simulate a greedy strategy where we try to delay using cards that would give us points.
- Specifically:
    - Count how many times each integer appears in the player's hand (frequency).
    - Simulate the game: for each turn:
        - If a card of the same value has already been placed on the table (i.e., we can score), take it.
        - Otherwise, place the card we have, and it won’t be able to score in future.
- This greedy method ensures that the optimal number of points are scored, as the player should prioritize placing cards that could give points only when necessary.
- The core idea is to compute the difference in total distinct cards vs. cards that appear in our hand.

Time Complexity: O(n), since we process each element once.
Space Complexity: O(n), for storing frequency and set of cards.

Input:
- Multiple test cases.
- For each test case:
    - n: number of cards.
    - Line of n integers representing cards in the player's hand.

Output:
- Maximum points the player can score.
"""

for line in [*open(0)][2::2]:
    print(len(tokens := line.split()) - len({*tokens}))


# https://github.com/VaHiX/CodeForces/