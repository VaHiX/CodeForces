# Problem: CF 2085 E - Serval and Modulo
# https://codeforces.com/contest/2085/problem/E

"""
E. Serval and Modulo

Purpose:
This code finds a valid "magic number" k such that when each element of array a is taken modulo k,
the resulting array can be shuffled to match the given array b.

Approach:
- We know that sum(a) - sum(b) = t, where t is the total difference due to modular operations.
- The magic number k must divide t (since all remainders must be consistent).
- We check potential divisors of t up to sqrt(t), and for each divisor x > max(b),
  we verify if elements in a mod x can match b by counting occurrences (using maps).
- Also ensures k > max(b) to avoid trivial cases like k=1 or k < max(b).

Time Complexity: O(sqrt(t) * n)
Space Complexity: O(n)

"""

import sys

def input():
    return sys.stdin.readline().strip()

def getints():
    return map(int, sys.stdin.readline().strip().split())

from math import isqrt

for _ in range(int(input())):
    n = int(input())
    a = list(getints())
    bb = list(getints())
    b = {}
    for x in bb:
        if x in b:
            b[x] += 1
        else:
            b[x] = 1
    t = sum(a) - sum(bb) # Difference in sums
    mb = max(bb)
    top = 10**6 + 10
    if t < 0: # If t is negative, impossible to have valid k
        print(-1)
        continue
    f = [10**6 + 5] # Placeholder to ensure loop works
    for i in range(1, isqrt(t) + 1): # Find all divisors of t up to sqrt(t)
        if t % i == 0:
            f.append(i)
            if i != t // i: # Avoid duplicates when i == t/i (perfect square case)
                f.append(t // i)
    for x in f:
        if x <= mb or x > top: # Skip k values that are too small or exceed limit
            continue
        c = {} # Count of remainders in a mod x
        for p in a:
            p = p % x
            if p in c:
                c[p] += 1
            else:
                c[p] = 1
        valid = True
        for p in c:
            if p in b:
                if c[p] != b[p]: # Check if counts match
                    valid = False
                    break
            else:
                valid = False
                break
        if valid:
            print(x)
            break
    else:
        print(-1) # No valid k found


# https://github.com/VaHiX/codeForces/