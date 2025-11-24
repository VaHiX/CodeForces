# Problem: CF 2101 D - Mani and Segments
# https://codeforces.com/contest/2101/problem/D

"""
D. Mani and Segments

Purpose:
    This code counts the number of "cute" subarrays in a given permutation.
    A subarray is considered "cute" if the sum of the lengths of its Longest Increasing Subsequence (LIS) 
    and Longest Decreasing Subsequence (LDS) equals the length of the array plus one.
    
Algorithms/Techniques:
    - Monotonic stack technique to efficiently compute left and right boundaries for each element
      where the current element is either the maximum or minimum in some subarray
    - For each element, we track how many elements it dominates on both sides
    - Reversing the array allows us to reuse the same logic for computing right boundaries

Time Complexity:
    O(n) per test case, since each element is pushed and popped from stacks at most once.
Space Complexity:
    O(n) for storing arrays and stacks.

"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, s = int(input()), 0
    a = [0] + list(map(int, input().split()))  # Add dummy 0 at start for 1-based indexing
    l = [0] * (n + 1)                          # Left boundary for each index
    c, s1, s2 = [0] * (n + 1), [], []          # Count of active elements, monotonic stacks
    
    # Compute left boundaries using increasing and decreasing stacks
    for i in range(1, n + 1):
        l[i] = l[i - 1]                        # Default to previous left boundary
        while s1 and a[s1[-1]] < a[i]:         # While element at stack top is smaller than current
            p = s1.pop()                       # Pop it from stack
            c[p] -= 1                          # Decrement its count in the count array
            if not c[p]:
                l[i] = max(l[i], p)            # Update left boundary if no more elements need this one
        while s2 and a[s2[-1]] > a[i]:         # While element at stack top is larger than current
            p = s2.pop()                       # Pop it from stack
            c[p] -= 1                          # Decrement its count in the count array
            if not c[p]:
                l[i] = max(l[i], p)            # Update left boundary if no more elements need this one
        s1.append(i)                           # Add current index to increasing stack
        s2.append(i)                           # Add current index to decreasing stack
        c[i] = 2                               # Initially set count for each element as 2
    
    # Reverse the array to reuse the same logic for computing right boundaries
    a = [0] + a[1:][::-1]
    r = [0] * (n + 1)                          # Right boundary for each index
    c, s1, s2 = [0] * (n + 1), [], []          # Reinitialize stacks and count array
    
    # Compute right boundaries using increasing and decreasing stacks
    for i in range(1, n + 1):
        r[i] = r[i - 1]                        # Default to previous right boundary
        while s1 and a[s1[-1]] < a[i]:         # While element at stack top is smaller than current
            p = s1.pop()
            c[p] -= 1                          # Decrement its count in the count array
            if not c[p]:
                r[i] = max(r[i], p)            # Update right boundary if no more elements need this one
        while s2 and a[s2[-1]] > a[i]:         # While element at stack top is larger than current
            p = s2.pop()
            c[p] -= 1                          # Decrement its count in the count array
            if not c[p]:
                r[i] = max(r[i], p)            # Update right boundary if no more elements need this one
        s1.append(i)                           # Add current index to increasing stack
        s2.append(i)                           # Add current index to decreasing stack
        c[i] = 2                               # Initially set count for each element as 2
    
    # Reverse the right boundary array back to original orientation
    r = [0] + r[1:][::-1]
    
    # Transform r[i] from index in reversed array to actual index in normal array
    for i in range(1, n + 1):
        r[i] = n - r[i] + 1
    
    # Calculate total sum based on formula derived from bounds
    for i in range(1, n + 1):
        s += (i - l[i]) * (r[i] - i)
        if i > 1:
            s -= (i - 1 - l[i]) * (r[i - 1] - i)  # Adjust overlapping regions
    
    print(s)


# https://github.com/VaHiX/codeForces/