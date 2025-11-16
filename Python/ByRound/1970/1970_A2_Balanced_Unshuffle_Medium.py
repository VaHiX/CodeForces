# Problem: CF 1970 A2 - Balanced Unshuffle (Medium)
# https://codeforces.com/contest/1970/problem/A2

"""
Balanced Unshuffle (Medium)

Algorithm:
The problem asks us to find the preimage of a balanced parentheses sequence under the "balanced shuffle" operation.
The process involves:
1. Simulating the balanced shuffle in reverse.
2. We build a stack-like structure where we track the depth of parentheses.
3. Using the given shuffled sequence, we reconstruct the original sequence by reversing the shuffle process.

Time Complexity: O(n^2) where n is the length of the input string.
Space Complexity: O(n^2) for storing the intermediate sequence information.
"""

s = input()
p = [[]]  # List of lists to simulate the stages of reconstruction
prv = 0   # Tracks the previous balance
c = 0     # Current balance counter
cur = 0   # Current level in the stack-like structure

# First pass: simulate the balanced shuffle process in reverse
for i in range(len(s)):
    if s[i] == "(":
        c += 1
        p[cur].append("(")
    else:
        if prv == 0:
            # When we are at the top of a new group
            cur += 1
            p.append([])
            p[cur].append(")")
            prv = c - 1  # Update previous balance to match the balance before closing
            c = 0        # Reset current counter
        else:
            prv -= 1
            p[cur].append(")")

# Second pass: reconstruct the original sequence by traversing backwards through levels
cur = 0
while len(p[cur]) > 0:
    x = p[cur].pop()  # Pop from current level
    if x == "(":
        cur += 1      # Move to higher level when encountering opening
    else:
        cur -= 1      # Move to lower level when encountering closing
    print(x, end="")


# https://github.com/VaHiX/CodeForces/