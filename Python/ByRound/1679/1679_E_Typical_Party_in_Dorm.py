# Problem: CF 1679 E - Typical Party in Dorm
# https://codeforces.com/contest/1679/problem/E

"""
Code Purpose:
This solution computes the total number of palindromic substrings across all possible strings formed by replacing question marks in a given string with characters from a query set. It uses dynamic programming with bitmasks to track which characters are available for replacement and computes contributions of each palindrome type efficiently.

Algorithms/Techniques:
- Bitmask Dynamic Programming (DP)
- Prefix/Suffix Counting for Question Marks
- Palindrome Expansion with Center Approach
- Inclusion-Exclusion with Bitmasking
- Modular Arithmetic for large results

Time Complexity: O(n^2 * 2^17 + Q * 2^17)
Space Complexity: O(n + 2^17)

Where n is the length of the string and Q is the number of queries.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]

n = int(input())
# Convert characters to numbers (0-16 for a-q, -1 for '?')
s = [ord(i) - 97 if "a" <= i <= "q" else -1 for i in input()]

# Precompute cumulative number of '?' from left and right
cumL = [0] * n
for i in range(n - 1):
    cumL[i + 1] = cumL[i] + (s[i] == -1)

cumR = [0] * n
for i in range(n - 1, 0, -1):
    cumR[i - 1] = cumR[i] + (s[i] == -1)

# Precompute population count for all values from 0 to 2^17 - 1
popcnt = [0] * (1 << 17)
for i in range(1, 1 << 17):
    popcnt[i] = popcnt[i >> 1] + (i & 1)

# Initialize answer array for different bitmasks
ans = [0] * (1 << 17)
mod = 998244353

# Process all possible lengths of character sets (from 1 to 17)
for size in range(1, 18):
    # Precompute powers of 'size' modulo 'mod' for fast computation
    POW = [1] * (n + 1)
    for i in range(1, n + 1):
        POW[i] = POW[i - 1] * size % mod
    
    # DP array to store counts of palindromes based on character availability masks
    dp = [0] * (1 << 17)
    
    # For each position in the string, expand around centers
    for i in range(n):
        for l, r in [(i, i), (i, i + 1)]:  # Odd and even length palindromes
            flag = True
            free = 0
            mask = 0
            # Expand while within bounds
            for _ in range(n):
                if 0 <= l <= r < n:
                    if s[l] == s[r]:
                        # If both are '?', one more freedom to choose
                        if s[l] == -1:
                            free += 1
                    elif s[l] == -1:
                        # Set bit in mask for fixed character at r
                        mask |= 1 << (s[r])
                    elif s[r] == -1:
                        # Set bit in mask for fixed character at l
                        mask |= 1 << (s[l])
                    else:
                        # Mismatch between fixed characters, invalid center
                        flag = False
                    if flag:
                        # Add contribution of this palindrome to the state
                        dp[mask] += POW[free + cumL[l] + cumR[r]]
                l -= 1
                r += 1

    # Apply inclusion-exclusion principle to compute final DP values
    for i in range(17):
        for bit in range(1 << 17):
            if (bit >> i) & 1:
                dp[bit] += dp[bit ^ (1 << i)]
            dp[bit] %= mod

    # Store results for this specific size into final answer array
    for i in range(1 << 17):
        if popcnt[i] == size:
            ans[i] = dp[i]

# Process queries
for _ in range(int(input())):
    bit = 0
    # Create bitmask from input characters
    for i in input():
        bit |= 1 << (ord(i) - 97)
    # Print precomputed answer for this query's mask
    print(ans[bit])


# https://github.com/VaHiX/CodeForces/