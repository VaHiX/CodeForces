# Problem: CF 2053 B - Outstanding Impressionist
# https://codeforces.com/contest/2053/problem/B

"""
B. Outstanding Impressionist

Purpose:
This code determines whether each of the n impressions (represented as intervals [l_i, r_i]) 
can be made unique in a sequence of n integers such that all other elements differ from it.

Algorithm:
- Uses a difference array technique to efficiently compute how many free values exist in a range.
- Preprocesses interval constraints to mark blocked values and compute prefix sums.
- For each impression, checks if there are enough free integer values to ensure uniqueness.

Time Complexity: O(n) per test case
Space Complexity: O(n)

"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    a = [tuple(map(int, input().split())) for _ in range(n)]
    ok = [1] * (2 * n + 1)  # Difference array to track free values
    ok[0] = 0               # Base case: no value before 1
    blocked = [0] * (2 * n + 1)  # Count how many intervals block a specific value
    
    # Mark blocked values and update ok array for single-value intervals
    for l, r in a:
        if l == r:
            ok[l] = 0       # Value l is blocked (cannot be used)
            blocked[l] += 1 # Increment the count of blocks on this value
            
    # Compute prefix sum to get total free values up to each point
    for i in range(1, 2 * n + 1):
        ok[i] += ok[i - 1]
        
    ans = []
    for i, (l, r) in enumerate(a):
        # Count the number of free values in the interval [l, r]
        free = ok[r] - ok[l - 1]
        
        # If the interval is a singleton and it's blocked exactly once,
        # we can reuse that single value only if there are extra options elsewhere
        if l == r and blocked[l] == 1:
            free += 1
            
        ans.append(int(free > 0))  # Append 1 if there are free values, 0 otherwise
        
    print("".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/