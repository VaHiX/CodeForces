# Problem: CF 1715 C - Monoblock
# https://codeforces.com/contest/1715/problem/C

"""
Algorithm: Dynamic Programming with Block Counting

This solution efficiently calculates the sum of awesomeness for all subsegments
after each update operation. The key idea is to maintain a running total of
awesomeness and update it incrementally when an element is changed.

Approach:
1. Precompute the initial sum of awesomeness for all subsegments
2. For each update, determine how the change affects the total by:
   - Identifying adjacent blocks that are broken or formed
   - Adjusting the total sum accordingly
3. Maintain a running total to avoid recalculating everything from scratch

Time Complexity: O(n + m)
Space Complexity: O(1) additional space (excluding input/output)

The formula for the initial computation uses the fact that each transition
between different consecutive elements contributes to the sum in a specific way.
"""

import sys

input = sys.stdin.readline
ans = []
n, m = map(int, input().split())
a = list(map(int, input().split()))
# Initialize the total awesomeness sum for all subsegments
b = n + n * (n - 1) // 2
# Add contribution from adjacent different elements
for i in range(n - 1):
    if a[i] != a[i + 1]:
        b += (i + 1) * (n - i - 1)
for _ in range(m):
    i, x = map(int, input().split())
    i -= 1  # Convert to 0-based indexing
    # Remove the effect of the old value's adjacent transitions
    if i > 0 and a[i] != a[i - 1]:
        b -= i * (n - i)
    if i < n - 1 and a[i] != a[i + 1]:
        b -= (i + 1) * (n - i - 1)
    a[i] = x  # Update the array
    # Add the effect of the new value's adjacent transitions
    if i > 0 and a[i] != a[i - 1]:
        b += i * (n - i)
    if i < n - 1 and a[i] != a[i + 1]:
        b += (i + 1) * (n - i - 1)
    ans.append(b)
for i in ans:
    print(i)


# https://github.com/VaHiX/CodeForces/