# Problem: CF 2084 E - Blossom
# https://codeforces.com/contest/2084/problem/E

"""
Problem: Blossom
Task: Find the sum of values of all valid permutations formed from a given array with missing elements (-1) filled in,
where value of a permutation is the sum of MEX (minimum excluded) over all subsegments.

Algorithms/Techniques:
- Preprocessing factorials and inverse factorials for combinatorics
- Generating function approach with inclusion-exclusion or direct counting
- Dynamic updating of counts while shifting pointers l, r
- Modular arithmetic with fast exponentiation for modular inverse

Time Complexity: O(n^3) per test case due to nested loops and combinatorial functions.
Space Complexity: O(n^2) for storing factorials and auxiliary arrays.
"""

MOD = 10**9 + 7


def modmul(x, y, c=0):
    return (x * y + c) % MOD


mod_mul = modmul


def inv(x):
    return pow(x, MOD - 2, MOD)


MAX = 10**4 * 3
fact = [1]
for i in range(1, MAX):
    fact.append(modmul(i, fact[i - 1]))
invfact = [1] * (MAX)
invfact[MAX - 1] = inv(fact[MAX - 1])
for i in range(MAX - 2, -1, -1):
    invfact[i] = modmul(i + 1, invfact[i + 1])


def comb(x, y):
    if 0 <= y <= x:
        return modmul(fact[x], modmul(invfact[y], invfact[x - y]))
    return 0


def perm(x, y):
    return modmul(fact[x], invfact[x - y])


def invcomb(x, y):
    return modmul(invfact[x], modmul(fact[y], fact[x - y]))


def invs(x):
    return modmul(fact[x - 1], invfact[x])


import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    z = a.count(-1)  # Count of missing (wildcard) elements
    ct = [0] * (n + 1)
    for i in range(n):
        curr = 0
        for j in range(i, n):
            if a[j] == -1:
                curr += 1
            ct[curr] += 1
    l = n + 1  # Left pointer of current active window
    r = -1     # Right pointer of current active window
    out = 0    # Final result accumulator
    miss = 0   # Number of missing elements seen so far at current position
    ctneg = 0  # Count of negative (-1) elements in current window (for tracking)
    for i in range(n):
        if i in a:  # If element 'i' exists already in the array
            if r == -1:
                # Initialize window if not set yet
                l = r = a.index(i)
                ct = [0] * (n + 1)
                xx = 0
                for j in range(l, -1, -1):  # Update prefix to include current element
                    if a[j] == -1:
                        xx += 1
                    curr = xx
                    for k in range(r, n):
                        if a[k] == -1:
                            curr += 1
                        ct[curr] += 1
            else:
                jj = a.index(i)
                # Adjust left pointer
                while l > jj:
                    if a[l] == -1:
                        ctneg += 1
                    # Update contribution of -1's in the subsegments
                    curr = ctneg
                    for k in range(r, n):
                        if a[k] == -1:
                            curr += 1
                        ct[curr] -= 1
                    l -= 1
                # Adjust right pointer
                while r < jj:
                    if a[r] == -1:
                        ctneg += 1
                    curr = ctneg
                    for k in range(l, -1, -1):
                        if a[k] == -1:
                            curr += 1
                        ct[curr] -= 1
                    r += 1
        else:
            miss += 1  # Increase number of missing elements
        for k in range(miss, z + 1):  # Process valid combinations of missing entries
            ex = modmul(modmul(fact[k], invfact[k - miss]), fact[z - miss])
            out += modmul(ct[k], ex)  # Accumulate result with combinatorial weights
        out %= MOD  # Keep modulo
    print(out)


# https://github.com/VaHiX/codeForces/