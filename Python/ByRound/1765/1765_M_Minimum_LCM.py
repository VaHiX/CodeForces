# Problem: CF 1765 M - Minimum LCM
# https://codeforces.com/contest/1765/problem/M

"""
Algorithm: Minimum LCM Pair Finder
Techniques: Prime factorization, mathematical optimization

Time Complexity: O(sqrt(n)) per test case, due to prime factorization
Space Complexity: O(1), only using constant extra space

The approach is based on the fact that to minimize the LCM of two numbers a and b such that a + b = n,
we want a and b to be as close to each other as possible. However, we also want their LCM to be small.
If n is prime, then the only way to write n = a + b with a,b > 0 is to use 1 and n-1.
If n is not prime, we can find its smallest prime factor p, and set a = n/p and b = n - n/p = n*(p-1)/p.
This makes the LCM small because a and b share a large common factor.
"""

def prime(n):
    # Find the smallest prime factor of n
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return n // i  # Return the largest factor (n/p)
    return 1  # If n is prime, return 1


for _ in range(int(input())):  # Process each test case
    n = int(input())  # Read the value of n
    p = prime(n)  # Find the smallest prime factor of n
    print(p, n - p)  # Output a = p, b = n - p


# https://github.com/VaHiX/CodeForces/