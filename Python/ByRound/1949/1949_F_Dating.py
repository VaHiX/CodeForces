# Problem: CF 1949 F - Dating
# https://codeforces.com/contest/1949/problem/F

"""
Algorithm: Two-Pointer with Set Intersection Optimization
Time Complexity: O(n * m * alpha(m) + n * log(n)) where alpha(m) is inverse Ackermann function
Space Complexity: O(n * m + m)

Approach:
- Process users in descending order of their number of liked activities.
- For each user, check if any previously processed user shares at least one activity.
- If so, verify that both users like at least one activity the other doesn't.
- Use `element_parents` array to track which user last saw an activity for fast lookup.

Steps:
1. Read input and store users' activity sets with index.
2. Sort users by size of activity set (descending).
3. Iterate through sorted users:
   - Find the latest user who also liked an activity (using element_parents).
   - If such user exists, check if both users like unique activities.
   - If yes, print match and exit.
   - Update element_parents for current user's activities.
4. If no match found, output "NO".

This approach avoids checking all pairs explicitly, using a smart lookup table to determine if any prior user shares an activity.
"""

import sys

input = sys.stdin.readline
N, M = map(int, input().split())
sets = [(set([*map(int, input().split())][1:]), i + 1) for i in range(N)]
sets.sort(key=lambda x: len(x[0]), reverse=True)
element_parents = [-1] * M
for i in range(N):
    curr_parent = -1
    for j in sets[i][0]:
        curr_parent = max(curr_parent, element_parents[j - 1])
    if curr_parent != -1:
        for j in sets[i][0]:
            if j not in sets[curr_parent][0]:
                print("YES")
                print(sets[i][1], sets[curr_parent][1])
                sys.exit(0)
    for j in sets[i][0]:
        element_parents[j - 1] = i
print("NO")


# https://github.com/VaHiX/CodeForces/