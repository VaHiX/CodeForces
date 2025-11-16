# Problem: CF 2029 E - Common Generator
# https://codeforces.com/contest/2029/problem/E

"""
Algorithm/Technique:
- Sieve of Eratosthenes to precompute prime factors for numbers up to 4*10^5
- For each test case, determine if there exists a common generator x >= 2 such that x can generate all elements in the input array.
- The key insight is that if a number x is a generator of y, then y must be expressible as x + sum of divisors of x (possibly repeated).
- If we have multiple primes in the array, then a generator x must be able to generate each of these primes which implies x must be 2 (the smallest possible) or no generator exists.
- When only one prime is present, we try to verify whether that prime can be the generator.
- Time complexity: O(n * sqrt(max_a)) where max_a <= 4*10^5
- Space complexity: O(max_a) for sieve and auxiliary storage
"""

def sieve(n):
    isprime = [1] * (n + 1)
    isprime[0] = 0
    isprime[1] = 0
    factor = [i for i in range(n + 1)]
    for i in range(2, int(n**0.5) + 1):
        if isprime[i]:
            for j in range(i * i, n + 1, i):
                isprime[j] = 0
                factor[j] = i
    return isprime, factor


isprime, factor = sieve(4 * 10**5 + 1)


def solve():
    int(input())
    arr = list(map(int, input().split()))
    primes = []  # Store primes from the array
    for a in arr:
        if isprime[a]:
            primes.append(a)
    if not primes:
        return 2  # If no primes, return 2 as it's a valid generator
    if len(primes) >= 2:
        return -1  # If more than one prime, no common generator exists
    p = primes[0]  # Only one prime in the array
    if p == 2:
        return 2
    for a in arr:
        if a < p or p < a < p + p:  # Check if a is in valid range relative to p
            return -1
        if a % p == 0:  # If divisible by p, skip
            continue
        b = a
        while b > 1:
            q = factor[b]  # Get smallest prime factor
            b //= q  # Reduce b
            if a - q >= p + p:  # Break if remaining value exceeds threshold
                break
        else:
            return -1  # If we exit normally, it's a contradiction
    return p


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    print(solve())


# https://github.com/VaHiX/CodeForces/