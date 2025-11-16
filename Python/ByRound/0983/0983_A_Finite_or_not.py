# Problem: CF 983 A - Finite or not?
# https://codeforces.com/contest/983/problem/A

"""
Algorithm: Determine if a fraction p/q in base b has a finite representation.
Technique: 
- A fraction p/q in base b has a finite representation if and only if
  all prime factors of the reduced denominator (q/gcd(p,q)) are also
  prime factors of the base b.
- Optimization: To check this, we compute the gcd of p and q,
  reduce the fraction, then test if the reduced denominator divides some power of b.
- We use modular exponentiation to compute large powers efficiently and avoid overflow.

Time Complexity: O(n * log(max(p,q,b))) due to GCD computation and modular exponentiation.
Space Complexity: O(1) excluding input/output storage.
"""

import sys

input()  # Read number of queries, but don't use it
out = []
for line in sys.stdin:
    p, q, b = map(int, line.split())  # Parse the input values
    # Check if all prime factors of q are also factors of b
    # Using a trick: compute p * b^64 mod q and check if result is 0
    # This works because if all prime factors of q are in b, then b^k % q == 0 for some k
    out.append("Infinite" if p * pow(b, 64, q) % q else "Finite")
sys.stdout.write("\n".join(out))


# https://github.com/VaHiX/CodeForces/