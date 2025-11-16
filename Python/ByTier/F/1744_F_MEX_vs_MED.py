# Problem: CF 1744 F - MEX vs MED
# https://codeforces.com/contest/1744/problem/F

"""
Code Purpose:
This code solves the problem of counting subsegments in a permutation where the MEX (minimum excludant) 
is greater than the MED (median). The approach uses an efficient method to compute the number of valid 
subsegments by leveraging the positions of elements in the permutation.

Algorithms/Techniques:
- MEX and MED computation for subarrays
- Efficient sliding window technique
- Position mapping for quick lookups

Time Complexity: O(n^2) in worst case, but optimized for most practical inputs due to early termination conditions
Space Complexity: O(n) for storing the position map and other variables

The algorithm tracks the minimum and maximum positions of elements seen so far, and uses these to 
calculate the number of valid subsegments ending at each step.
"""

tests = int(input())
for it in range(tests):
    n = int(input())
    a = [int(x) for x in input().split()]
    d = dict()
    for i in range(n):
        d[a[i]] = i
    ans = 1  # For subsegment [0] which always satisfies the condition
    l = d[0]
    r = d[0]
    cur = 0
    for i in range(2, n + 1):
        local = 0
        k = (i - 1) // 2
        l = min(l, d[k])
        r = max(r, d[k])
        lr = max(r, i - 1)  # Left boundary of valid range
        rr = min(n - 1, l + i - 1)  # Right boundary of valid range
        local += max(0, rr - lr + 1)  # Count of valid subsegments
        ans += local
    print(ans)


# https://github.com/VaHiX/CodeForces/