# Problem: CF 2091 E - Interesting Ratio
# https://codeforces.com/contest/2091/problem/E

"""
E. Interesting Ratio

Purpose:
This code calculates the number of "interesting ratios" F(a, b) = lcm(a, b) / gcd(a, b)
such that 1 ≤ a < b ≤ n and F(a, b) is a prime number.

Algorithm:
- Uses Sieve of Eratosthenes to precompute primes up to n.
- For each prime p, count how many valid pairs (a, b) exist where a < b, gcd(a,b) = a,
  and lcm(a,b)/gcd(a,b) = b/a = p (i.e., b = p * a).
- This reduces to counting pairs (a, p*a) where p*a ≤ n for all primes p <= n.

Time Complexity: O(n log log n + n)
Space Complexity: O(n)

Techniques:
- Sieve of Eratosthenes
- Mathematical derivation using GCD/LCM properties
"""

t = int(input())
for i in range(t):
    n = int(input())
    l = [1 for _ in range(n + 1)]
    l[0] = 0
    l[1] = 1
    ans = 0
    # Sieve of Eratosthenes to find primes
    for x in range(2, int(n**0.5 + 1)):
        if l[x]:
            for y in range(x**2, n + 1, x):
                l[y] = 0
    # For each prime p, count pairs (a, p*a) such that p*a <= n
    for w in range(2, n + 1):
        if l[w]:  # If w is a prime
            ans += n // w  # Add number of valid a values such that a * w <= n
    print(ans)


# https://github.com/VaHiX/codeForces/