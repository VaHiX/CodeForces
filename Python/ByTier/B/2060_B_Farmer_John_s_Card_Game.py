# Problem: CF 2060 B - Farmer John's Card Game
# https://codeforces.com/contest/2060/problem/B

"""
B. Farmer John's Card Game

Algorithm/Technique:
- This problem is about finding a valid permutation of cows such that they can play their cards in order,
  following the constraint that each card played must be greater than the one on top of the pile.
- We use a greedy approach: sort all cards by value, and assign them to cows in a way that simulates
  a valid playing order.
- Time Complexity: O(n*m*log(n*m)) due to sorting.
- Space Complexity: O(n*m) for storing card data.

The idea is:
1. All cards are collected and sorted by their values.
2. For each card, we determine which cow originally had it.
3. We assign cows to rounds in a way that allows the sequence of cards to be played.
4. If all cards can be assigned correctly without conflict, print the permutation; otherwise output -1.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m = map(int, input().split())
    a = []
    for i in range(n):
        b = map(int, input().split())
        for x in b:
            a.append((x, i))  # (card_value, cow_id)
    a.sort()
    b = [i[1] for i in a[:n]]  # First n cards' cow IDs in sorted order
    if [i[1] for i in a] == b * m:  # Check if the assignment is valid
        print(*[i + 1 for i in b])  # Convert to 1-based indexing
    else:
        print(-1)


# https://github.com/VaHiX/codeForces/