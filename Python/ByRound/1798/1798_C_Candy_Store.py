# Problem: CF 1798 C - Candy Store
# https://codeforces.com/contest/1798/problem/C

"""
Algorithm: 
The problem is about finding the minimum number of price tags needed to describe costs of packs of candies.
We can see that for each candy type i, cost of a pack is c_i = b_i * d_i where d_i divides a_i.
The key idea is to group consecutive candy types such that their pack costs are the same.
This leads to a greedy approach:
1. For each candy type, compute the cost of the pack: b_i * d_i for some valid d_i.
2. We want to minimize number of segments with equal costs.
3. We compute gcd of all costs so far and lcm of b_i values so far.
4. If gcd is not divisible by lcm, we can't group the current element with the previous group.
5. Increment counter and reset the gcd and lcm.

Time Complexity: O(n * sqrt(a_i)) where n is number of candy types and each a_i is processed in sqrt(a_i) time.
Space Complexity: O(1) - only using constant extra space.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]
from math import gcd, lcm


def factors(x, bi):
    # This function appears unused in final code, but might be for factor computation
    paired = set()

    i = 1
    while i * i <= x:
        if x % i == 0:
            paired.add(i * bi)
            if x // i != i:
                paired.add(x // i * bi)
        i += 1
    return paired


t = int(input())
for _ in range(t):
    n = int(input())
    ans = 0

    _gcd = -1
    _lcm = -1

    for right in range(n):
        ai, bi = map(int, input().split())
        val = ai * bi  # cost of pack for current candy type

        if _gcd == -1:  # First element
            _gcd = val
            _lcm = bi
        else:
            # Update gcd of all costs seen so far
            _gcd = gcd(_gcd, val)
            # Update lcm of b_i values seen so far
            _lcm = lcm(_lcm, bi)

        # If gcd is not divisible by lcm, we can't merge this element with last group
        if _gcd % _lcm:
            ans += 1
            _gcd = val  # Reset gcd to current
            _lcm = bi  # Reset lcm to current b_i

    print(ans + 1)  # +1 because we have one more group than transitions


# https://github.com/VaHiX/CodeForces/