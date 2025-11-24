# Problem: CF 1978 E - Computing Machine
# https://codeforces.com/contest/1978/problem/E

"""
Algorithm: 
The problem involves computing the maximum number of 1s in a substring of string 'a' 
after applying specific operations that can increase 1s in 'a' and 'b' using rules:
1. If a[i] = a[i+2] = 0, then b[i+1] can be set to 1.
2. If b[i] = b[i+2] = 1, then a[i+1] can be set to 1.

Approach:
1. Precompute the effect of operations on all possible substrings using precomputed arrays 'aa' and 'bb'.
2. Use prefix sums for efficient range queries.
3. For each query, handle different cases:
   - If the range is large enough, use prefix sums directly.
   - If the range is small, simulate operations on the subarrays.

Time Complexity: O(n + q) per test case where n is the string length and q is number of queries.
Space Complexity: O(n) for storing strings and auxiliary arrays.
"""

import sys

t = int(sys.stdin.readline().strip())
for _ in range(t):
    n = int(sys.stdin.readline().strip())
    a = [0] + list(map(int, sys.stdin.readline().strip())) # 1-indexed
    b = [0] + list(map(int, sys.stdin.readline().strip()))
    aa = a[::] # Copy of a
    bb = b[::] # Copy of b
    
    # Apply operation 1: if a[i] = a[i+2] = 0, then b[i+1] = 1
    for i in range(1, n + 1):
        if i + 2 <= n and a[i] == a[i + 2] == 0:
            bb[i + 1] = 1

    # Apply operation 2: if b[i] = b[i+2] = 1, then a[i+1] = 1
    for i in range(1, n + 1):
        if i + 2 <= n and bb[i] == bb[i + 2] == 1:
            aa[i + 1] = 1

    # Create prefix sum array for fast range sum queries
    p = [0 for i in range(n + 1)]
    for i in range(1, n + 1):
        p[i] = p[i - 1] + aa[i]

    q = int(sys.stdin.readline().strip())
    for z in range(q):
        l, r = map(int, sys.stdin.readline().strip().split())
        
        # If range is large enough, use prefix sums
        if r - l >= 4:
            # Total 1s in the middle parts: p[r-2] - p[l+1]
            # Add the original endpoints if they can contribute to the result
            ans = p[r - 2] - p[l + 1] + a[l] + a[r]
            # Check if l+1 can be increased: if b[l] and b[l+2] are both 1
            x = a[l + 1] | (b[l] and bb[l + 2])
            # Check if r-1 can be increased: if b[r] and b[r-2] are both 1
            y = a[r - 1] | (b[r] and bb[r - 2])
            print(ans + x + y)
        else:
            # For small range, simulate operations on the subarray
            A = [0] * (n + 1)
            B = [0] * (n + 1)
            for i in range(l, r + 1):
                A[i] = a[i]
                B[i] = b[i]
                
            # Apply operation 1 to the subarray
            for i in range(l, r + 1):
                if i + 2 <= r and a[i] == a[i + 2] == 0:
                    B[i + 1] = 1
                    
            # Apply operation 2 to the subarray
            for i in range(l, r + 1):
                if i + 2 <= r and B[i] == B[i + 2] == 1:
                    A[i + 1] = 1
                    
            # Count total 1s in the subarray A[l:r+1]
            print(sum(A[l : r + 1]))


# https://github.com/VaHiX/CodeForces/