# Problem: CF 2008 G - Sakurako's Task
# https://codeforces.com/contest/2008/problem/G

"""
G. Sakurako's Task

Purpose:
This code solves a problem involving maximizing the k-th missing non-negative integer in an array after performing allowed operations.
The allowed operation is: choose two indices i and j such that a[i] >= a[j], then update a[i] = a[i] - a[j] or a[i] = a[i] + a[j].
These operations allow us to generate new values based on GCD relationships.

Key insight:
- All numbers can be reduced to multiples of their GCD.
- The maximum value of mex_k depends on how many non-negative integers we can represent,
  which in turn relates to the structure defined by the GCD and allowed moves.

Algorithms/Techniques:
- Use GCD (Greatest Common Divisor) to simplify array elements
- Modular arithmetic to determine position of k-th missing number
- Special cases for n=1

Time Complexity: O(n * log(max(a))) per test case due to GCD computation
Space Complexity: O(1) excluding input storage

"""

import math
import sys

input = lambda: sys.stdin.readline().strip()
kase = int(input())
outs = []
for _ in range(kase):
    n, k = map(int, input().split())
    nums = list(map(int, input().split()))
    if n == 1:
        # For single element, mex_k is simply k - 1 if k <= nums[0]
        # Otherwise it's k (we can't avoid using values >= nums[0])
        if k <= nums[0]:
            outs.append(k - 1)
        else:
            outs.append(k)
    else:
        # Calculate GCD of all elements
        d = math.gcd(*nums)
        # If k is too large, the result is straightforward based on n and k
        if k > (n - 1) * (d - 1):
            outs.append(n + k - 1)
        else:
            # Decompose k into quotient and remainder with respect to d-1
            x, rare = divmod(k - 1, d - 1)
            # Compute the result using derived formula
            outs.append(d * x + rare + 1)
print("\n".join(map(str, outs)))



# https://github.com/VaHiX/codeForces/