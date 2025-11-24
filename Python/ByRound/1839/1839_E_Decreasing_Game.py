# Problem: CF 1839 E - Decreasing Game
# https://codeforces.com/contest/1839/problem/E

"""
Algorithm: Game Theory + Sprague-Grundy Theorem + Nim-like Game
This problem is a variant of a Nim-like game where two players take turns decreasing two elements of an array simultaneously.
The key insight is to determine the winning player using the Sprague-Grundy theorem and nim-sum calculation.
We compute the nim-sum (XOR) of all array elements to determine who wins.
Time Complexity: O(n * sum(a)) where n is the length of array and sum(a) is the total sum of elements
Space Complexity: O(sum(a)) for the dp array storing nim-values
"""

import os
import sys

def f(u):
    # Function to send move to jury and receive response
    os.write(1, b"%d\n" % u)
    return int(input())


n = int(input())
a = [0] + list(map(int, input().split()))  # 1-indexed array
l = sum(a) + 5  # Upper bound for dp array size
dp = [0] * l
dp[0] = 1  # Base case: nim-sum 0 is losing for current player
s = 0  # Total sum of elements

# Build dp table using dynamic programming (similar to subset sum problem)
for i in range(1, n + 1):
    ai = a[i]
    # Traverse backwards to prevent using updated values in same iteration
    for j in range(s, -1, -1):
        if dp[j] and not dp[ai + j]:
            dp[ai + j] = i  # Mark which element contributes to this nim-sum
    s += ai  # Update total sum

# Determine winner based on nim-sum
# If total sum is odd or if we can't reach sum/2, first player wins
x = "First" if s % 2 or not dp[s // 2] else "Second"
os.write(1, b"%s\n" % x.encode())

if x == "First":
    # First player's turn: always choose the maximum element
    v = 1
    while v:
        u = a.index(max(a))  # Find index of maximum element
        v = f(u)  # Send move to jury and get opponent's move
        d = min(a[u], a[v])  # Calculate minimum of the two values
        a[u] -= d  # Decrease both elements
        a[v] -= d

else:
    # Second player's turn: determine winning strategy using dp
    c = [0] * (n + 1)  # Boolean array to identify winning moves
    z = s // 2  # Target nim-sum we want to avoid
    while z:
        c[dp[z]] = 1  # Mark elements involved in strategy
        z -= a[dp[z]]  # Backtrack to find components
    u = int(input())  # Receive first move from jury
    while u:
        # Find a move such that xor of current move and our strategy is zero
        for i in range(1, n + 1):
            if a[i] and c[i] ^ c[u]:
                v = i  # Valid move found
                break
        d = min(a[u], a[v])
        a[u] -= d
        a[v] -= d
        u = f(v)  # Send move and continue
exit()


# https://github.com/VaHiX/CodeForces/