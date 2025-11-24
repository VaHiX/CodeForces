# Problem: CF 1982 A - Soccer
# https://codeforces.com/contest/1982/problem/A

"""
Soccer Game Analysis
=====================
Problem Description:
Given initial and final scores of a soccer game, determine if it's possible that 
the teams never had an equal score during the time Dima was away.

Key Insights:
- If the initial score is x1:y1 and final score is x2:y2
- The difference in goals for each team is (x2-x1) and (y2-y1) respectively
- If initially x1 < y1, then for the teams to never be equal, 
  the final score must also be x2 < y2 (first team never catches up)
- Similarly for y1 < x1 case

Techniques:
- Simple mathematical reasoning based on relative score differences
- No complex algorithms needed

Time Complexity: O(1) per test case
Space Complexity: O(1) for auxiliary space (not counting output)
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    x1, y1 = map(int, input().split())
    x2, y2 = map(int, input().split())

    # Check if the first team was behind initially and remained behind
    # This means x1 < y1 and x2 < y2 (first team never catches up)
    if x1 < y1 and x2 < y2:
        return "YES"
    
    # Check if the second team was behind initially and remained behind
    # This means y1 < x1 and y2 < x2 (second team never catches up)
    if y1 < x1 and y2 < x2:
        return "YES"
    
    # Otherwise, there must have been a time when scores were equal
    return "NO"


ans = []
for _ in range(int(input())):
    ans += [solve_case()]
print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/