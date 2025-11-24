# Problem: CF 1785 A - Monsters (easy version)
# https://codeforces.com/contest/1785/problem/A

"""
Monsters (easy version)
Algorithm: Greedy with sorting
Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) excluding input storage

This problem involves minimizing the number of type-1 spells needed to kill all monsters,
given that we can cast at most one type-2 spell which deals 1 damage to all alive monsters
and repeats until no more monsters die.

Approach:
- Sort monsters by health in ascending order.
- For each monster in sorted order, decide if it's better to use a type-2 spell
  before this monster or to deal damage individually using type-1 spells.
- 'tt1' keeps track of how much total damage we've already applied via type-1 spells
  before reaching current monster, ensuring no two monsters share same health level.
- If current monster's health is greater than the accumulated damage (tt1),
  we use one type-1 spell to reduce its health by 1 and increment tt1.
- The difference between monster's health and tt1 represents additional required type-1 spells.
"""
import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    [n] = list(map(int, input().split()))
    arr = list(map(int, input().split()))
    tt1 = 0  # Tracks accumulated damage from type-1 spells
    ans = 0  # Total count of type-1 spells used
    arr.sort()  # Sort monsters by health to process from smallest to largest
    for i in range(n):
        if arr[i] > tt1:
            tt1 += 1  # If monster's HP exceeds accumulated damage, use one type-1 spell
        ans += arr[i] - tt1  # Add remaining damage needed for this monster via type-1 spells
    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/