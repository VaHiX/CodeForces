# Problem: CF 861 A - k-rounding
# https://codeforces.com/contest/861/problem/A

import math

# =============================================================================
# Problem: k-rounding
# 
# Given a positive integer n and k, find the minimum positive integer x such that:
# 1. x ends with k or more zeros
# 2. x is divisible by n
# 
# Algorithm:
# - For x to end with k zeros, it must be divisible by 10^k
# - For x to be divisible by both n and 10^k, it must be divisible by LCM(n, 10^k)
# - The minimum such x is LCM(n, 10^k)
# 
# Time Complexity: O(log(min(n, 10^k))) due to LCM calculation using GCD
# Space Complexity: O(1) - only using constant extra space
# =============================================================================

n, k = map(int, input().split())
print(math.lcm(n, 10**k))


# https://github.com/VaHiX/CodeForces/