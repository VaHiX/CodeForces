# Problem: CF 1761 D - Carry Bit
# https://codeforces.com/contest/1761/problem/D

"""
Code Purpose:
This code computes the number of ordered pairs (a, b) such that 0 <= a, b < 2^n and f(a, b) = k,
where f(a, b) is the number of carries when adding a and b in binary.
The solution uses combinatorics and dynamic programming techniques.

Algorithms/Techniques:
- Preprocessing factorials and their modular inverses for combinations
- Mathematical formula derivation involving binomial coefficients and powers of 3
- Modular arithmetic to handle large numbers

Time Complexity: O(n)
Space Complexity: O(n)
"""

m = 10**9 + 7
fact = [1]  # Factorials modulo m
inv = []    # Modular inverses of factorials modulo m
n, k = map(int, input().split())

# Precompute factorials
for i in range(1, n + 1):
    fact.append((fact[-1] * i) % m)

# Precompute modular inverse of factorials using Fermat's little theorem
inv.append(pow(fact[-1], m - 2, m))  # Modular inverse of last factorial
for i in range(n, 0, -1):
    inv.append((inv[-1] * i) % m)
inv.reverse()  # Reverse to align indices properly

ans = 0
# Loop through possible values of i for the summation
# The sum is up to min(k, n - k + 1) to avoid redundant computation
for i in range(min(k, n - k + 1)):
    # Compute contribution of each term in the series
    ans += (
        fact[k - 1]            # k-1 choose i
        * inv[i]               # i!
        * inv[k - 1 - i]       # (k-1-i)!
        * pow(3, n - 2 - 2 * i, m)  # 3^(n - 2 - 2*i)
        * (n - k)              # (n - k)
        * (2 * i - k + n + 3)  # (2*i - k + n + 3)
        * fact[n - k - 1]      # (n-k-1)!
        * inv[i + 1]           # (i+1)!
        * inv[n - k - i]       # (n-k-i)!
    )
    ans %= m  # Keep result modulo m

# Special cases: if k is 0 or n, handle separately
if k == 0:
    print(pow(3, n, m))
elif k == n:
    print(pow(3, n - 1, m))
else:
    print(ans)


# https://github.com/VaHiX/CodeForces/