# Problem: CF 2116 A - Gellyfish and Tricolor Pansy
# https://codeforces.com/contest/2116/problem/A

"""
Problem: Determine the winner of a game between Gellyfish and Flower based on their HP and knight HP.

Algorithms/Techniques:
- Greedy simulation approach
- Optimal play analysis

Time Complexity: O(1) per test case
Space Complexity: O(1)

The key insight is that both players play optimally. The decision depends on the minimum HP of each player's unit (either the player himself or his knight). The game essentially ends when one of these minimums reaches zero, and we compare how many turns each side can survive.
"""

for _ in range(int(input())):
    a, b, c, d = map(int, input().split())
    # Compare the minimum HP of each player (player's HP or knight's HP)
    # If Gellyfish's minimum is greater than Flower's, then Gellyfish wins
    print(["Gellyfish", "Flower"][min(b, d) > min(a, c)])


# https://github.com/VaHiX/codeForces/