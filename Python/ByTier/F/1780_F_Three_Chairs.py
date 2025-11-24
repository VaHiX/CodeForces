# Problem: CF 1780 F - Three Chairs
# https://codeforces.com/contest/1780/problem/F

"""
Algorithm: Inclusion-Exclusion Principle with Prime Factorization
Purpose: Count the number of ways to choose 3 friends such that the GCD of the minimum and maximum heights is 1.
Time Complexity: O(n * log(max(a)) + max(a) * log(max(a)))
Space Complexity: O(max(a))

Approach:
- Precompute prime factors for all numbers up to 3*10^5 using sieve.
- For each element in the sorted array, use inclusion-exclusion principle to count invalid triplets.
- Use bitmasks to iterate over all subsets of prime factors.
- For each subset, calculate contribution to the answer using inclusion-exclusion.
- Subtract invalid triplets from total possible triplets to get valid ones.
"""

from sys import stdin

input = stdin.readline

inp = lambda: list(map(int, input().split()))

size = 3 * (10**5) + 1
pf = [[] for i in range(size)]
for i in range(2, size):
    if len(pf[i]):
        continue

    for j in range(i, size, i):
        pf[j].append(i)


def answer():

    ans = 0
    val, count = [0 for i in range(size)], [0 for i in range(size)]
    for ind in range(n):

        # Iterate through all non-empty subsets of prime factors of a[ind]
        for mask in range(1, 1 << len(pf[a[ind]])):

            prod, c = 1, 0
            for i in range(len(pf[a[ind]])):
                if mask >> i & 1 == 0:
                    continue
                prod *= pf[a[ind]][i]
                c += 1

            # Apply inclusion-exclusion: odd number of primes -> add, even -> subtract
            if c & 1:
                ans += count[prod] * ind - val[prod]
            else:
                ans -= count[prod] * ind - val[prod]

        # Update the prefix sums for current element's prime factors
        for mask in range(1, 1 << len(pf[a[ind]])):

            prod = 1
            for i in range(len(pf[a[ind]])):
                if mask >> i & 1 == 0:
                    continue
                prod *= pf[a[ind]][i]

            val[prod] += ind + 1
            count[prod] += 1

    # Total number of triplets minus invalid ones
    good = (n * (n - 1) * (n - 2)) // 6
    good -= ans
    return good


for T in range(1):

    n = int(input())
    a = sorted(inp())

    print(answer())


# https://github.com/VaHiX/CodeForces/