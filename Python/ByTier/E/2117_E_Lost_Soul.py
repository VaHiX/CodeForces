# Problem: CF 2117 E - Lost Soul
# https://codeforces.com/contest/2117/problem/E

"""
E. Lost Soul

Purpose:
    Given two arrays a and b of length n, determine the maximum number of positions where a[i] == b[i] 
    after performing operations. Each operation allows choosing index i (1 <= i <= n-1) and either:
        - set a[i] := b[i+1], or
        - set b[i] := a[i+1].
    Additionally, we may remove one pair of elements from both arrays at most once before any operations.

Algorithms/Techniques:
    - Greedy approach with backward iteration
    - Tracking used values to prevent conflicts
    - Preprocessing with suffix arrays or flags

Time Complexity: O(n) per test case
Space Complexity: O(n) for auxiliary array q

"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split())) + [n + 1]  # Add sentinel to avoid index overflow
    b = list(map(int, input().split())) + [n + 1]
    q = [0] * (n + 2)  # Array to track which values are used in current process
    
    for i in range(n - 1, -1, -1):  # Iterate backwards from n-1 to 0
        # If a[i] == b[i], or if any of the following conditions hold:
        #   - a[i] has already been marked as used
        #   - b[i] has already been marked as used
        #   - a[i] equals next element in a (a[i+1])
        #   - b[i] equals next element in b (b[i+1])
        if a[i] == b[i] or a[i] == a[i + 1] or b[i] == b[i + 1] or q[a[i]] or q[b[i]]:
            print(i + 1)  # Print the position (1-indexed)
            break
        
        # Mark next elements as used for future checks
        if i < n - 1:
            q[a[i + 1]] = 1
            q[b[i + 1]] = 1
    
    else:
        print(0)  # If no conflict was found during the loop, return 0


# https://github.com/VaHiX/codeForces/