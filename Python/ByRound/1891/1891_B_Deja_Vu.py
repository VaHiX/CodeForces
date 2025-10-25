# Problem: CF 1891 B - Deja Vu
# https://codeforces.com/contest/1891/problem/B

"""
Algorithm: Deja Vu
Techniques: Bit manipulation, prefix processing

Time Complexity: O(n + q) per test case
Space Complexity: O(1) extra space (not counting input/output)

This solution processes a series of modifications on an array where each modification
adds a power of 2 to elements divisible by a certain power of 2. The key insight is
to precompute which bits need to be added and apply them efficiently using bit operations.
"""

import sys


def dejaVu(n, q, A, X):
    k, a = 31, 0  # k tracks minimum x_i, a accumulates bitmask of operations
    for i in X:
        if i < k:
            k = i
            a += 1 << (i - 1)  # Precompute the bitmask for additions
    for i in range(n):
        # Efficiently check divisibility and add appropriate value using bit hacks
        A[i] = str(A[i] + (((A[i] ^ (A[i] - 1)) >> 1) & a))
    A += "\n"
    sys.stdout.write(" ".join(A))


t = int(sys.stdin.readline())
for _ in range(t):
    num1, num2 = list(map(int, sys.stdin.readline().split()))
    lis1 = list(map(int, sys.stdin.readline().split()))
    lis2 = list(map(int, sys.stdin.readline().split()))
    dejaVu(num1, num2, lis1, lis2)


# https://github.com/VaHiX/CodeForces/