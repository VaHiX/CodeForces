# Problem: CF 1687 A - The Enchanted Forest
# https://codeforces.com/contest/1687/problem/A

"""
A. The Enchanted Forest

Algorithms/Techniques:
- Sliding window technique with prefix sums
- Optimization of movement strategy by considering only k positions (or n if k < n)
- Using prefix sum array for efficient range sum queries

Time Complexity: O(n) per test case, where n is the number of points in the forest.
Space Complexity: O(n) for storing the prefix sum array and auxiliary variables.

Marisa can move at most 1 unit per minute and collects mushrooms at each point she visits.
Each minute, new mushrooms appear on all points (equal to the initial mushroom count at that point).
We model a sliding window of size k (or n if k > n) over the forest and compute the maximum sum
of mushrooms collected within any such window after adjustment for the "k choose 2" cost
from movement and the increase due to new mushrooms.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
t = int(input())
ans = []
for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    
    # Add (k - 1) to each element to simulate the "new mushrooms" that appear at each step
    for i in range(n):
        a[i] += k - 1
    
    # Limit k to n since Marisa can't move more than n steps anyway
    k = min(n, k)
    
    # Build prefix sum array for efficient range queries
    cnt = [0]
    for i in a:
        cnt.append(i + cnt[-1])
    
    # Initialize answer
    ans0 = 0
    
    # Compute the value of k * (k - 1) // 2, which represents cost of moving in optimal path
    x = k * (k - 1) // 2
    
    # Slide window over all valid starting positions for a group of k consecutive points
    for i in range(k, n + 1):
        ans0 = max(cnt[i] - cnt[i - k] - x, ans0)
    
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/