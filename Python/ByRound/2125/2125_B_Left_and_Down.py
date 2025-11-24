# Problem: CF 2125 B - Left and Down
# https://codeforces.com/contest/2125/problem/B

# Flowerbox
"""
Problem: B. Left and Down

Purpose:
  Determine the minimum cost to move a robot from position (a, b) to (0, 0) on an infinite grid using allowed moves 
  of form (dx, dy) where 0 <= dx, dy <= k. Each unique pair (dx, dy) has a cost of 1 if used for the first time,
  otherwise 0.

Algorithms/Techniques:
  - Mathematical approach based on GCD (Greatest Common Divisor)
  - Greedy logic to minimize number of distinct operations

Time Complexity: O(1) per test case
Space Complexity: O(1)

Approach:
  We observe that the minimum number of operations needed is determined by how many distinct pairs (dx, dy) 
  are required such that their combined movements sum up to the total horizontal and vertical distance.
  
  Let's define:
    - g = gcd(a, b): the greatest common divisor of a and b.
    - If max(a,b) <= k * g, we can move in one go using a single distinct pair.
    - Otherwise, we need at least two operations because we must break down the movement into multiple steps 
      where each step uses a valid (dx, dy) from [0, k].
    
  So, if max(a,b) > k * gcd(a,b), we need at least 2 distinct operations.
  But if max(a,b) <= k * gcd(a,b), we may still use only one pair, but with multiple operations.
  
  Therefore:
    - If max(a,b) <= k * gcd(a,b): cost = 1
    - Else: cost = 2
"""

import math

for s in [*open(0)][1:]:
    *a, k = map(int, s.split())  # Read a, b and k from input line; unpacking into list 'a' and last element as k
    print(1 + (max(*a) > math.gcd(*a) * k))  # Compute cost using mathematical condition


# https://github.com/VaHiX/codeForces/