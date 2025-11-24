# Problem: CF 2116 B - Gellyfish and Baby's Breath
# https://codeforces.com/contest/2116/problem/B

# B. Gellyfish and Baby's Breath
# Purpose: Compute an array r where each element ri is the maximum of 2^pj + 2^qi-j over all valid j in [0, i].
# Algorithm: Use two pointers to track maximum values from both arrays p and q for efficient computation.
# Time Complexity: O(n) per test case, due to single pass through array with precomputed powers of 2.
# Space Complexity: O(n) for storing the precomputed powers of 2 and output array.

import sys

input = sys.stdin.readline
mod = 998244353
p = [1]  # Precompute powers of 2 modulo 998244353
for j in range(10**5):
    p.append((p[-1] << 1) % mod)  # Left shift to multiply by 2, then take mod

for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))  # First permutation
    b = list(map(int, input().split()))  # Second permutation
    
    m1, m2 = (-1, -1), (-1, -1)  # Track max value and index for both arrays
    out = []
    
    for j in range(n):
        m1 = max(m1, (a[j], j))  # Update max value and index for array a
        m2 = max(m2, (b[j], j))  # Update max value and index for array b
        
        if m1[0] > m2[0]:
            # If current max in a is greater than in b, compute based on that
            out.append((p[m1[0]] + p[b[j - m1[1]]]) % mod)
        elif m2[0] > m1[0]:
            # If current max in b is greater than in a, compute based on that
            out.append((p[m2[0]] + p[a[j - m2[1]]]) % mod)
        else:
            # In case of equality, choose the maximum between two possible combinations
            out.append((p[m1[0]] + p[max(a[j - m2[1]], b[j - m1[1]])]) % mod)
    
    print(*out)


# https://github.com/VaHiX/codeForces/