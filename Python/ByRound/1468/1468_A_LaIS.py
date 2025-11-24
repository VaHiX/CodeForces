# Problem: CF 1468 A - LaIS
# https://codeforces.com/contest/1468/problem/A

"""
Algorithm: Longest Almost Increasing Subsequence (LaIS)
Techniques: Stack-based approach with monotonic stack and binary search

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for the auxiliary arrays

This implementation uses a stack-based strategy to maintain the longest 
almost increasing subsequence. It tracks minimum values in segments using 
a monotonic stack and binary search operations to efficiently place elements.
"""

import bisect as bs

for _ in range(int(input())):
    n, a = int(input()), list(map(int, input().split()))
    stack, m, p = [a[0]], [], [(1000000, 0)]  # stack stores current sequence, m tracks min values, p is monotonic stack
    for v in a[1:]:
        k = bs.bisect_right(m, v)  # Find where to insert v in m to maintain sorted order
        if k == len(m):  # If v is larger than all elements in m
            stack.append(v)  # Add to stack
            m.append(min(stack[-1], stack[-2]))  # Update min value for new segment
        else:  # Replace existing element
            stack[k + 1] = m[k] = v  # Update both stack and min value tracking
        while p[-1][0] <= v:  # Maintain monotonic property of p
            vv, kk = p.pop()  # Pop from p
            m[kk] = min(m[kk], vv)  # Update min values accordingly
        if k + 1 < len(m):  # If not at end of m
            p.append((v, k + 1))  # Push to p for monotonic tracking
    print(len(stack))  # Length of longest almost increasing subsequence


# https://github.com/VaHiX/codeForces/