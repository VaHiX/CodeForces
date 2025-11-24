# Problem: CF 1612 F - Armor and Weapons
# https://codeforces.com/contest/1612/problem/F

"""
Algorithm: BFS with pruning
Time Complexity: O(max(n,m)^2 * max(n,m) * log(max(n,m)))
Space Complexity: O(max(n,m)^2)

This problem involves finding the minimum number of hours to obtain the n-th armor set and m-th weapon.
Each hour, we can obtain either a new armor set or a new weapon. The key insight is to model this as a graph
where each node represents (armor_level, weapon_level) and edges represent obtaining a new item.
We use BFS to explore the minimum number of steps and prune redundant states.

The solution uses a BFS approach to find the minimum number of steps.
At each step, we simulate all possible moves:
- Obtain a new armor set (if we can afford it with current power)
- Obtain a new weapon (if we can afford it with current power)
We also check synergy pairs and adjust power calculation accordingly.
"""

from itertools import permutations


def solve(m, n, arr):
    # Start with the initial state (1, 1) - first armor and first weapon
    level = [(1, 1)]

    # Iterate through possible number of hours (up to max(m,n) + 1)
    for i in range(max(m, n) + 1):
        l2 = []
        # For each current state (x,y), try all possible next moves
        for x, y in level:
            # If we have both items, we're done
            if x >= m and y >= n:
                return i
            # Check if current combination has synergy
            delta = (x, y) in arr
            # Obtain a new armor set if possible
            l2 += [(min(x + y + delta, m), y)]
            # Obtain a new weapon if possible
            l2 += [(x, min(x + y + delta, n))]

        # Remove duplicate states
        l2 = set(l2)
        l3 = l2
        
        # Pruning: Remove dominated states (where one state is worse in both dimensions)
        for (x1, y1), (x2, y2) in permutations(l2, 2):
            if x1 <= x2 and y1 <= y2:
                l2.discard((x1, y1))

        level = list(l3)


m, n = map(int, input().split())
r = int(input())
arr = set()
for _ in range(r):
    x, y = map(int, input().split())
    arr.add((x, y))

print(solve(m, n, arr))


# https://github.com/VaHiX/CodeForces/