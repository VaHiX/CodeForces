# Problem: CF 1043 F - Make It One
# https://codeforces.com/contest/1043/problem/F

"""
F. Make It One

Purpose:
This code solves the problem of finding the minimum number of elements from a given sequence 
such that their greatest common divisor (GCD) equals 1. If no such subset exists, it returns -1.

Algorithms/Techniques:
- Sieve-like preprocessing to count occurrences of each number.
- Mobius inversion principle applied to efficiently compute contributions of divisors.
- Combination counting with modular arithmetic.
Time Complexity: O(R log R + n), where R = 3 * 10^5 and n is the input size.
Space Complexity: O(R), for storing arrays of size up to 300,000.

Input:
- First line contains an integer n (number of elements).
- Second line contains n integers (elements of the sequence).

Output:
- Minimum number of elements in a subset with GCD = 1, or -1 if impossible.
"""

from math import gcd

R = 3 * 10**5

def C(n, k):
    # Computes combination C(n, k) = n! / (k! * (n-k)!)
    if n < k:
        return 0
    y = 1
    for i in range(n - k + 1, n + 1):
        y *= i
    for i in range(2, k + 1):
        y //= i
    return y

# Count how many times each number appears in input
n = int(input())
c = [0] * (R + 1)
for e in input().split():
    c[int(e)] = 1

# d[i] will store the count of numbers divisible by i
d = [0] * (R + 1)
for i in range(1, R + 1):
    j = i
    while j <= R:
        d[i] += c[j]
        j += i

# If GCD of all given numbers > 1, then no subset can have GCD 1
if gcd(*(i for i in range(1, R + 1) if c[i])) > 1:
    print(-1)
else:
    k = 0
    while 1:
        k += 1
        # F[i] is the sum over all subsets of size k using numbers divisible by i
        F = [C(d[i], k) for i in range(R + 1)]
        # Apply inclusion-exclusion (Mobius inversion) 
        for i in range(R, 0, -1):
            j = 2 * i
            while j <= R:
                F[i] -= F[j]
                j += i
        # If there exists a subset of size k with GCD=1, we found answer
        if F[1]:
            print(k)
            break


# https://github.com/VaHiX/codeForces/