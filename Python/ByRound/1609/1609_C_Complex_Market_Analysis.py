# Problem: CF 1609 C - Complex Market Analysis
# https://codeforces.com/contest/1609/problem/C

"""
Complex Market Analysis

Algorithm:
- Precompute all primes up to 10^6 using Sieve of Eratosthenes
- For each element in the array that is a prime number:
  - Count how many consecutive 1's exist to the right (c)
  - Count how many consecutive 1's exist to the left (d)
  - Add to answer: c + d * (c + 1)
- The logic uses the fact that a product of numbers is prime if and only if 
  one number is prime and all others are 1.

Time Complexity: O(n log log n + n) where n is the maximum possible value
Space Complexity: O(n) for the prime array and input array
"""

n = 10**6
prime = [True for i in range(n + 1)]
prime[1] = False
p = 2
while p * p <= n:
    if prime[p]:
        for i in range(p * p, n + 1, p):
            prime[i] = False
    p += 1

for _ in range(int(input())):
    n, b = map(int, input().split())
    li = list(map(int, input().split()))
    ans = 0
    for i in range(n):
        if prime[li[i]]:
            # Count consecutive 1's to the right
            j, c = i + b, 0
            while j < n and li[j] == 1:
                j, c = j + b, c + 1
            # Count consecutive 1's to the left
            d, j = 0, i - b
            while j >= 0 and li[j] == 1:
                j, d = j - b, d + 1
            # Add combinations to result
            ans += c + d * (c + 1)
    print(ans)


# https://github.com/VaHiX/CodeForces/