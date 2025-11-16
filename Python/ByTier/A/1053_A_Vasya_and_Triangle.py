# Problem: CF 1053 A - Vasya and Triangle
# https://codeforces.com/contest/1053/problem/A

"""
Code Purpose:
This code solves the problem of finding three integer points that form a triangle with a specific area.
The area of the triangle is given by the formula nm/k, where n, m, k are input parameters.
We use a mathematical approach to check if such a triangle exists and construct a valid solution if possible.

Algorithm:
1. First check if it's possible to form a triangle with area nm/k by verifying (n * m * 2) % k == 0.
   If not, then it's impossible and we output "NO".
2. Then use GCD to simplify the fraction nm/k to its lowest terms.
3. Based on the simplified values, construct three points forming a triangle of required area.

Time Complexity: O(log(min(n, k)) + log(min(m, k))) due to GCD computations.
Space Complexity: O(1) as it uses only a constant amount of extra space.
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

n, m, k = na()

# Check if it's possible to form a triangle with area nm/k
# For a triangle with vertices at (0,0), (a,0), (0,b), area = (1/2)*a*b
# So we need (n * m * 2) % k == 0 to ensure the area is integral
if (n * m * 2) % k:
    print("NO")
    exit()

from math import gcd

# Simplify n/k and m/k using GCD to reduce to lowest terms
gn = gcd(n, k)
N = n // gn
k //= gn

gm = gcd(m, k)
M = m // gm
k //= gm

# If k becomes 1 after all simplifications, then we can choose N and M such that area = (1/2)*N*M = nm/k
# In this case, we try to make one of N or M larger so that we can fit within bounds
if k == 1:
    # If N * 2 <= n, then double N, else double M
    if N * 2 <= n:
        N *= 2
    else:
        M *= 2

# Output the result
print("YES")
print(0, 0)
print(N, 0)
print(0, M)


# https://github.com/VaHiX/CodeForces/