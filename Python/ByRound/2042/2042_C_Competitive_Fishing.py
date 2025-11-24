# Problem: CF 2042 C - Competitive Fishing
# https://codeforces.com/contest/2042/problem/C

"""
C. Competitive Fishing

Algorithm:
This problem involves splitting n fishes into m groups such that Bob's score exceeds Alice's score by at least k.
The key insight is to use a greedy approach:
- First, we compute a "gain" array where each element represents the difference in score if we place a fish in a group versus not.
- We then sort these gains and greedily select the largest ones to maximize the difference in scores.
- Binary search or direct simulation can be used to determine the minimum number of groups.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the gain array

Techniques:
- Greedy algorithm with sorting
- Prefix sum-like computation for group assignment
"""

import sys

input = lambda: sys.stdin.readline()[:-1]
for _ in [0] * int(input()):
    n, k = map(int, input().split())
    s = input()
    l = [0]
    # Compute prefix-like gain values for each fish
    for i in s[::-1]:  # Iterate from right to left
        l += (l[-1] + (i == "1") * 2 - 1,)  # Add 1 if Bob caught it, subtract 1 if Alice caught it
    l = l[-2:0:-1]  # Reverse and slice to get the correct order
    l.sort()  # Sort gains in ascending order
    ans = 1  # Start with one group
    while l and 0 < k:  # Greedily consume largest gains
        k -= l.pop()  # Take the maximum gain
        ans += 1  # Increment number of groups
    if 0 < k:  # If we still need more points
        print(-1)
    else:
        print(ans)


# https://github.com/VaHiX/codeForces/