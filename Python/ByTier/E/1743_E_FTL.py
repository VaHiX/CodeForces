# Problem: CF 1743 E - FTL
# https://codeforces.com/contest/1743/problem/E

"""
Code Purpose:
This code solves the problem of finding the minimum time required to destroy an enemy spaceship 
with given durability and shield capacity using two lasers with different powers and reload times.
The approach involves dynamic programming where we track the minimum time to reach each level of 
damage. For each possible damage increment, we evaluate the optimal combination of laser usage 
including single-shot and simultaneous firing, taking into account reload times.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Greedy optimization for laser firing sequences
- Simulation of laser reload states

Time Complexity: O(h^2 * t_max) where h is the enemy durability and t_max is the maximum reload time
Space Complexity: O(h) for the DP array
"""

from math import inf

p1, t1 = map(int, input().split())
p2, t2 = map(int, input().split())
h, s = map(int, input().split())

ans = inf
dp = [inf] * (h + 1)
dp[0] = 0
ts = [t1, t2]
ps = [p1, p2]

for i in range(h):
    for j in range(1, h - i + 1):  # j represents number of shots of one laser
        for k in range(2):  # k represents which laser to use for this shot sequence
            # Calculate next damage state when firing 'j' times using laser k
            ni = min(
                h,
                i + j * (ps[k] - s) + (j * ts[k] // ts[k ^ 1]) * (ps[k ^ 1] - s)
            )
            # If we can destroy the enemy with this sequence
            if ni == h:
                # Update the minimum time needed
                ans = min(ans, dp[i] + j * ts[k])
            # If the firing time of laser k exceeds the reload time of the other laser
            if j * ts[k] >= ts[k ^ 1]:
                # Calculate another potential state by using both lasers
                ni = min(
                    h,
                    i
                    + (j - 1) * (ps[k] - s)
                    + ((j * ts[k] // ts[k ^ 1]) - 1) * (ps[k ^ 1] - s)
                    + (ps[0] + ps[1] - s),
                )
                # Update the DP value if a better path is found
                dp[ni] = min(dp[ni], dp[i] + j * ts[k])

ans = min(ans, dp[h])
print(ans)


# https://github.com/VaHiX/CodeForces/