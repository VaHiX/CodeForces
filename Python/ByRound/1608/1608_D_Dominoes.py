# Problem: CF 1608 D - Dominoes
# https://codeforces.com/contest/1608/problem/D

"""
Algorithm: Dominoes Coloring
Approach:
- The problem involves coloring dominoes such that a valid arrangement exists where 
  adjacent dominoes (in a circular manner) have different colors on their touching ends.
- We analyze the constraints imposed by the existing colors and determine how many 
  ways to color the ? cells lead to valid arrangements.
- Key observations:
  - For any valid circular arrangement, we can think of it as a cycle where each 
    domino contributes a "left" and "right" color.
  - The constraint is: right color of domino i must be different from left color of domino i+1 (mod n).
  - The approach uses combinatorics to count valid assignments of ? cells.

Time Complexity: O(n)
Space Complexity: O(n)

This solution computes for each valid combination of black/white assignments to ? cells 
that satisfy the constraint, and then subtracts invalid configurations and accounts 
for edge cases.
"""

n = int(input())
dom = []
for _ in range(n):
    dom.append(list(input().strip()))

# Flip right colors so that:
# If right was W, now it's B (so that we can think of it as "must be different from left")
# If right was B, now it's W (same idea)
# If right was ?, then it stays ? (we'll assign it later)
for d in dom:
    if d[1] == "W":
        d[1] = "B"
    elif d[1] == "B":
        d[1] = "W"

MOD = 998244353


def modmul(x, y, c=0):
    # Modular multiplication: (x * y + c) % MOD
    return (x * y + c) % MOD


def inv(x):
    # Modular inverse using Fermat's little theorem
    return pow(x, MOD - 2, MOD)


MAX = 10**6

# Precompute factorials and inverse factorials for combinations
fact = [1]
for i in range(1, MAX):
    fact.append(modmul(i, fact[i - 1]))

invfact = [1] * (MAX)
invfact[MAX - 1] = inv(fact[MAX - 1])
for i in range(MAX - 2, -1, -1):
    invfact[i] = modmul(i + 1, invfact[i + 1])


def comb(x, y):
    # Compute combination C(x, y) = x! / (y! * (x - y)!)
    if y > x or y < 0:
        return 0
    return modmul(fact[x], modmul(invfact[y], invfact[x - y]))


out = 0

# Count existing W on left and right, and number of ? on left and right
wL = 0
wR = 0
qL = 0
qR = 0

for d in dom:
    if d[0] == "W":
        wL += 1
    if d[1] == "W":
        wR += 1
    if d[0] == "?":
        qL += 1
    if d[1] == "?":
        qR += 1

# Try all possible count of black cells that can be assigned to the left
# (must lie between wL and wL + qL) to make sure it works for the entire
# cycle. Similarly for right.
for i in range(n + 1):
    if wL <= i <= wL + qL and wR <= i <= wR + qR:
        # Add number of ways to choose how many ? to color black on left and right
        out += modmul(comb(qL, i - wL), comb(qR, i - wR))

# Subtract cases where there is no way to avoid a valid cycle 
# (i.e., no pair of dominoes with same color on both ends)
bad = 1
for d in dom:
    if d == ["W", "B"]:
        bad = 0
    elif d == ["B", "W"]:
        bad = 0
    elif d == ["?", "?"]:
        bad = modmul(2, bad)

# Subtract the bad case
out -= bad

# Handle edge case where all dominoes are empty — only one valid way
if not any("B" in d for d in dom):
    out += 1
if not any("W" in d for d in dom):
    out += 1

# Output final result modulo MOD
print(out % MOD)


# https://github.com/VaHiX/CodeForces/