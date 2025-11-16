# Problem: CF 1728 E - Red-Black Pepper
# https://codeforces.com/contest/1728/problem/E

# # Red-Black Pepper
# ## Problem Analysis
# This is a problem involving optimal assignment of pepper types to dishes, where we need to determine the maximum tastiness achievable for each shop. The key insight is to model this as a linear Diophantine equation and use dynamic programming with prefix sums to optimize the assignment.

# ### Techniques Used
# - Extended Euclidean Algorithm to solve linear Diophantine equations
# - Linear Diophantine equation solver
# - Prefix sum optimization
# - Modular arithmetic and cycle detection

# ### Time and Space Complexity
# - **Time Complexity**: O(n log n + m * sqrt(n)) where n is the number of dishes and m is the number of shops. The log n factor comes from sorting operations, and sqrt(n) is due to the bounded search space for valid solutions.
# - **Space Complexity**: O(n) for storing prefix sums and dish information.

import io
import math
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def lcm(a, b):
    # Calculate least common multiple of two numbers
    return a * b // math.gcd(a, b)


def extgcd(a, b):
    # Extended Euclidean algorithm to solve ax + by = gcd(a,b)
    # Returns coefficients x, y such that ax + by = gcd(a,b)
    if not b:
        return 1, 0
    u, v = extgcd(b, a % b)
    x, y = v, u - a // b * v
    return x, y


n = int(input())
x = [0] * n
s = 0
# Process each dish and calculate: a_i - b_i for optimization
for i in range(n):
    a, b = map(int, input().split())
    s += b  # cumulative sum of black pepper tastiness
    x[i] = a - b  # difference between red and black pepper tastiness

# Build prefix sum of optimized values
u = [s]  # Start with sum of all black pepper tastiness
# Sort differences in descending order to prioritize dishes with larger red-black difference
for i in sorted(x, reverse=True):
    u.append(u[-1] + i)  # Add cumulative sum
# Find the index where maximum value occurs in prefix sum array
z = u.index(max(u))

m = int(input())
ans = []
for _ in range(m):
    # Process each shop
    x_shop, y_shop = map(int, input().split())
    g = math.gcd(x_shop, y_shop)
    # Check if it's possible to distribute exactly n portions
    if n % g:
        ans0 = -1
        ans.append(ans0)
        continue
    
    # Use extended Euclidean algorithm to find one solution
    x0, y0 = extgcd(x_shop, y_shop)
    x0, y0 = x0 * n // g, y0 * n // g
    
    # Calculate lcm of shop's packages
    l = lcm(x_shop, y_shop)
    # Scale up to get actual solution
    x_shop, y_shop = x_shop * x0, y_shop * y0
    
    # Adjust solution to make x_shop non-negative
    if x_shop < 0:
        # Calculate how many full cycles to add to make it ≥ 0
        c = -x_shop // l + min(-x_shop % l, 1)
        x_shop += l * c
    x_shop %= l  # Normalize to 0 to l-1
    
    # Optimize starting point using prefix sums
    # Adjust x_shop to be close to the optimal point z
    c = max(z - x_shop, 0) // l
    x_shop += l * c
    
    ans0 = -1
    # Check two potentially valid solutions: x_shop and x_shop + l
    # This covers the full cycle range where we might find optimal assignment
    for i in [x_shop, x_shop + l]:
        if i <= n:  # i represents how many red packages to buy
            ans0 = max(ans0, u[i])  # Use prefix sum to get max tastiness
    ans.append(ans0)

# Output all results
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/