# Problem: CF 1499 E - Chaotic Merge
# https://codeforces.com/contest/1499/problem/E

"""
Code Purpose:
This code solves the "Chaotic Merge" problem by using dynamic programming to count the number of valid merging sequences
that produce chaotic merges (no two consecutive characters are the same) for all possible substrings of the input strings x and y.
The approach uses a state machine with DP to track valid transitions based on the last characters added from x and y.

Algorithms/Techniques:
- Dynamic Programming with memoization
- State tracking for last characters from x (fs) and y (ft)
- Transition logic for valid merges
- Modular arithmetic for large results

Time Complexity:
O(n * m * 2 * 2 * 27) where n and m are lengths of strings x and y respectively.
In the worst case this is O(1000 * 1000 * 2 * 2 * 27) = O(10^8) operations, which should be acceptable within time limits.

Space Complexity:
O(m * 2 * 2 * 27) for DP arrays, which is approximately O(1000 * 2 * 2 * 27) = O(10^5) space.
"""

s = [0] + list(input())  # Convert string x to 1-indexed list of integers (a=1, b=2, ..., z=26)
t = [0] + list(input())  # Convert string y to 1-indexed list of integers (a=1, b=2, ..., z=26)
n = len(s) - 1
m = len(t) - 1
mod = 998244353

# Convert characters to numeric values (a=1, b=2, ..., z=26)
for i in range(1, n + 1):
    s[i] = ord(s[i]) - 96
for i in range(1, m + 1):
    t[i] = ord(t[i]) - 96


# Helper function to create a unique index for DP state
def _(j, fs, ft, al):
    if j < 0:
        return -1
    return ((j * 2 + fs) * 2 + ft) * 27 + al


# DP arrays for current and previous states
dp = [0] * (m + 3) * 2 * 2 * 27
dp[_(0, 0, 0, 0)] = 1  # Base state
sdp = [0] * (m + 3) * 2 * 2 * 27
sdp[_(0, 0, 0, 0)] = 1
ans = 0  # Final result

# Arrays to store the current iteration's DP state
dpi = [0] * (m + 3) * 2 * 2 * 27
sdpi = [0] * (m + 3) * 2 * 2 * 27

# Iterate through each character in x
for i in range(n + 1):
    # For each position in y
    for j in range(m + 1):
        # For each possible last state from x and y (fs and ft)
        for fs in range(2):
            for ft in range(2):
                # For each possible alphabet character that can be added next
                for al in set([0, s[i], t[j]]):
                    # Handle base case
                    if fs == ft == 0:
                        if al == 0:
                            dpi[_(j, fs, ft, al)] = 1
                        sdpi[_(j, fs, ft, 0)] += dpi[_(j, fs, ft, al)]
                        continue
                    # Handle transitions from strings x
                    if fs == 1:
                        if al == s[i]:
                            dpi[_(j, fs, ft, al)] += (
                                sdp[_(j, 1, ft, 0)]
                                + sdp[_(j, 0, ft, 0)]
                                - dp[_(j, 0, ft, al)]
                                - dp[_(j, 1, ft, al)]
                            )
                            dpi[_(j, fs, ft, al)] %= mod

                    # Handle transitions from strings y
                    if ft == 1:
                        if al == t[j]:
                            dpi[_(j, fs, ft, al)] += (
                                sdpi[_(j - 1, fs, 1, 0)]
                                + sdpi[_(j - 1, fs, 0, 0)]
                                - dpi[_(j - 1, fs, 1, al)]
                                - dpi[_(j - 1, fs, 0, al)]
                            )
                            dpi[_(j, fs, ft, al)] %= mod
                    # Update summed DP value for this state
                    sdpi[_(j, fs, ft, 0)] += dpi[_(j, fs, ft, al)]
                    sdpi[_(j, fs, ft, 0)] %= mod
    
    # After processing all y positions, add results for the current x character to total
    for j in range(1, m + 1):
        for al in set([0, s[i], t[j]]):
            ans += dpi[_(j, 1, 1, al)]
            ans %= mod
    
    # Swap DP arrays for next iteration
    dp, dpi = dpi, dp
    sdp, sdpi = sdpi, sdp
    
    # Reset current dpi and sdpi arrays for next iteration
    for j in range(m + 1):
        for al in [0, s[i - 1], t[j]]:
            for fs in range(2):
                for ft in range(2):
                    dpi[_(j, fs, ft, al)] = 0
                    sdpi[_(j, fs, ft, 0)] = 0


print(ans)


# https://github.com/VaHiX/CodeForces/