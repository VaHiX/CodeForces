# Problem: CF 2115 D - Gellyfish and Forget-Me-Not
# https://codeforces.com/contest/2115/problem/D

"""
D. Gellyfish and Forget-Me-Not

Algorithm:
This problem uses a greedy approach with bit manipulation to determine the optimal value of x after n rounds.
The key idea is to process bits from the most significant to least significant (MSB to LSB), simulating the game
where Gellyfish minimizes x and Flower maximizes it.

Time Complexity: O(60 * n) = O(n)
Space Complexity: O(n)

The problem models a game between two players where each player chooses an operation to either minimize or maximize
the final XOR value. The solution uses a greedy algorithm on bits, processing from MSB to LSB, and determining the
best choice for each bit position based on which player is active and optimal play.

Techniques:
- Bit manipulation (XOR)
- Greedy selection with binary representation
- Simulating turn-based game optimally using bitwise operations

Rules for choosing optimal value per bit:
For each bit position from MSB to LSB:
1. Find a number b[i] that has this bit set and is not yet fixed.
2. If the active player is Flower (c[i]=='1'), choose to maximize x.
3. Otherwise, if Gellyfish plays (c[i]=='0'), minimize x.
"""

import sys

input = sys.stdin.readline

out = []
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    c = input().strip()
    base = 0
    for i in range(n):
        base ^= a[i]  # Accumulate the XOR of all a values initially (before updating b)
        b[i] ^= a[i]  # b[i] now represents difference between b and a at that index
    fixed = [0] * n  # Tracks which positions have already been processed for this bit
    for bt in range(60)[::-1]:  # Iterate through each bit from MSB to LSB (60 bits max as per constraints)
        mask = 1 << bt  # Create a mask for the current bit position
        i = n - 1
        while i >= 0:
            if b[i] & mask == 0 or fixed[i]:  # Skip if this bit is unset or already fixed
                i -= 1
                continue
            diff = b[i]  # This is the value of b at current bit position (before applying updates)
            fixed[i] = 1  # Mark this index as processed for this bit
            if c[i] == "1":  # If Flower plays here (maximizing)
                base = max(base, base ^ diff)  # Choose to maximize result by adding the difference if beneficial
            else:  # Gellyfish plays here (minimizing)
                base = min(base, base ^ diff)  # Choose to minimize result
            break
        i -= 1  # Move to next index
        while i >= 0:
            if b[i] & mask:  # If this bit is set in b[i]
                b[i] ^= diff  # Apply update so that future decisions are consistent with previous choice
            i -= 1
    out.append(base)
print("\n".join(map(str, out)))


# https://github.com/VaHiX/codeForces/