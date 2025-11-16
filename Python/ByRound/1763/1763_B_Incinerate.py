# Problem: CF 1763 B - Incinerate
# https://codeforces.com/contest/1763/problem/B

"""
Algorithm: Greedy Simulation
Approach:
- Sort monsters by power in ascending order to process them from weakest to strongest.
- For each monster, simulate the damage dealt until the monster's health is reduced to zero or less.
- After each attack, update the effective damage (k) by subtracting the current weakest monster's power.
- If at any point the effective damage becomes zero or negative, return "NO".
- If all monsters are killed, return "YES".

Time Complexity: O(n log n) due to sorting, where n is the number of monsters.
Space Complexity: O(n) for storing monster data.

Techniques:
- Sorting
- Greedy simulation
- Accumulative damage adjustment
"""

def f():
    n, k = map(int, input().split())
    # Sort monsters by power (p) in ascending order
    mons = sorted(
        (p, h) for h, p in zip(map(int, input().split()), map(int, input().split()))
    )
    damage = k  # Effective damage after subtraction of weakest monster's power
    for p, h in mons:
        # While monster's health is greater than current damage
        while h > damage:
            k -= p  # Reduce k by the power of the weakest monster
            if k <= 0:  # If damage becomes non-positive, Genos fails
                return "NO"
            damage += k  # Update damage with remaining k
    return "YES"


for _ in range(int(input())):
    print(f())


# https://github.com/VaHiX/CodeForces/