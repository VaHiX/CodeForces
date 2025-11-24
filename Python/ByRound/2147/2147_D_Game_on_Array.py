# Problem: CF 2147 D - Game on Array
# https://codeforces.com/contest/2147/problem/D

"""
D. Game on Array

Purpose:
This code solves a game theory problem where two players (Alice and Bob) play a turn-based game on an array of positive integers.
Each player, on their turn, chooses a value x > 0 present in the array, earns points equal to the count of x's in the array,
and then decreases all instances of x by 1. The game ends when all values in the array become zero.
The goal is to determine the final scores when both players play optimally.

Algorithms/Techniques:
- Greedy approach based on optimal move selection (maximize current points)
- Frequency counting using Counter
- Mathematical calculation to determine final scores

Time Complexity: O(n log n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing frequencies and intermediate data structures.

"""

from collections import Counter

for t in range(int(input())):
    N = int(input())
    arr = [*map(int, input().split())]
    # Count frequency of odd numbers (key insight: only odd counts affect final difference)
    count = Counter([_ for _ in arr if _ % 2 == 1])
    # Sort frequencies in descending order to process highest frequencies first
    freqs = sorted(count.values(), reverse=True)
    diff = 0
    # Alternate adding and subtracting frequencies based on turn (odd turns contribute positively, even negatively)
    for i in range(len(freqs)):
        curr = freqs[i]
        if i % 2 == 1:  # Bob's turn contribution (subtract)
            curr *= -1
        diff += curr
    X = sum(arr)  # Total sum of all elements in the original array
    # Adjust difference when total sum is odd and difference is even to ensure correct parity
    if X % 2 == 1 and diff % 2 == 0:
        diff += 1
    # Calculate Alice's score using formula: (X + diff + 1) // 2
    a = (X + diff + 1) // 2
    # Bob's score is total sum minus Alice's score
    b = X - a
    print(a, b)


# https://github.com/VaHiX/CodeForces/