# Problem: CF 1692 H - Gambling
# https://codeforces.com/contest/1692/problem/H

"""
Algorithm: Dynamic Programming with Sliding Window
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks us to find the optimal strategy for Marian to maximize his money after playing a sequence of rounds. 
Each round, he chooses a fixed number 'a' and plays from round 'l' to 'r' (inclusive). 
If the dice shows 'a', his money doubles; otherwise, it halves.

We use dynamic programming to track how many consecutive correct guesses we can make for each number.
The key insight is to find a number 'a' that maximizes the length of consecutive rounds where:
- If the actual number matches 'a', we gain (multiply by 2)
- If it doesn't match, we lose (divide by 2)

This is transformed into a problem of maximizing the number of consecutive correct guesses for a fixed choice 'a'.
By using a sliding window approach, we can find the maximum number of consecutive rounds (with same choice 'a') such that 
the product of 2^k (where k is the number of correct guesses) is maximized.
"""

ans = []
for _ in range(int(input())):
    n = int(input())
    u = input().split()
    idx = ma = 0
    lst, dp = {}, {}
    for i, v in enumerate(u):
        # Update dp: how many consecutive rounds with same value up to now,
        # considering gap between last occurrence
        dp[v] = 1 + max(dp.get(v, 0) - (i - lst.get(v, -1) - 1), 0)
        lst[v] = i  # Record last seen index of value v
        if dp[v] > ma:
            ma = dp[v]
            idx = i
    l, sb = idx, 0
    # Backtrack to find the start of the optimal sequence
    while sb < ma:
        if u[l] == u[idx]:
            sb += 1
        else:
            sb -= 1
        l -= 1
    print(u[idx], l + 2, idx + 1)


# https://github.com/VaHiX/CodeForces/