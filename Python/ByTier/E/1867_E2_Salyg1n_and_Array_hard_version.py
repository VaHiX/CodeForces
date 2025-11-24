# Problem: CF 1867 E2 - Salyg1n and Array (hard version)
# https://codeforces.com/contest/1867/problem/E2

"""
Interactive problem: Salyg1n and Array (hard version)

Algorithm:
- The goal is to compute XOR of all elements in the array using at most 57 queries.
- The key insight is to use the fact that we can query XOR of subarrays of size k,
  and each query reverses the corresponding subarray.
- We exploit the properties of XOR and the reversal operation to reconstruct
  the full XOR efficiently.

Time Complexity: O(n) per test case, as we perform at most O(n/k) queries.
Space Complexity: O(1), only using a constant amount of extra space.

Approach:
1. If n is divisible by k, we make queries at positions 1, k+1, 2k+1, ..., and XOR the results.
2. If n is not divisible by k:
   - Make queries at specific positions:
     - Position 1 (to get a[0] ^ a[1] ^ ... ^ a[k-1])
     - Position t//2 + 1 (to get a[t//2] ^ a[t//2 + 1] ^ ... ^ a[t//2 + k-1])
     - Position t + 1 (to get a[t] ^ a[t+1] ^ ... ^ a[t+k-1])
   - Then process remaining segments similarly.
   - This avoids double-counting or missing elements due to partial overlaps.

This method reduces the number of required queries and ensures efficient reconstruction.
"""

import sys

input = sys.stdin.readline
R = lambda: list(map(int, input().split()))


def qa(i):
    # Query the XOR of subarray starting at index i of length k
    print("?", i)
    sys.stdout.flush()
    return int(input())


for _ in range(int(input())):
    n, k = R()
    res = 0
    if n % k == 0:
        # If n is divisible by k, we process all full chunks
        for i in range(1, n - k + 2, k):
            res ^= qa(i)
        print("!", res)
        sys.stdout.flush()
    else:
        # If n is not divisible by k, handle partial segments
        t = n % k  # remainder of division
        # Query specific positions to account for the partial segment
        res ^= qa(1)            # XOR of first k elements
        res ^= qa(t // 2 + 1)   # XOR of middle k elements (centered around remainder)
        res ^= qa(t + 1)        # XOR of last k elements
        # Process remaining full segments
        for i in range(1 + t + k, n - k + 2, k):
            res ^= qa(i)
        print("!", res)
        sys.stdout.flush()


# https://github.com/VaHiX/CodeForces/