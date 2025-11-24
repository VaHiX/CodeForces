# Problem: CF 2123 A - Blackboard Game
# https://codeforces.com/contest/2123/problem/A

# Problem: Determine the winner of a blackboard game where players alternate choosing numbers
#          such that their sum is congruent to 3 modulo 4.
# Algorithm: Mathematical analysis based on modular arithmetic properties
# Time Complexity: O(1) per test case
# Space Complexity: O(1)

for n in [*open(0)][1:]:
    # Check if n % 4 is non-zero; if so, Alice wins, otherwise Bob wins
    print(int(n) % 4 and "Alice" or "Bob")


# https://github.com/VaHiX/codeForces/