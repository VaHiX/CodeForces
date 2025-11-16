# Problem: CF 1798 E - Multitest Generator
# https://codeforces.com/contest/1798/problem/E

"""
Multitest Generator Solution

Algorithm:
- This solution uses dynamic programming with suffix processing to determine the minimum number of operations
  required for each prefix of the array to become a multitest.
- The key insight is to compute for each position the "testability" of the suffix starting from that position,
  which is defined recursively based on the length of the suffix and the values in the array.

Time Complexity: O(n) amortized over all test cases
Space Complexity: O(n) for the auxiliary arrays h and s

Techniques:
- Suffix-based dynamic programming
- Reverse iteration to build auxiliary structures
- Fast lookup using precomputed values
"""

import sys

input = lambda: sys.stdin.readline().rstrip()

t = int(input())
while t:
    t -= 1
    n = int(input())
    A = list(map(int, input().split()))
    # h stores the maximum valid test length ending at each position (suffix)
    h = [0]
    for i in range(n - 1, -1, -1):
        a = A[i]
        # idx represents the required length of the test starting at position i
        idx = a + 1
        # If there's a valid value in h at position -a-1 (from current position)
        # we can extend it by 1
        if len(h) >= a + 1 and h[-a - 1] != -1:
            h.append(h[-a - 1] + 1)
        else:
            # No valid extension found, mark as unreachable
            h.append(-1)
    
    # ans stores the result for each prefix
    ans = []
    # s stores the minimum operations needed to make the suffix starting at position i a multitest
    s = [0]
    m = 0  # maximum value in h seen so far
    
    # Process from right to left to determine minimum operations
    for i in range(n - 1):
        cur = m + 1  # current minimal operations needed
        a = A[n - 1 - i]  # value at current position
        
        # Check if we can make a valid split based on s array
        if len(s) >= a + 1 and cur < s[-a - 1] + 1:
            cur = s[-a -1] + 1
        s.append(cur)

        # Determine result based on h and s values
        a = A[n - 2 - i]  # next element backwards
        if a == h[i + 1]:
            # Already satisfies the test condition
            ans.append(0)
        elif a <= s[-1] or h[i + 1] != -1:
            # Can be fixed in one operation
            ans.append(1)
        else:
            # Requires two operations
            ans.append(2)
        
        # Update maximum
        if h[i + 1] > m:
            m = h[i + 1]

    # Reverse the result to match original order
    ans = ans[::-1]
    print(*ans)


# https://github.com/VaHiX/CodeForces/