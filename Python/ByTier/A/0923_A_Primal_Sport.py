# Problem: CF 923 A - Primal Sport
# https://codeforces.com/contest/923/problem/A

"""
Algorithm: Primal Sport
Approach:
- We are given X2, the state after two moves.
- We need to determine the minimum possible X0 that could lead to X2 after two moves.
- Each move involves selecting a prime p < current number and finding the smallest multiple of p >= current number.
- The key insight is to reverse-engineer the process:
  - For a given X2, find all possible X1 such that a valid prime operation from X1 to X2 is possible.
  - Then for each such X1, find possible X0 values by trying all primes < X1.

Time Complexity: O(N log log N + N) where N = 10^6
Space Complexity: O(N) for sieve and storing primes

"""

def sieve(MAX):
    sieve = [1] * MAX
    for i in range(2, MAX):
        if sieve[i] != 1:
            continue
        # Mark all multiples of i with i (smallest prime factor)
        for j in range(2 * i, MAX, i):
            sieve[j] = i
    return sieve


def main():
    MAX = int(1e6)
    N = MAX + 1
    # Generate smallest prime factor for all numbers up to 10^6
    primes = sieve(N)

    x2 = int(input())

    # Get the smallest prime factor of x2
    max_p = primes[x2]

    result = float("inf")
    # Iterate from x2 - max_p + 1 to x2 (possible values for x1)
    for x1 in range(x2 - max_p + 1, x2 + 1):
        # If x1 is prime, then x1 itself is the x0
        if primes[x1] == x1:
            result = min(result, x1)
            continue
        # Otherwise get the smallest prime factor of x1 (denoted as max_p)
        max_p = primes[x1]
        # x0 can be at most x1 - max_p + 1
        t = x1 - max_p + 1
        result = min(result, t)

    print(result)


main()


# https://github.com/VaHiX/CodeForces/