# Problem: CF 2046 A - Swap Columns and Find a Path
# https://codeforces.com/contest/2046/problem/A

"""
Code Purpose:
This solution computes the maximum cost of a path from (1,1) to (2,n) in a 2xN matrix,
where columns can be swapped to maximize the path sum. The optimal strategy is to
select the maximum value from each column pair and add the minimum value from each
column pair to the total sum.

Algorithms/Techniques:
- Greedy approach: For each column, we pick the maximum value between the two rows,
  and we add the minimum value from that column to the total to ensure optimal path.
- Column swapping is allowed, so we can rearrange columns to place the highest
  values as early as possible in the path.

Time Complexity: O(n)
Space Complexity: O(n)
"""

import sys

data = sys.stdin.read().splitlines()
t = int(data[0])
for tc in range(1, 3 * t + 1, 3):
    n = int(data[tc])
    a1 = list(map(int, data[tc + 1].split()))
    a2 = list(map(int, data[tc + 2].split()))
    a = list(zip(a1, a2))
    print(max(map(min, a)) + sum(map(max, a)))


# https://github.com/VaHiX/CodeForces/