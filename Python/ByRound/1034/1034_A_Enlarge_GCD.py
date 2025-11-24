# Problem: CF 1034 A - Enlarge GCD
# https://codeforces.com/contest/1034/problem/A

"""
Problem: Enlarge GCD
Task: Given a list of integers, find the minimum number of elements to remove such that the GCD of the remaining elements is greater than the initial GCD.

Algorithms/Techniques:
- Sieve of Eratosthenes for finding smallest prime factor (SPF) for numbers up to 1.5 * 10^7
- Prime factorization using SPF
- GCD computation using math.gcd

Time Complexity: O(n log n + max(a) log log(max(a)))
Space Complexity: O(max(a))

The solution works by:
1. Finding the initial GCD of all numbers
2. Dividing each number by the GCD to normalize them
3. For each normalized number, factorizing it and tracking how many times each prime appears
4. The answer is n minus the maximum count of any prime factor across all numbers
"""

import math


def sieve():
    n = 15000002
    spf = [i for i in range(n + 1)]  # Smallest prime factor array initialization
    for i in range(4, n, 2):         # Mark all even numbers with SPF = 2
        spf[i] = 2
    for i in range(3, n):
        if i * i > n:                # Stop if square of i exceeds n
            break
        if spf[i] == i:              # If i is prime
            for j in range(2 * i, n, i):  # Mark multiples of i with SPF = i
                if spf[j] == j:
                    spf[j] = i
    return spf


spf = sieve()  # Precompute smallest prime factors

n = int(input())
a = list(map(int, input().split()))

# Compute initial GCD of all numbers
g = math.gcd(a[0], a[1])
for i in range(2, n):
    g = math.gcd(g, a[i])

flag = False  # Check if any number is greater than 1 after division by GCD
for i in range(n):
    a[i] = a[i] // g  # Normalize numbers by dividing by initial GCD
    if a[i] > 1:
        flag = True

if not flag:  # If all normalized numbers are 1, no improvement possible
    print(-1)
else:
    ans = -1
    f = [0] * (max(a) + 1)  # Frequency count of each prime factor
    for i in range(len(a)):
        num = a[i]
        while num > 1:
            p = spf[num]       # Get smallest prime factor of current number
            f[p] += 1          # Increment frequency count of this prime
            num = num // p     # Divide by smallest prime factor
            ans = max(ans, f[p])  # Update maximum frequency seen so far
            while num % p == 0:  # Remove all occurrences of the same prime factor
                num = num // p
    print(n - ans)  # Minimum elements to remove is total minus max frequency


# https://github.com/VaHiX/codeForces/