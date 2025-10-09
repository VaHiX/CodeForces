# Problem: CF 2089 A - Simple Permutation
# https://codeforces.com/contest/2089/problem/A

"""
Problem: Construct a permutation of length n such that among the ceiling averages c1, c2, ..., cn,
there are at least floor(n/3) - 1 prime numbers.

Algorithm:
- Precompute primes up to 100000 using Sieve of Eratosthenes.
- For each test case:
  - Find a prime number near n/2 (the midpoint).
  - Generate a permutation starting with that prime number, placing elements in a symmetric fashion around it.
- Time Complexity: O(n log log n + n) for sieve and permutation generation
- Space Complexity: O(100001) for the prime array + O(n) for the output permutation
"""

t = int(input())
prime = [1] * 100001
# Sieve of Eratosthenes to precompute primes up to 100000
for i in range(2, 100001):
    if prime[i] == 1:
        for j in range(2 * i, 100001, i):
            prime[j] = 0

for t_ in range(t):
    n = int(input())
    m = (n + 1) // 2  # Calculate the midpoint
    if prime[m] == 1:
        p = m  # If m is prime, use it as the starting point
    else:
        # Find nearest prime to m
        for i in range(1, min(m - 1, n - m) + 1):
            q = m + i  # Check larger values
            r = m - i  # Check smaller values
            if prime[q] == 1:
                p = q
                break
            if prime[r] == 1:
                p = r
                break
    
    perm = [p]  # Start building permutation with the prime number p
    # Fill symmetrically around p
    for i in range(1, min(p - 1, n - p) + 1):
        perm.append(p + i)
        perm.append(p - i)
    
    # Handle remaining elements depending on which side is longer
    if p - 1 < n - p:
        # If left side (smaller than p) is shorter, fill right side with remaining numbers
        for i in range(2 * p, n + 1):
            perm.append(i)
    elif p - 1 > n - p:
        # If left side (smaller than p) is longer, fill left side with remaining numbers
        for i in range(2 * p - n - 1, 0, -1):
            perm.append(i)

    print(" ".join(map(str, perm)))


# https://github.com/VaHiX/codeForces/