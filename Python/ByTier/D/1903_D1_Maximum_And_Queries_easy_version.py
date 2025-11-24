# Problem: CF 1903 D1 - Maximum And Queries (easy version)
# https://codeforces.com/contest/1903/problem/D1

"""
Maximum And Queries (easy version)

Algorithm:
- For each bit position (from highest to lowest), we try to set that bit in the final AND result.
- To do this, we calculate how many operations are needed to make all elements at least as large as the current bit value.
- If we have enough operations, we include this bit in the answer and update the array elements accordingly.
- This greedy approach processes bits from most significant to least significant.

Time Complexity: O(61 * n) per query = O(n) since 61 is a constant
Space Complexity: O(n) for storing the array and powers of 2
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n, q = map(int, input().split())
a = list(map(int, input().split()))
pow2 = [1]
for _ in range(61):
    pow2.append(2 * pow2[-1])
pow2.reverse()
ans = []
for _ in range(q):
    k = int(input())
    x = list(a)
    ans0 = 0
    for i in pow2:
        c = 0
        for j in x:
            if not i & j:  # If the bit at position i is 0 in j
                c += i - j  # Number of operations needed to set this bit
            if c > k:
                break
        if c <= k:
            ans0 ^= i  # Include this bit in the answer
            k -= c     # Reduce the remaining operations
            for j in range(n):
                if x[j] < i:
                    x[j] = 0
                else:
                    x[j] ^= i  # Toggle this bit
        else:
            for j in range(n):
                if x[j] & i:
                    x[j] ^= i  # Toggle this bit back
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/