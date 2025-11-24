# Problem: CF 1710 C - XOR Triangle
# https://codeforces.com/contest/1710/problem/C

"""
Algorithm: Dynamic Programming with Digit DP
Purpose: Count the number of triples (a,b,c) such that a XOR b, b XOR c, and a XOR c form the sides of a non-degenerate triangle.

Time Complexity: O(n * 2^6) = O(n), where n is the length of the binary string of n.
Space Complexity: O(n * 2^6) = O(n), for the DP table.

The solution uses digit DP to count valid combinations. We process the binary representation of n digit by digit.
At each step, we track the constraints on a, b, c and their XOR values (ab, bc, ac) which represent the triangle sides.
We ensure a, b, c are all <= n and the triangle inequality holds for a XOR b, b XOR c, a XOR c.
"""

import sys

input = sys.stdin.readline

M = 998244353
s = input()[:-1] # Read input and remove newline
n = len(s)
# dp[i][state]: number of ways to reach state after processing first i digits
dp = [[0] * 64 for i in range(n + 1)]
dp[0][0] = 1
step = [1, 2, 4, 8, 16, 32] # Powers of 2 for state encoding

# For each digit position in the binary string
for i in range(1, n + 1):
    d = int(s[i - 1]) # Current digit (0 or 1)
    # For each possible combination of flags and XOR results
    for fl1 in range(2): # flag for a < d
        for fl2 in range(2): # flag for b < d
            for fl3 in range(2): # flag for c < d
                for c in range(2): # value of bit c
                    if c <= fl3 + d: # Check if this value can be valid
                        for b in range(2): # value of bit b
                            if b <= fl2 + d: # Check if this value can be valid
                                for a in range(2): # value of bit a
                                    if a <= fl1 + d: # Check if this value can be valid
                                        for ab in range(2): # XOR of a and b
                                            for bc in range(2): # XOR of b and c
                                                for ac in range(2): # XOR of a and c
                                                    x = ab
                                                    y = bc
                                                    z = ac
                                                    FL1 = fl1
                                                    FL2 = fl2
                                                    FL3 = fl3
                                                    
                                                    # Update flags if a, b, or c is less than current digit
                                                    if a < d:
                                                        FL1 = 1
                                                    if b < d:
                                                        FL2 = 1
                                                    if c < d:
                                                        FL3 = 1

                                                    # Handle special case for equal bits (XOR result becomes 0)
                                                    # When two bits are equal, their XOR is 0, so we set corresponding x,y,z to 1
                                                    if 1 <= a + b + c <= 2: # Only valid when not all are 0 or all are 1
                                                        if a == b:
                                                            x = 1
                                                        if a == c:
                                                            z = 1
                                                        if b == c:
                                                            y = 1

                                                    # Encode the current state into a single number (6-bit state)
                                                    EEE = (
                                                        FL1
                                                        + 2 * FL2
                                                        + 4 * FL3
                                                        + 8 * x
                                                        + 16 * y
                                                        + 32 * z
                                                    )
                                                    
                                                    # Encode the previous state
                                                    AAA = (
                                                        fl1
                                                        + 2 * fl2
                                                        + 4 * fl3
                                                        + 8 * ab
                                                        + 16 * bc
                                                        + 32 * ac
                                                    )
                                                    
                                                    # Add to DP table for next position
                                                    dp[i][EEE] = (
                                                        dp[i][EEE] + dp[i - 1][AAA]
                                                    ) % M

ans = 0
# Sum up all valid final states
for fl1 in range(2):
    for fl2 in range(2):
        for fl3 in range(2):
            for ab in range(1, 2): # ab must be 1 (we want non-degenerate triangles, at least one XOR result > 0)
                for bc in range(1, 2): # bc must be 1 (we want non-degenerate triangles)
                    for ac in range(1, 2): # ac must be 1 (we want non-degenerate triangles)
                        AAA = (
                            step[0] * fl1
                            + step[1] * fl2
                            + step[2] * fl3
                            + step[3] * ab
                            + step[4] * bc
                            + step[5] * ac
                        )
                        ans += dp[n][AAA]
print(ans % M)


# https://github.com/VaHiX/CodeForces/