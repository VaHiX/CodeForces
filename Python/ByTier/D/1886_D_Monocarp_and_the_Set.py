# Problem: CF 1886 D - Monocarp and the Set
# https://codeforces.com/contest/1886/problem/D

"""
Algorithm: Dynamic Programming with Modular Arithmetic
Purpose: To count the number of permutations of integers 1..n that produce a given sequence of
         '<', '>', '?' characters when inserted into a set one by one, tracking how each insertion
         affects min/max status.

Time Complexity: O(n + m * log(mod)) where n is the size of string s, and m is number of queries.
Space Complexity: O(n) for storing the string s and auxiliary variables.

The core idea is that:
- When the first element is added, no character is written.
- For subsequent elements:
  - '>' means element is maximum in current set
  - '<' means element is minimum in current set
  - '?' means element is neither min nor max
- The number of valid permutations depends on how many positions in the string are "?"
  and the relative arrangement of elements.
- The count is calculated using modular arithmetic and precomputed values.
"""

import sys

input = lambda: sys.stdin.readline().strip()
n, m = map(int, input().split())
s = [c == "?" for c in input()]  # Convert to boolean array (True for "?", False otherwise)
mod = 998244353
v = 1
for i in range(1, n - 1):
    if s[i]:
        v = (v * i) % mod  # Multiply by i if it's a "?", to account for internal arrangements
out = []
# If first char is "<" or ">", it's invalid since first element can't be min or max
out.append(str(0 if s[0] else v))
for _ in range(m):
    i, c = input().split()
    i = int(i) - 1
    c = c == "?"  # Convert character to boolean
    
    if i > 0 and s[i] != c:
        # If we changed a "?", we need to adjust the value v accordingly
        if c:
            # We're changing from non-"?" to "?"
            # Multiply by i to allow more internal permutations
            v = (v * i) % mod
        else:
            # We're changing from "?" to non-"?" 
            # Divide by i to remove those extra arrangements
            v = (v * pow(i, mod - 2, mod)) % mod  # Modular inverse via Fermat's little theorem
    
    s[i] = c  # Update the string
    out.append(str(0 if s[0] else v))  # Append result for current state
print("\n".join(out))


# https://github.com/VaHiX/CodeForces/