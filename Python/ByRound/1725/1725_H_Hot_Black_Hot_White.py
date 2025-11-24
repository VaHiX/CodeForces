# Problem: CF 1725 H - Hot Black Hot White
# https://codeforces.com/contest/1725/problem/H

"""
Code Purpose:
This code solves the problem of coloring N magical stones (N being even) either black (0) or white (1), 
such that exactly N/2 stones are black and N/2 are white. The goal is to choose a magic coefficient Z 
(0 <= Z <= 2) such that no pair of stones with different colors causes a reaction. A reaction occurs 
if the condition (concat(A_i, A_j) * concat(A_j, A_i) + A_i * A_j) % 3 == Z is satisfied.

The approach uses modular arithmetic to simplify the problem:
- We reduce each stone's strength modulo 3 and square it (since A_i * A_i mod 3 is sufficient for pattern matching).
- Using frequency counts of values mod 3, we decide a "majority class" to be colored white (1) to minimize conflicts.
- Color the stones accordingly to ensure equal distribution of colors and no reactions.

Algorithms/Techniques:
- Modular arithmetic to reduce problem space
- Frequency counting to identify dominant classes
- Greedy assignment of colors

Time Complexity: O(N) - Single pass through the array for processing and coloring.
Space Complexity: O(1) - Only using a constant amount of extra space (Counter and temporary variables).
"""

from sys import stdin

input = lambda: stdin.readline().rstrip("\r\n")
from collections import Counter

n = int(input())
# Precompute A_i^2 % 3 for each stone strength
a = list(map(lambda x: int(x) * int(x) % 3, input().split()))
# Count occurrences of each mod value
f = Counter(a)
# Choose the color class that has more stones to be the 'white' class (1)
# If count of 0 mod is >= count of 1 mod, set mx = 0; otherwise set mx = 1
mx = 0 if f[0] >= f[1] else 1

# Determine the magic coefficient Z based on the chosen dominant class
# (mx - 1) % 3 ensures Z is in [0,2] and avoids conflict with the current class
print((mx - 1) % 3)
ct, ans = 0, []
# Assign colors greedily to meet the half-half requirement
for x in a:
    # If the current stone's mod value matches the dominant class and we haven't filled all slots yet for that class,
    # color this stone as white (1)
    if x == mx and ct < n // 2:
        ans += ["1"]
        ct += 1
    else:
        # Otherwise, assign as black (0)
        ans += ["0"]
# Output the final color assignment string
print("".join(ans))


# https://github.com/VaHiX/CodeForces/