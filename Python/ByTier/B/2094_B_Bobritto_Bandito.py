# Problem: CF 2094 B - Bobritto Bandito
# https://codeforces.com/contest/2094/problem/B

"""
B. Bobritto Bandito
Algorithm: Simulation of plague spread on infinite line
Time Complexity: O(1) per test case
Space Complexity: O(1)

The plague starts at house 0 on day 0 and spreads one house per day outward,
forming a continuous segment [l, r] where l is the leftmost infected house
and r is the rightmost infected house.

Each day, the infection expands by 1 unit to both sides (left and right),
so after n days, if the initial infection was at 0, then the interval becomes
[-n, n]. Given an interval [l, r] after n days, we need to find a valid
interval [l', r'] that could have existed on day m (where m <= n).
"""

for s in [*open(0)][1:]:
    n, m, l, r = map(int, s.split())
    # Compute the new left boundary: max(-m, l) ensures it doesn't go too far left
    print(l := max(-m, l), l + m)


# https://github.com/VaHiX/codeForces/