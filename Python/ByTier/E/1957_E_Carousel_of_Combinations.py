# Problem: CF 1957 E - Carousel of Combinations
# https://codeforces.com/contest/1957/problem/E

"""
Purpose: This code computes the sum of (C(i, j) mod j) for all valid pairs (i, j) where i ranges from 1 to n and j ranges from 1 to i.
The function C(i, j) represents the number of ways to choose and arrange j distinct elements from {1, ..., i} in a circle.

Algorithms:
- Sieve of Eratosthenes to find primes up to max_n
- Use of prefix sum technique for efficient range updates
- Mathematical optimization for calculating the contribution of each i to the final sum

Time Complexity: O(n log log n + n) where n is up to 10^6
Space Complexity: O(n) for storing various arrays and precomputation

Key Techniques:
- Modular arithmetic for large numbers
- Efficient prefix sum over ranges using difference array
- Mathematical insights for reducing computational complexity
"""

import math

mod = 10**9 + 7
max_n = 1000000
size = max_n + 1


def main():
    # Sieve of Eratosthenes to find primes up to max_n
    sieve = [True] * (size)
    sieve[0] = False
    sieve[1] = False
    sqrt_n = int(math.isqrt(max_n))
    for i in range(2, sqrt_n + 1):
        if sieve[i]:
            for j in range(i * i, size, i):
                sieve[j] = False
    primes = []
    for i in range(3, size):
        if sieve[i]:
            primes.append(i)
    
    # Difference array technique to calculate contribution of each i
    D = [0] * (size + 2)
    for j in primes:
        q_max = max_n // j
        for q in range(1, q_max + 1):
            i0 = j * q
            if i0 > max_n:
                break
            i1 = i0 + j - 1
            if i1 > max_n:
                i1 = max_n
            r = q % j
            if r == 0:
                v = 0
            else:
                v = j - r
            D[i0] += v
            if i1 + 1 <= max_n:
                D[i1 + 1] -= v

    # Prefix sum of difference array to get actual values
    T_prime = [0] * size
    current = 0
    for i in range(1, size):
        current += D[i]
        T_prime[i] = current

    # Apply additional mathematical adjustments to T_prime to get T
    T = [0] * size
    for i in range(1, size):
        add = 0
        if i >= 2:
            if i % 4 == 2 or i % 4 == 3:
                add += 1
        if i >= 4:
            if i % 8 in (4, 5, 6, 7):
                add += 2
        T[i] = T_prime[i] + add

    # Prefix sum of T gives the final result array P_arr
    P_arr = [0] * size
    for i in range(1, size):
        P_arr[i] = (P_arr[i - 1] + T[i]) % mod

    # Process input test cases
    t = int(input().strip())
    res = []
    for _ in range(t):
        n = int(input().strip())
        res.append(str(P_arr[n]))
    print("\n".join(res))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/