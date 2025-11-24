# Problem: CF 2140 C - Ultimate Value
# https://codeforces.com/contest/2140/problem/C

"""
C. Ultimate Value

Purpose:
This problem involves a game where Alice and Bob take alternating turns to maximize or minimize the value of a function f(a) defined over an array a, with each turn allowing a swap operation that increases cost by (r - l). Both players play optimally.

The function f(a) is computed as:
f(a) = cost + (a1 - a2 + a3 - a4 + ... ± an)

Approach:
- We precompute the base value of f(a) without any swaps.
- Then simulate the optimal moves based on the parity of indices and attempt to find the best gain from swapping elements, considering both minimizing and maximizing strategies.
- The key part is calculating the maximum possible benefit from a single swap of two elements using a greedy-like approach.

Time Complexity: O(n) per test case
Space Complexity: O(n)

"""

import sys

def input():
    return sys.stdin.readline().strip()

def bmw():
    return map(int, sys.stdin.readline().strip().split())

for _ in range(int(input())):
    n = int(input())
    a = [0] + list(bmw())  # 1-indexed array
    ans = 0
    for i in range(1, n + 1):
        if i % 2 == 1:
            ans += a[i]
        else:
            ans -= a[i]
    
    mao = (n + 1) // 2   # count of odd indices (1-based)
    mie = n // 2         # count of even indices (1-based)
    
    # Compute some initial temp value from the structure
    temp = max(2 * (mao - 1) if mao > 1 else 0, 2 * (mie - 1) if mie > 1 else 0)
    
    negative = mao1 = mie1 = float("-inf")
    
    for i in range(1, n + 1):
        if i % 2 == 1:  # odd index
            if mie1 != negative:
                temp = max(temp, i - 2 * a[i] + mie1)
            mao1 = max(mao1, -i - 2 * a[i])   # Track maximum for future use in even indices
        else:  # even index
            if mao1 != negative:
                temp = max(temp, i + 2 * a[i] + mao1)
            mie1 = max(mie1, -i + 2 * a[i])   # Track maximum for future use in odd indices
    
    print(ans + temp)


# https://github.com/VaHiX/codeForces/