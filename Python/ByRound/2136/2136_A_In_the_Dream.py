# Problem: CF 2136 A - In the Dream
# https://codeforces.com/contest/2136/problem/A

"""
A. In the Dream
time limit per test1 second
memory limit per test256 megabytes

Algorithms/Techniques: 
    - Simple validation based on constraints of consecutive scoring
    - Checks if score differences in either half violate the rule that neither team can have 
      three consecutive goals.

Time Complexity: O(1) per test case, as we perform a constant number of operations.
Space Complexity: O(1), as we only use a fixed amount of extra space.

The problem checks if a given score distribution in two football halves is valid under the rule
that no team can score three consecutive goals in either half. We calculate the score changes 
between halves and validate that the maximum score difference in either half doesn't exceed 
a threshold based on the minimum difference, which ensures no three consecutive goals.
"""

for _ in range(int(input())):
    a, b, c, d = map(int, input().split())
    t1 = c - a  # Score difference in first half
    t2 = d - b  # Score difference in second half
    if max(a, b) > 2 * min(a, b) + 2 or max(t1, t2) > 2 * min(t1, t2) + 2:
        print("No")
    else:
        print("Yes")


# https://github.com/VaHiX/codeForces/