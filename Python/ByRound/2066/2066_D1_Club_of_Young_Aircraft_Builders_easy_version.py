# Problem: CF 2066 D1 - Club of Young Aircraft Builders (easy version)
# https://codeforces.com/contest/2066/problem/D1

"""
Problem: D1. Club of Young Aircraft Builders (easy version)

Purpose:
This code solves a combinatorial problem where we need to count the number of valid ways
to fill in gaps in an array representing the floors from which paper airplanes were launched.
Each gap (0) must be filled with a value from 1 to n, such that:
- From each floor i, at least c airplanes have already been launched before any airplane
  from that floor can be launched.
- A total of m airplanes are launched.

Key Concepts:
- Precomputed factorials and inverse factorials for fast combination calculations
- Mathematical approach using combinations: C(n, k) represents number of ways to choose k items from n items

Algorithms/Techniques:
- Preprocessing factorials and modular inverses using Fermat's little theorem
- Combinatorial counting via combination formula
- Modular arithmetic to handle large results

Time Complexity: O(max(n, m)) preprocessing + O(1) per query
Space Complexity: O(max(n, m))

"""

import sys

input = sys.stdin.readline
mod = 10**9 + 7
FACT = [1]
for i in range(1, 2 * 10**5 + 1):
    FACT.append(FACT[-1] * i % mod)  # Precompute factorials modulo mod
FACT_INV = [pow(FACT[-1], mod - 2, mod)]  # Precompute inverse of last factorial using Fermat's little theorem
for i in range(2 * 10**5, 0, -1):
    FACT_INV.append(FACT_INV[-1] * i % mod)  # Compute inverses backwards
FACT_INV.reverse()  # Reverse to get correct order


def Combi(a, b):
    """Compute combination C(a, b) = a! / (b! * (a-b)! ) mod mod"""
    if 0 <= b <= a:
        return FACT[a] * FACT_INV[b] % mod * FACT_INV[a - b] % mod
    else:
        return 0


t = int(input())
for tests in range(t):
    n, c, m = map(int, input().split())  # Read n floors, minimum c airplanes per floor, total m airplanes
    A = list(map(int, input().split()))  # Array of airplane launchers (0 means unknown)
    x = (n - 1) * c  # Calculate a value based on given constraints for combinations
    print(Combi(x, m - c))  # Output number of valid combinations modulo mod


# https://github.com/VaHiX/codeForces/