# Problem: CF 1498 A - GCD Sum
# https://codeforces.com/contest/1498/problem/A

"""
Algorithm: GCD Sum
Approach:
- For each input number n, we need to find the smallest number x >= n such that gcd(x, sum_of_digits(x)) > 1.
- We iterate from n upwards, calculating the gcd of the number and its digit sum at each step.
- The loop continues until we find such a number where the gcd is greater than 1.

Time Complexity: O(d * log(min(x, digit_sum))) where d is the number of digits in x, and x is the number we're checking.
Space Complexity: O(d) due to storing the digits of the number as a list.

Techniques:
- Using built-in `gcd` function from math module.
- Converting integer to string to extract digits.
- Using `sum` and `map` functions for digit sum calculation.
"""

from math import *

a = int(input())
for i in range(a):
    b = int(input())
    # Loop until we find a number whose gcd with its digit sum is greater than 1
    while gcd(b, sum(list(map(int, str(b))))) == 1:
        b += 1
    print(b)


# https://github.com/VaHiX/CodeForces/