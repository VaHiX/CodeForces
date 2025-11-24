# Problem: CF 2104 D - Array and GCD
# https://codeforces.com/contest/2104/problem/D

"""
Problem: Array and GCD

This code solves the problem of finding the minimum number of elements to remove from an array to make it "beautiful".
A beautiful array can be transformed into an "ideal" array using operations:
- Pay 1 coin to increase any element by 1
- Gain 1 coin to decrease any element by 1
An ideal array satisfies:
1. All elements are at least 2
2. GCD of every pair of distinct elements is 1

Algorithm:
- Precompute primes up to 6*10^6 using Sieve of Eratosthenes
- For each test case:
    - Sort the input array in descending order
    - Compute prefix sums of primes
    - Greedily remove elements from the end until we can form an ideal array
Time Complexity: O(n log n + M log log M) where M = 6*10^6 (for sieve)
Space Complexity: O(M + n)
"""

p = [1] * (6 * 10**6)  # Sieve of Eratosthenes initialization
for i in range(2, int(len(p) ** 0.5) + 1):  # Mark non-primes
    if p[i]:
        for j in range(i**2, len(p), i):  # Mark multiples of i as not prime
            p[j] = 0
primes = [i for i in range(2, 6 * 10**6) if p[i]]  # Collect primes
psum = [primes[0]]  # Prefix sum array for primes
for i in range(1, len(primes)):
    psum.append(primes[i] + psum[i - 1])  # Build prefix sums

for _ in range(int(input())):  # For each test case
    n = int(input())  # Read size of array
    a = list(map(int, input().split()))  # Read array elements
    a.sort(reverse=True)  # Sort in descending order for greedy selection
    k = sum(a)  # Total sum of current elements
    ans = 0  # Number of elements to remove
    while psum[n - ans - 1] > k:  # While we cannot form ideal array with remaining elements
        ans += 1  # Remove one element (greedy removal)
        k -= a.pop()  # Decrease sum by that element
    print(ans)  # Print minimum number of elements to remove


# https://github.com/VaHiX/codeForces/