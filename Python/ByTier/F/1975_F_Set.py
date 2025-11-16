# Problem: CF 1975 F - Set
# https://codeforces.com/contest/1975/problem/F

"""
Algorithm: Set Intersection and Masking
Purpose: Find all sets S ⊆ {0,1,...,n-1} such that for every non-empty T ⊆ {0,1,...,n-1}, 
         the size of S ∩ T belongs to V_f(T), where V_f(T) is given as a binary encoding.
Time Complexity: O(n * 2^n)
Space Complexity: O(2^n)

Approach:
- The problem involves checking a constraint over all subsets of {0,1,...,n-1}.
- We use dynamic programming with bitmasking:
  1. Preprocess the input sets V_i into a usable form.
  2. Use inclusion-exclusion or a DP-style update on masks to compute valid intersections.
  3. Finally, output those masks s for which the constraint holds.

The given code implements an optimized algorithm that:
- Reads the number of elements n and the list of encodings.
- Updates a 'sizes' array using a technique known as "subset convolution" or "inclusion-exclusion DP".
- Filters valid sets S using the computed 'sizes' array.
- Outputs the count and values of valid sets.

This is a bit manipulation and subset DP optimization.
"""

from sys import stdin

n = int(stdin.readline())
sizes = [1]
sizes.extend(map(int, stdin.readline().split()))

# Dynamic Programming step to update 'sizes' array
# This is a form of subset DP that updates based on bit masking
for elem in reversed(range(n)):
    diff = 1 << elem
    for i in range(1 << n):
        if i & diff == 0:
            # Update values using bitwise operations
            sizes[i], sizes[i | diff] = (
                sizes[i] & sizes[i | diff],
                sizes[i] & sizes[i | diff] >> 1,
            )

# Filter all valid sets S where the constraint is satisfied
# Only those with the least significant bit set in 'sizes[i]' are valid
result = [i for i in range(1 << n) if sizes[i] & 1 == 1]

# Output results
print(len(result))
print(*result, sep="\n")


# https://github.com/VaHiX/CodeForces/