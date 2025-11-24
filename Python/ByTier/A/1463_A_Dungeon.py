# Problem: CF 1463 A - Dungeon
# https://codeforces.com/contest/1463/problem/A

# ==============================================================================
# Problem: Dungeon
# Purpose: Determine if all three monsters can be killed simultaneously with an enhanced shot.
# Algorithm:
#   - The total damage needed is a + b + c.
#   - Enhanced shots occur every 7th shot and deal 1 damage to all monsters.
#   - Regular shots deal 1 damage to one monster each.
#   - Strategy:
#     * Try to use combinations of regular and enhanced shots such that
#       all three monsters die at the same time (i.e., on an enhanced shot).
#     * Let x = number of regular shots, y = number of enhanced shots.
#     * After x regular shots + y enhanced shots:
#         Total shots = x + y
#         Enhanced shots = y (every 7th)
#         Then: x = 7*y - (some offset) and total damage distributed properly.
#     * Optimization:
#         We observe that:
#         s = a + b + c (total HP)
#         Total regular shots needed to distribute damage = s - 9*(number of enhanced shots),
#         where number of enhanced shots is some integer k.
#         For the final shot to be an enhanced one:
#            Total shots = 7*k
#            Regular shots = 7*k - k = 6*k
#            So we have: a+b+c = 6*k + (a+b+c-k) -> invalid.
#         Better insight:
#            Let s = total health.
#            To end with enhanced shot:
#              s must be divisible by 9, and the enhanced shots are used in full.
#              If s % 9 == 0 and s <= 9 * min(a,b,c), then YES.
#           BUT that logic is simplified and not completely accurate from problem analysis.
#
# Approach: Simplified check using sum and minimum:
#   - If sum < 9 or sum > 9 * min(a,b,c) -> NO
#   - Else return YES
# Time Complexity: O(1)
# Space Complexity: O(1)
# ==============================================================================

for s in [*open(0)][1:]:
    a = (*map(int, s.split()),)  # Convert input line to tuple of integers a, b, c
    s = sum(a)                   # Compute total health points
    print("YNEOS"[0 < s % 9 or s > 9 * min(a) :: 2])  # Check condition and print YES/NO


# https://github.com/VaHiX/codeForces/