# Problem: CF 2109 C1 - Hacking Numbers (Easy Version)
# https://codeforces.com/contest/2109/problem/C1

"""
C1. Hacking Numbers (Easy Version)
Interactive problem to transform an unknown integer x (1 <= x <= 10^9) into a given target n using at most 7 commands.
Commands available:
- "add y": add y to x
- "mul y": multiply x by y
- "div y": divide x by y if divisible
- "digit": replace x with sum of its digits
- "!": check if x equals n

Algorithm:
Uses a combination of arithmetic operations and digit sum manipulation.
The approach leverages the fact that we can build large numbers via multiplication,
and reduce complexity using digit sums when needed.

Time Complexity: O(1) - fixed number of steps per test case
Space Complexity: O(1) - constant extra space used
"""

for i in range(int(input())):
    print(f"digit\ndigit\nadd -8\nadd -4\nadd -2\nadd -1\nadd {int(input())-1}\n!\n")
    for j in range(8):  # Read responses to commands
        input()


# https://github.com/VaHiX/codeForces/