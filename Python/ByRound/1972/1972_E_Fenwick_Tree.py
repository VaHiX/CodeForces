# Problem: CF 1972 E - Fenwick Tree
# https://codeforces.com/contest/1972/problem/E

"""
Fenwick Tree Inversion Problem
Algorithm: Inverse Fenwick Transform using mathematical properties and bit manipulation
Time Complexity: O(n log^2 n) per test case
Space Complexity: O(n) per test case

This solution reconstructs an array 'a' such that f^k(a) = b, where f is the Fenwick tree transformation.
We use the inverse transformation approach based on the properties of the Fenwick tree.
The key idea is to reverse the transformation process by leveraging the mathematical structure
and bit operations to compute the original array from the transformed result.
"""

from math import factorial as fact
from sys import stdin, stdout

input = stdin.readline
print = lambda s: stdout.write(s + "\n")

M = 998244353

# Precompute inverse factorials for later use
ifac = [1] * 21
ifac[20] = pow(fact(20), -1, M)
for i in range(20, 1, -1):
    ifac[i - 1] = i * ifac[i] % M

for _ in range(int(input())):

    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    # Compute factorials needed for the binomial coefficients
    fac = [1]
    for i in range(k, k - 1 + n.bit_length()):
        fac.append(i * fac[-1] % M)
    for i in range(len(fac)):
        fac[i] *= ifac[i]
        fac[i] %= M

    # Apply transformation for indices 1, 5, 9, ... (i % 4 == 1)
    # This step updates elements based on the relation between current element and previous one
    for i in range(1, n, 4):
        a[i] -= k * a[i - 1]
        a[i] %= M

    # Apply transformation for indices 3, 7, 11, ... (i % 4 == 3)
    # This step uses the binomial coefficients and bit manipulation to reconstruct values
    for i in range(3, n, 4):
        for j in range(1, 1 << ((i ^ (i + 1)).bit_length() - 1)):
            a[i] -= fac[j.bit_count()] * a[i - j] % M
        a[i] %= M

    print(" ".join(map(str, a)))


# https://github.com/VaHiX/CodeForces/