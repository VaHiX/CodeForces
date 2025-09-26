# Problem: CF 2113 D - Cheater
# https://codeforces.com/contest/2113/problem/D

"""
D. Cheater

Purpose:
This code solves the problem of maximizing the number of points a player can score in a card game,
given that the player can swap at most two cards in their hand to optimize the outcome.

Algorithm:
The solution uses binary search on the answer (number of rounds won) combined with a greedy validation approach.
For each possible number of wins (mid), we check if it's achievable by trying to select a subsequence of length mid
from the player's hand such that it beats the dealer's strategy optimally.

Time Complexity: O(n * log n)
Space Complexity: O(n)

Techniques:
- Binary Search on Answer
- Sliding window to find minimum value in a range
- Greedy selection for optimization

"""
import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    lo = 0
    hi = n + 1
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        # Precompute minimum value in sliding window of size (n - mid + 1)
        premin = 2 * n + 1
        for i in range(n - mid + 1):
            premin = min(premin, b[i])
        smol = 0
        # Count how many cards in first 'mid' positions of a are less than premin
        for j in range(mid):
            if a[j] < premin:
                smol += 1
        big = 0
        # Count how many cards in remaining positions of a are greater than premin
        for j in range(mid, n):
            if a[j] > premin:
                big += 1
        # If valid configuration (smallexpected <= 1, and big >= smol)
        if smol <= 1 and big >= smol:
            lo = mid
        else:
            hi = mid
    print(lo)


# https://github.com/VaHiX/codeForces/