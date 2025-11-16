# Problem: CF 1912 B - Blueprint for Seating
# https://codeforces.com/contest/1912/problem/B

"""
Problem: Blueprint for Seating
Algorithm: Dynamic Programming + Mathematical Combinations
Time Complexity: O(k) per test case, where k is the number of aisles
Space Complexity: O(k) for precomputed factorials and inverse factorials

This problem is about finding the minimum inconvenience of seating layouts
with n seats and k aisles, and counting how many such layouts achieve this
minimum inconvenience.

Approach:
- For a given number of seats n and aisles k, we try to distribute n seats
  into k+1 groups (aisles divide the seats into groups).
- Each group of seats contributes to the inconvenience based on seat positions
  relative to the nearest aisle.
- We minimize the sum of distances to nearest aisle across all seats in a row.
- This is solved using combinatorics to count valid arrangements.

We use modular arithmetic throughout and precompute factorials and inverse
factorials for efficient binomial coefficient calculations.
"""

mod = 998244353

# Precompute factorials and inverse factorials for binomial coefficients
M = 2 * (10**5) + 10
fac = [1] * M
ninv = [1] * M
finv = [1] * M
for i in range(2, M):
    fac[i] = fac[i - 1] * i % mod
    ninv[i] = (-(mod // i) * ninv[mod % i]) % mod
    finv[i] = finv[i - 1] * ninv[i] % mod


def binom(n, k):
    """
    Computes binomial coefficient C(n, k) modulo mod
    """
    if n < 0 or k < 0:
        return 0
    if k > n:
        return 0
    return (fac[n] * finv[k] % mod) * finv[n - k] % mod


def solve():
    """
    Solves the seating layout problem for given n (seats) and k (aisles)
    """
    n, k = map(int, input().split())
    # Divide n seats among k+1 groups (k aisles divide into k+1 groups)
    a, b = divmod(n, 2 * k)
    if a == 0:
        # If there are not enough seats to make any group have ≥2 seats,
        # then all groups must have sizes at most one, making inconvenience zero.
        # Count valid combinations using stars and bars.
        print(0, binom(k - 1, n - k - 1) % mod)
        return
    # Compute minimal inconvenience for uniform distribution
    ans1 = k * a * (a - 1) + b * a
    ans2 = 0
    # Sum over valid partitions to count arrangements with minimal inconvenience
    for i in range(b // 2 + 1):
        x = b - 2 * i
        ans2 += binom(k - 1, i) * binom(k + 1 - i, x)
        ans2 %= mod
    print(ans1, ans2)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/