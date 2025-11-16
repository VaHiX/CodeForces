# Problem: CF 1796 F - Strange Triples
# https://codeforces.com/contest/1796/problem/F

"""
Algorithm: Strange Triples Counting
Approach:
    We are to find the number of triples (a, b, n) such that:
    concatenate(a, n) / concatenate(n, b) = a / b
    where concatenate(x, y) is the number formed by placing x and y together.

    The key mathematical transformation:
    an / nb = a / b  => (a * 10^len(n) + n) / (n * 10^len(b) + b) = a / b
    Cross Multiply and simplify:
    b(a * 10^len(n) + n) = a(n * 10^len(b) + b)
    b * a * 10^len(n) + b * n = a * n * 10^len(b) + a * b
    b * a * 10^len(n) + b * n - a * n * 10^len(b) - a * b = 0
    b * a * 10^len(n) - a * b = a * n * 10^len(b) - b * n
    b * a * (10^len(n) - 1) = n * (a * 10^len(b) - b)

    Let:
    d1 = len(n)
    d2 = len(b)

    So: b * a * (10^d1 - 1) = n * (a * 10^d2 - b)

    Solve for n:
    n = (b * a * (10^d1 - 1)) / (a * 10^d2 - b)

    This implies:
    (a * 10^d2 - b) must divide (b * a * (10^d1 - 1))

    We iterate over possible values of d1 (from 1 to 9, since n < N <= 1e9)
    For each d1, we compute 10^d1 - 1
    Then we find divisors of 10^d1 - 1 to enumerate all valid factors
    For each divisor f of (10^d1 - 1), we attempt to find valid `a`, `b`, `n` that satisfy
    the equation.

Time Complexity: O(D * sqrt(10^d1 - 1) * sqrt(B) * log(B)) where D <= 9 is the number of digits
Space Complexity: O(10^5) for precomputed divisors and factorization structures
"""

MX = 10**5 + 10

from functools import cache


@cache
def factor(n):
    # Factorize number n into divisors
    tst = 1
    l = []
    lr = []
    while True:
        if tst * tst > n:
            break
        if tst * tst == n:
            l.append(tst)
            break
        d = n // tst
        if d * tst == n:
            l.append(tst)
            lr.append(d)
        tst += 1
    return l + lr[::-1]


from math import gcd

A, B, N = map(int, input().split())

out = 0

# Precompute divisors of all numbers up to MX
div = [[] for _ in range(MX)]
for i in range(1, MX):
    for j in range(i, MX, i):
        div[j].append(i)

# Precompute a list of pairs (d1, d2) such that gcd(d1, d2) == 1
div2 = [[] for _ in range(MX)]
for i in range(MX):
    for d1 in div[i]:
        for d2 in div[i]:
            if gcd(d2, i // d1) == 1:
                div2[i].append(d1 * d2)

# Iterate over all possible number of digits for n (d1 from 1 to 9)
for d in range(1, 10):
    p = pow(10, d) - 1  # 10^d - 1
    u = factor(p)       # All factors of (10^d - 1)

    pb = 10             # Power of 10 for b based on its digit length
    for b in range(1, B): # Iterate b from 1 to B - 1
        if b == pb:       # Update pb when b crosses a power of 10 (digit increase)
            pb *= 10

        g = gcd(pb, b)    # GCD needed for normalization
        c1 = b // g       # Simplified terms for equation
        c2 = pb // g

        # Try all combinations of factored values and divisor pairs from div2
        for fff in u:
            for gg in div2[c1]:
                ff = fff * gg

                # Compute a based on the derived formula from cross multiplication
                a = (ff + c1) // c2

                if a >= A:    # Skip if a exceeds A
                    continue

                # Check consistency with our derivation (to avoid false positives)
                if a * c2 - c1 != ff:
                    continue

                # Ensure gcd condition
                if gcd(gg, p // fff) != 1:
                    continue

                # Compute n based on the derived formula (solve the equation for n)
                n = (c1 * a * p) // (c2 * a - c1)

                # Filter valid n values in terms of constraints
                if 10 * n >= p and n <= p and n < N:
                    out += 1

print(out)


# https://github.com/VaHiX/CodeForces/