# Problem: CF 1970 B3 - Exact Neighbours (Hard)
# https://codeforces.com/contest/1970/problem/B3

"""
Code Purpose:
This code solves the problem of placing n wizards' houses on an n×n grid such that:
1. Each wizard's house is at a unique column (no two houses in the same column).
2. Each wizard can visit another wizard's house at a specific distance a_i.
3. The layout respects the view constraints (houses in same column are not allowed).

Algorithm:
- The algorithm uses a greedy approach to arrange wizards in order of decreasing distances.
- Special cases are handled for small n and specific patterned inputs.
- The placement logic ensures that distance requirements are satisfied and no column violates the view constraint.

Time Complexity:
O(n log n) due to sorting the wizards by their required distances in descending order.

Space Complexity:
O(n) for storing positions and where mappings.
"""

from sys import stdin


def place_wizards(r):
    wizards = list(range(n))
    x = 1
    prev_y = 1
    result = [None] * n
    where = [1] * n
    wizards.sort(key=lambda w: -r[w]) # Sort wizards by required distance in descending order
    if r[wizards[-1]] == 0: # If the wizard with minimum distance needs zero distance
        w0 = wizards[-1]
        result[w0] = (x, 1)
        where[w0] += w0
        wizards.pop()
        x += 1
        prev_w = w0
    elif n >= 3 and [r[w] for w in wizards[:-4:-1]] == [1, 2, 3]: # Special case for specific distances
        one, two, three = wizards[:-4:-1]
        wizards[-3:] = []
        result[three] = (x, 2)
        result[two] = (x + 1, 1)
        result[one] = (x + 2, 1)
        where[three] += one
        where[two] += three
        where[one] += two
        x += 3
        prev_w = one
    else: # General case: handle pairs of wizards with same distance
        for a, b in zip(wizards, wizards[1:]):
            if r[a] == r[b]:
                break
        else:
            assert False
        wizards.remove(a)
        wizards.remove(b)
        result[a] = (x, r[a])
        result[b] = (x + 1, 1)
        where[a] += b
        where[b] += a
        x += 2
        prev_w = b
    prev_y = 1

    for w in wizards: # Place remaining wizards
        if r[w] == 0:
            result[w] = (x, 1)
            where[w] += w
        else:
            if prev_y - r[w] + 1 >= 1:
                y = prev_y - r[w] + 1
            else:
                y = prev_y + r[w] - 1
                assert y <= n
            result[w] = (x, y)
            where[w] += prev_w
        prev_y = result[w][-1]
        prev_w = w
        x += 1
    return result, where


n = int(stdin.readline())
r = list(map(int, stdin.readline().split()))
if n == 2 and sorted(r) == [1, 2]: # Handle special invalid case
    print("NO")
else:
    positions, where = place_wizards(r)
    print("YES")
    for x, y in positions:
        print(x, y)
    print(*where)


# https://github.com/VaHiX/CodeForces/