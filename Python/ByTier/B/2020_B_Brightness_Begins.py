# Problem: CF 2020 B - Brightness Begins
# https://codeforces.com/contest/2020/problem/B

# Brightness Begins
# Algorithm: The problem is about finding the minimum n such that after toggling bulbs based on divisors,
#            exactly k bulbs remain on. It turns out that only perfect squares have an odd number of divisors,
#            hence only bulbs at positions that are perfect squares will be on.
#            Therefore, the number of bulbs on after all operations equals the number of perfect squares <= n.
#            This means we want the smallest n such that floor(sqrt(n)) = k.
#            Solving for n: k^2 <= n < (k+1)^2 => n = k^2 is minimal.
#            The computation uses nested square roots to find this efficiently in the code.
# Time Complexity: O(1) per test case due to mathematical insight and fast operations like isqrt
# Space Complexity: O(1) - only using constant extra space

from math import *

for k in [*map(int, open(0))][1:]:
    print(isqrt(isqrt(k) + k) + k)


# https://github.com/VaHiX/codeForces/