# Problem: CF 1776 L - Controllers
# https://codeforces.com/contest/1776/problem/L

"""
Problem: Determine if it's possible to achieve a score of 0 in a game with n rounds,
where each round has either '+' or '-' symbol and player chooses between two buttons
with values a and b. The goal is to check whether a given controller (a, b) allows
the player to win the game.

Approach:
- Count number of '+' and '-' symbols in the string.
- For a given controller with button values a and b:
  - If a == b:
    - Check if number of '+'s equals number of '-'s (p == m).
  - Else:
    - Compute score as p*a - m*b.
    - Check if there exists a valid assignment of buttons to rounds such that
      final score is 0. Using algebraic derivation, we check if certain modular
      conditions hold.

Time Complexity: O(n + q), where n is the length of string s and q is number of queries.
Space Complexity: O(1) additional space excluding input storage.

Algorithms/Techniques:
- Linear time counting
- Modular arithmetic and algebraic analysis
"""

import sys

input = sys.stdin.readline
n = int(input())
p = input().count("+")  # Count of '+' signs
m = n - p               # Count of '-' signs

for _ in range(int(input())):
    a, b = map(int, input().split())
    if not (min(a, b) * p - max(a, b) * m <= 0 <= max(a, b) * p - min(a, b) * m):
        print("NO")
        continue
    if a == b:
        print("YES" if p == m else "NO")  # Only possible if equal number of + and - signs
    else:
        print("YES" if (m * b - p * b) % (b - a) == 0 else "NO")  # Check modular condition for valid assignment


# https://github.com/VaHiX/codeForces/