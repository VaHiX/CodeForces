# Problem: CF 2123 F - Minimize Fixed Points
# https://codeforces.com/contest/2123/problem/F

"""
F. Minimize Fixed Points
Algorithm: Sieve of Eratosthenes + Permutation Construction

Purpose:
This code finds a "good" permutation of length n (where gcd(p[i], i) > 1 for all 2 <= i <= n)
with the minimum number of fixed points. The approach uses a precomputed sieve to determine
the smallest prime factor of each number, then constructs the permutation using a specific
swapping strategy that minimizes fixed points.

Time Complexity: O(n log log n) for sieve + O(n) for permutation construction = O(n log log n)
Space Complexity: O(n) for storing the sieve and intermediate arrays

The algorithm leverages the fact that for a permutation to be good, each element at position i
must satisfy gcd(p[i], i) > 1. This implies p[i] and i share a common prime factor.
We use smallest prime factor (SPF) decomposition to efficiently group numbers that share factors.

"""

is_prime = [k for k in range(200001)]  # Initialize array with indices


def prime():
    is_prime[0] = is_prime[1] = 1  # Mark 0 and 1 as not prime
    for i in range(2, 200001):
        if is_prime[i] == i:  # If i is prime
            for j in range(i, 200001, i):  # Mark multiples of i with SPF = i
                is_prime[j] = i


prime()  # Precompute smallest prime factors

t = int(input())
for l in range(t):
    n = int(input())
    ans = [0] * (n + 1)
    jump = [k for k in range(n + 1)]  # Jump array to track mappings
    ans[1] = 1  # Base case: p[1] = 1
    for i in range(n + 1):
        jump[i] = jump[is_prime[i]]  # Update jump based on smallest prime factor
        jump[is_prime[i]] = i       # Reverse mapping to track groupings
    for i in range(n + 1):
        ans[jump[i]] = i            # Final permutation assignment
    for i in range(1, n + 1):
        print(ans[i], end=" ")      # Output the result
    print()  # New line after each test case


# https://github.com/VaHiX/CodeForces/