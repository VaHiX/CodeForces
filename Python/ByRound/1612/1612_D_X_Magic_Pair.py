# Problem: CF 1612 D - X-Magic Pair
# https://codeforces.com/contest/1612/problem/D

"""
Algorithm: X-Magic Pair Checker
Approach:
- The operations allowed are:
  1. a := |a - b|
  2. b := |a - b|
- These operations are essentially Euclidean algorithm steps, which means
  that after a series of operations, the pair (a, b) will eventually reduce to
  (gcd(a, b), 0) or (0, gcd(a, b)).
- If the pair (a, b) is x-magic, it means that by applying operations, we can
  eventually get either a = x or b = x.
- As the process resembles the Euclidean algorithm, we can exploit the property
  that all numbers reachable in this process are multiples of the GCD of the initial a and b.
- So we first check if x is a multiple of gcd(a, b) — if not, then it's impossible.
- We can simplify the problem by using the Euclidean algorithm to reduce (a, b)
  to (gcd(a,b), 0), or more importantly, reduce (a, b) step by step while keeping
  track of the values in a way that mimics how numbers evolve in GCD process.
- We keep reducing until either a becomes equal to x or we have reached a state
  where we can determine that x is not reachable.
- Special cases like a == b, or when one of the values is 0, are handled.

Time Complexity: O(log(min(a, b))) - Dominated by the number of iterations in Euclidean algorithm.
Space Complexity: O(1) - Only using a constant amount of extra space.
"""

for _ in range(int(input())):
    a, b, x = map(int, input().split())
    # Ensure a >= b to simplify logic
    a, b = (a, b) if a > b else (b, a)
    # If x is greater than maximum of a and b, it's impossible to obtain it
    if x > a:
        print("NO")
        continue
    # Start the Euclidean-like reduction
    a, b = b, a % b
    # Continue until we either find x in the sequence or we know it's impossible
    while (x % a) != b and x <= a and b:
        a, b = b, a % b
    # If we found that x % a == b, then x is reachable
    else:
        print(("NO", "YES")[(x % a) == b])


# https://github.com/VaHiX/CodeForces/