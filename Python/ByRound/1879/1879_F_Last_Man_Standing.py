# Problem: CF 1879 F - Last Man Standing
# https://codeforces.com/contest/1879/problem/F

"""
Code Purpose:
This solution computes the maximum points each hero can achieve across all possible values of x (from 1 to infinity) in a game where heroes are attacked in rounds with x damage per round. It uses a sophisticated approach involving sorting, prefix sums, and binary search-like logic to determine optimal attack rounds.

Algorithms/Techniques:
- Sorting with custom key function (bit manipulation for ranking)
- Prefix sum computation
- Binary search over the range of x values
- Optimization to track maximum health heroes with armor constraints

Time Complexity: O(n log n + m * sqrt(m))
Space Complexity: O(n + m)

Where n is the number of heroes, and m is the maximum armor value.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Custom hashing function using bit manipulation
    return u << 20 ^ v


t = int(input())
for _ in range(t):
    n = int(input())
    h = list(map(int, input().split())) + [-1]  # Append -1 as sentinel
    a = list(map(int, input().split()))
    z = [f(a[i], i) for i in range(n)]  # Create array with custom keys
    z = [i & 0xFFFFF for i in sorted(z)] + [n]  # Sort and mask to get indices
    ma1, ma2 = [-1] * n, [-1] * n  # Track max and second max heroes
    m1, m2 = n, n  # Initialize with sentinel
    p = [n] * (n + 1)  # Position mapping
    
    # Iterate backwards to determine max heroes by health
    for i in range(n - 1, -1, -1):
        j = z[i]
        p[j] = i  # Map armor value to index
        if h[m1] < h[j]:
            m1, m2 = j, m1
        elif h[m2] < h[j]:
            m2 = j
        ma1[i], ma2[i] = m1, m2

    m = max(a) + 1  # Maximum armor + 1
    s0 = [0] * (m + 1)  # Prefix sum array for armor counts
    
    # Build prefix sum of armor values
    for i in a:
        s0[i + 1] += 1
    for i in range(1, m + 1):
        s0[i] += s0[i - 1]

    ans = [0] * n  # Final result array
    
    # Process all possible x values from 1 to m
    for x in range(1, m + 1):
        u, v, j = 0, 0, -1  # u = max score, v = second max, j = hero index
        y = 1  # Round counter
        # Process intervals of size x
        for l in range(1, m + 1, x):
            r = min(l + x, m)
            if s0[l] == s0[r]:
                y += 1
                continue
            ll, rr = s0[l], s0[r] - 1  # Determine interval boundaries
            i = ma1[ll]  # Get max health hero in interval
            if ll <= p[i] <= rr:
                s = y * h[i]
                if u < s:
                    u, v, j = s, u, i
                elif v < s:
                    v = s
            i = ma2[ll]  # Get second max health hero in interval
            if ll <= p[i] <= rr:
                s = y * h[i]
                if u < s:
                    u, v, j = s, u, i
                elif v < s:
                    v = s
            y += 1  # Increment round
        ans[j] = max(ans[j], u - v)
    sys.stdout.write(" ".join(map(str, ans)) + "\n")


# https://github.com/VaHiX/CodeForces/