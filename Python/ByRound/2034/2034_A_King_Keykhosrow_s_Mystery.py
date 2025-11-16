# Problem: CF 2034 A - King Keykhosrow's Mystery
# https://codeforces.com/contest/2034/problem/A

import math

# Flowerbox description:
"""
Problem: A. King Keykhosrow's Mystery
Purpose: Find the smallest number m such that:
1. m >= max(a, b)
2. (m % a) == (m % b)

This is equivalent to finding the smallest m >= max(a,b) where m mod a = m mod b.
This happens when m ≡ r (mod a) and m ≡ r (mod b), meaning m ≡ r (mod LCM(a,b)).
So we can start from max(a,b) and check multiples of LCM(a,b) to find the smallest valid m.

Algorithms/Techniques: 
- Use of LCM (Least Common Multiple) to determine periodicity
- Check from max(a,b) upward for the first number satisfying both modular conditions

Time Complexity: O(t * log(min(a,b))) where t is number of test cases and log factor comes from GCD computation in LCM
Space Complexity: O(1) - only using a constant amount of extra space
"""

for _ in range(int(input())):
    n, m = map(int, input().split())  # Read two integers a and b
    print(math.lcm(n, m))  # Print the LCM of a and b, which is the answer


# https://github.com/VaHiX/codeForces/