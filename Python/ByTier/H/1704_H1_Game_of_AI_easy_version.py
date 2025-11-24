# Problem: CF 1704 H1 - Game of AI (easy version)
# https://codeforces.com/contest/1704/problem/H1

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(k^2)
Space Complexity: O(k)

This solution computes the number of distinct pairs (a, b) where:
- a is a sequence of length n where a[i] != i
- b is the final state of bots occupying towers after all rounds of attacks
- The result is calculated over all valid permutations p and sequences a
"""

import sys

input = sys.stdin.readline


k, M = map(int, input().split())

MOD = M


def modmul(x, y, c=0):
    # Modular multiplication with optional addition
    return (x * y + c) % MOD


mod_mul = modmul


def inv(x):
    # Modular inverse using Fermat's little theorem
    return pow(x, MOD - 2, MOD)


MAX = 10**5

# Precompute factorials and inverse factorials
fact = [1]
for i in range(1, MAX):
    fact.append(modmul(i, fact[i - 1]))

invfact = [1] * (MAX)
invfact[MAX - 1] = inv(fact[MAX - 1])
for i in range(MAX - 2, -1, -1):
    invfact[i] = modmul(i + 1, invfact[i + 1])


def comb(x, y):
    # Compute combination C(x, y) = x! / (y! * (x-y)!)
    assert 0 <= y <= x
    return modmul(fact[x], modmul(invfact[y], invfact[x - y]))


def invcomb(x, y):
    # Compute inverse of combination C(x, y)
    return modmul(invfact[x], modmul(fact[y], fact[x - y]))


def invs(x):
    # Compute inverse of x! 
    return modmul(fact[x - 1], invfact[x])


def count(a, b):
    # Count arrangements of a elements of one type and b elements of another type
    if a + b == 0:
        return 1
    return modmul(a, fact[a + b - 1])


n = k

# Precompute powers of (n-1) for efficient lookup
pn1 = [1]
for i in range(5000):
    pn1.append(modmul(pn1[-1], n - 1))

out = 0
# Iterate over all possible values of i from 1 to n-1
for i in range(1, n):

    # Precompute powers of (n-i) for efficient lookup
    pni = [1]
    for _ in range(5000):
        pni.append(modmul(pni[-1], n - i))

    # Iterate over all possible values of j from 0 to i
    for j in range(i + 1):
        if n - i - j < 0:
            continue

        # Compute combinatory components
        stab = comb(n, i)  # Ways to choose i elements from n (for stable part)
        app = modmul(comb(i, j), comb(n - i, n - i - j))  # Ways to arrange 
        order = count(j, n - i - j)  # Ways to arrange remaining elements
        sao = modmul(modmul(stab, app), order)  # Combined arrangement count

        # Compute power terms
        u1 = pni[i - j]
        u2 = pn1[j]
        u = modmul(u1, u2)  # Combined power term

        out += modmul(sao, u)

print(out % M)


# https://github.com/VaHiX/CodeForces/