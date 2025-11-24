# Problem: CF 2053 D - Refined Product Optimality
# https://codeforces.com/contest/2053/problem/D

# D. Refined Product Optimality
# Algorithms/Techniques: Greedy with sorting and binary search (bisect_right), modular arithmetic, prefix computation
# Time Complexity: O(n * log n + q * log n)
# Space Complexity: O(n)

import io
import os
import sys
from bisect import bisect_right
from functools import reduce

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
M = 998244353

for _ in range(int(input())):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    
    # Sort arrays to allow greedy matching
    c = sorted(a)
    d = sorted(b)
    
    # Initial answer is product of min elements after optimal pairing (greedy approach)
    ans = reduce(lambda x, y: (x * y) % M, [min(c[i], d[i]) for i in range(n)], 1)
    sys.stdout.write(str(ans) + " ")
    
    # Process queries
    while q:
        o, x = map(int, input().split())
        x -= 1  # Convert to 0-based index
        
        if o == 1:
            # Update array a and corresponding sorted array c
            i = bisect_right(c, a[x]) - 1  # Find insertion point in sorted c
            if c[i] < d[i]:
                # Adjust answer: divide by old value, multiply by new value
                ans = (ans * pow(c[i], -1, M) * (c[i] + 1)) % M
            c[i] += 1
            a[x] += 1
        else:
            # Update array b and corresponding sorted array d
            i = bisect_right(d, b[x]) - 1  # Find insertion point in sorted d
            if d[i] < c[i]:
                # Adjust answer: divide by old value, multiply by new value
                ans = (ans * pow(d[i], -1, M) * (d[i] + 1)) % M
            d[i] += 1
            b[x] += 1
            
        sys.stdout.write(str(ans) + " ")
        q -= 1
        
    sys.stdout.write("\n")


# https://github.com/VaHiX/codeForces/