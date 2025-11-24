# Problem: CF 2072 G - I've Been Flipping Numbers for 300 Years and Calculated the Sum
# https://codeforces.com/contest/2072/problem/G

# ====================================================================
# Problem: G. I've Been Flipping Numbers for 300 Years and Calculated the Sum
# Task: Calculate the sum of rev(n, p) for all p from 2 to k, modulo 10^9 + 7.
# Algorithm:
#   - Split computation into two parts:
#     1. For small bases (p < B), process ranges of n/p values with arithmetic formulae.
#     2. For large bases (p >= B), compute rev(n, p) directly using base conversion.
# Time Complexity: O(B * log n + sqrt(k) * log n), where B = 550
# Space Complexity: O(1)
# ====================================================================

M = 10**9 + 7
for _ in range(int(input())):
    n, k = map(int, input().split())
    a = 0
    B = 550
    
    # Part 1: Process small bases using mathematical shortcuts
    for i in range(1, B):
        # Determine the range of p values to consider by grouping similar n/p values
        l = max(n // (i + 1) + 1, B) - 1
        r = min(n // i, k)
        if r >= l:
            # Compute sum of arithmetic sequences for s1 and s2
            s1 = r * (r + 1) // 2 - l * (l + 1) // 2
            s2 = r * (r + 1) * (2 * r + 1) // 6 - l * (l + 1) * (2 * l + 1) // 6
            a += n * s1 - i * s2 + i * (r - l)
    
    # Part 2: Direct computation for larger bases up to min(B, k+1, n+1)
    for p in range(2, min(B, k + 1, n + 1)):
        x, m = 0, n
        while m:
            x = p * x + m % p  # Reverse the digits in base p
            m //= p
        a += x
    
    # Part 3: Handle bases greater than n
    if k > n:
        a += n * (k - n)
    
    print(a % M)


# https://github.com/VaHiX/codeForces/