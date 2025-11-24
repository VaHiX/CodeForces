# Problem: CF 1717 E - Madoka and The Best University
# https://codeforces.com/contest/1717/problem/E

"""
Algorithm: Mathematical approach using Euler's totient function and divisors.

The problem asks to compute the sum of lcm(c, gcd(a,b)) over all triples (a,b,c) such that a+b+c=n.
Key insight:
- For a fixed c, we iterate over all possible values of a+b = n-c.
- For each such pair (a,b), we compute gcd(a,b) and then lcm(c, gcd(a,b)).
- Using the property lcm(x,y) = x*y / gcd(x,y), we have lcm(c, gcd(a,b)) = c * gcd(a,b) / gcd(c, gcd(a,b)) = c * gcd(a,b) / gcd(c, gcd(a,b)) = c * gcd(a,b) / gcd(gcd(c,a), gcd(c,b)).
- But more directly, because we're summing over all valid combinations:
    - For fixed c and a+b = n-c, we can enumerate all divisors d of (n-c) and count how many pairs (a,b) satisfy gcd(a,b) = d.
    - This count corresponds to the number of pairs such that gcd(a,b) = d, which is related to Euler's totient function phi((n-c)/d).

Approach:
1. Precompute Euler's totient function phi for all numbers up to n.
2. Precompute the divisors for each number up to n.
3. For each value of c from 1 to n-2:
   - Let x = n - c, and iterate through all divisors d of x.
   - The number of pairs (a,b) with a+b=x and gcd(a,b)=d is equal to phi(x/d).
   - Add contribution of c * (x/d) / gcd(c, x/d) = c * d to the result.

Time Complexity: O(n log n)
Space Complexity: O(n)
"""

import math

mod = 10**9 + 7
n = int(input())

# Precompute Euler's totient function
phi = list(range(n + 1))
for x in range(2, n + 1):
    if phi[x] == x:
        for y in range(x, n + 1, x):
            phi[y] = phi[y] // x * (x - 1)

# Precompute divisors for each number
divs = [[] for i in range(n + 1)]
for i in range(1, n + 1):
    for j in range(2 * i, n + 1, i):
        divs[j].append(i)

ans = 0
for c in range(1, n - 1):  # c goes up to n-2 since a, b >= 1
    x = n - c
    for d in divs[x]:  # iterate through divisors of x
        cnt = phi[x // d]  # count of pairs (a,b) with gcd(a,b) = d
        # Add contribution: c * d // gcd(c, d) * cnt
        ans += c * d // math.gcd(c, d) % mod * cnt % mod
    ans %= mod

print(ans)


# https://github.com/VaHiX/CodeForces/