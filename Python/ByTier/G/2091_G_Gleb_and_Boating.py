# Problem: CF 2091 G - Gleb and Boating
# https://codeforces.com/contest/2091/problem/G

"""
G. Gleb and Boating

Problem Description:
Gleb needs to travel from point 0 to point s using a kayak with initial power k.
Each paddle stroke moves the kayak by the current power amount.
Turning around decreases power by 1 (but never goes below 1), and consecutive turns are not allowed.
The goal is to find the maximum power that can be retained at the end of the journey.

Approach:
- If s is divisible by k, we can reach s with power k.
- If 2*s > k*k, it's better to use a smaller power to avoid too many turns.
- Otherwise, simulate a dynamic programming approach where we try to reach point s
  with different powers from k down to 1 using a greedy method with transitions.

Time Complexity: O(k^2) per test case in worst case due to nested loops and DP updates.
Space Complexity: O(s) for DP array, but optimized in practice due to sliding window-like operations.

"""

import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))

for _ in range(sint()):
    s, k = mint()
    if s % k == 0:
        print(k)
        continue
    if 2 * s > k * k:
        print(max(k - 2, 1))
        continue
    
    # dp[i] represents whether we can reach position i with current power
    dp = [1] + [0] * s
    while k > 1:
        # Shrink the dp array to size k and shift left 
        dp = [0] * k + dp[: s + 1 - k]
        # Forward pass: determine if we can reach positions from previous states 
        for i in range(2 * k, s + 1):
            dp[i] |= dp[i - k]
        if dp[-1]:  # If we can reach last position
            print(k)
            break
        
        k = max(k - 1, 1)  # Decrease power
        # Shift dp right and update backwards 
        dp = dp[k:] + [0] * k
        for i in range(s - k, k - 1, -1):
            dp[i - k] |= dp[i]
        k = max(k - 1, 1)  # Decrease power again
    else:
        print(1)


# https://github.com/VaHiX/codeForces/