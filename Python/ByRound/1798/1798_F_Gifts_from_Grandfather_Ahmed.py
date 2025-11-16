# Problem: CF 1798 F - Gifts from Grandfather Ahmed
# https://codeforces.com/contest/1798/problem/F

"""
Algorithm: Gift Distribution with Modular Arithmetic
Purpose: To distribute n boxes of gifts among k classes such that each class receives exactly s_i boxes, 
         and the total gifts in each class is divisible by s_i. We need to determine how many gifts to add 
         in the missing box (1 to 10^6) and provide a valid distribution.

Approach:
- Sort classes by size.
- For each class (except last), determine a subset of boxes whose sum is divisible by class size using 
  the EGZ (Erdos–Ginzburg–Ziv) theorem based algorithm.
- For the last class, compute the required number of gifts (x) such that x + sum of remaining boxes is divisible by s_k.
- Output x + s_k as the size of the missing box, and print the distribution.

Time Complexity: O(n^2 * k) due to the recursive EGZ implementation and multiple subset selections
Space Complexity: O(n * k) for storing box sizes and distributions
"""

def Find_t(p, T, d, u, v):
    # Helper function to find a specific value using binary search
    l, h = u * pow(d, -1, p) % p, p + v * pow(d, -1, p) % p
    while l + 1 != h:
        m = (l + h) // 2
        if T[m * d % p]:
            l = m
        else:
            h = m
    return h * d % p


def EGZ_prime(p, a):
    # Algorithm for prime number case using Erdos-Ginzburg-Ziv theorem
    k = sorted(range(2 * p - 1), key=lambda x: a[x] % p)
    L = [False] * (2 * p - 1)
    for i in range(p - 1):
        if a[k[1 + i]] % p == a[k[p + i]] % p:
            for i in range(1 + i, 1 + p + i):
                L[k[i]] = True
            return L

    s = sum((a[k[i]] for i in range(p))) % p
    T, P = [False] * p, [None] * p
    T[s] = True
    for i in range(1, p):
        if T[0]:
            break
        t = Find_t(p, T, (a[k[p + i - 1]] - a[k[i]]) % p, s, 0)
        T[t] = True
        P[t] = i

    c = 0
    for i in range(p):
        L[k[i]] = True
    while s != c:
        L[k[p + P[c] - 1]], L[k[P[c]]] = True, False
        c = (c - (a[k[p + P[c] - 1]] - a[k[P[c]]])) % p

    return L


def EGZ_composite(p, q, a):
    # Algorithm for composite number case
    S, T = list(range(p - 1)), [None] * (2 * q - 1)
    for i in range(2 * q - 1):
        S.extend(range((i + 1) * p - 1, (i + 2) * p - 1))
        ret = EGZ(p, [a[s] for s in S])
        T[i] = [S[j] for j in range(2 * p - 1) if ret[j]]
        S = [S[j] for j in range(2 * p - 1) if not ret[j]]
    L = [False] * (2 * p * q - 1)
    ret = EGZ(q, [sum(a[t] for t in T[i]) // p for i in range(2 * q - 1)])

    for i in range(2 * q - 1):
        if ret[i]:
            for j in T[i]:
                L[j] = True
    return L


def EGZ(n, a):
    # Main entry point for EGZ algorithm
    if n == 1:
        return [True]
    for i in range(2, n):
        if n % i == 0:
            return EGZ_composite(i, n // i, a)
    return EGZ_prime(n, a)


# Read input
n, k = map(int, input().split())
a = list(map(int, input().split()))
s = list(map(int, input().split()))

# Pair sizes with class indices and sort by size
l = [(s[i], i) for i in range(k)]
l.sort()

# Initialize result arrays
ans = [0] * k
l1 = a[::]

# Process all but the last class
for i in l[:-1]:
    N = i[0]
    ret = EGZ(i[0], l1)
    ans[i[1]] = [l1[j] for j in range(2 * N - 1) if ret[j]]
    x = len(l1)
    l2 = []
    for j in range(x):
        if j >= len(ret) or ret[j] == False:
            l2.append(l1[j])
    l1 = l2[::]

# Compute missing gift count for the last class
x = (-sum(l1)) % l[-1][0]
print(x + l[-1][0])
ans[l[-1][1]] = l1 + [x + l[-1][0]]

# Output the distribution
for i in ans:
    print(*i)


# https://github.com/VaHiX/CodeForces/