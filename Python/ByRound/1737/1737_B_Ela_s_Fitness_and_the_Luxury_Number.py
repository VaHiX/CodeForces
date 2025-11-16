# Problem: CF 1737 B - Ela's Fitness and the Luxury Number
# https://codeforces.com/contest/1737/problem/B

from math import isqrt

# Purpose: Count the number of "luxurious numbers" in the range [l, r].
# A luxurious number x is divisible by floor(sqrt(x)).
# Algorithm:
#   - For each integer k = floor(sqrt(x)), we check when k^2 <= x < (k+1)^2.
#   - In such interval, if x is divisible by k, then it's a luxurious number.
#   - For k, the multiples of k in range [k^2, (k+1)^2 - 1] are k^2, k^2 + k, k^2 + 2k, ...
#   - We count how many such multiples are within [l, r].
#   - Optimized using prefix sums and mathematical formulas to compute counts in O(1).
# Time Complexity: O(1) per test case
# Space Complexity: O(1)

for _ in range(int(input())):
    l, r = map(int, input().split())
    # Compute floor(sqrt(l - 1)) and floor(sqrt(r))
    a, b = isqrt(l - 1), isqrt(r)
    # Compute the count using mathematical formula:
    # - Count of luxurious numbers in [1, r] minus count in [1, l-1]
    print(
        3 * b
        + (b**2 + b <= r)  # Check if b*(b+1) is within range [1, r]
        + (b**2 + 2 * b <= r)  # Check if b*(b+2) is within range [1, r]
        - 3 * a
        - (a**2 + a < l)  # Check if a*(a+1) is less than l
        - (a**2 + 2 * a < l)  # Check if a*(a+2) is less than l
    )


# https://github.com/VaHiX/CodeForces/