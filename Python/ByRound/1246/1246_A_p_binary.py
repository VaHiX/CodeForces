# Problem: CF 1246 A - p-binary
# https://codeforces.com/contest/1246/problem/A

"""
Problem: p-binary numbers of the form 2^x + p, where x is a non-negative integer.
We need to represent a given positive integer n as the sum of the minimum number of p-binary numbers.
If impossible, return -1.

Approach:
- Try all possible numbers of summands k from 1 to 100 (since we have tight constraints on n and p).
- For each k, check if it's possible to represent n as sum of exactly k terms.
- Each term has the form 2^x + p, so we can rewrite n = k*p + (sum of 2^x terms).
- Let x = n - k*p, then we need to express x as a sum of at most k powers of 2.
- This is equivalent to checking if the number of 1-bits in binary representation of x is <= k.
- Time Complexity: O(1) since we iterate up to 100 and bit counting is constant for reasonable inputs.
Space Complexity: O(1)

Algorithms/Techniques:
- Bit manipulation (counting 1-bits)
- Greedy approach with small enumeration
"""

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")

n, p = na()

# Try all possible numbers of terms from 1 to 100
for k in range(1, 100):
    x = n - k * p  # Calculate remaining value after subtracting k*p
    if x < k:      # If remaining is less than number of terms, skip (not enough bits)
        continue
    y = 0          # Count the number of 1-bits in binary representation of x
    while x:
        y += x % 2  # Add 1 if last bit is 1
        x //= 2     # Remove last bit
    if y <= k:      # If bits needed <= allowed terms, valid solution
        print(k)
        exit()

print(-1)  # No valid solution found in range


# https://github.com/VaHiX/codeForces/