# Problem: CF 2041 B - Bowling Frame
# https://codeforces.com/contest/2041/problem/B

# B. Bowling Frame
# Time complexity: O(1) per test case
# Space complexity: O(1)
# 
# Problem Summary:
# - We are given w white pins and b black pins.
# - We need to build the largest triangular bowling frame possible using these pins.
# - A triangular frame of side length k requires k*(k+1)/2 pins total.
# - Each row in the frame must be uniformly colored (all white or all black).
# 
# Strategy:
# - The maximum number of pins we can use is w + b.
# - Find the largest k such that k*(k+1)/2 <= w + b.
# - This is a mathematical optimization problem solvable via quadratic formula.
# 
# Mathematical derivation:
# 1. Total pins needed for a triangle of side k: k*(k+1)/2
# 2. Solve inequality k*(k+1)/2 <= total_pins
# 3. Rearranging: k^2 + k - 2*total_pins <= 0
# 4. Use quadratic formula: k = (-1 + sqrt(1 + 8*total_pins)) / 2
# 
# The key steps:
# 1. Sum input w and b to get total pins available.
# 2. Apply the derived formula to find maximum possible k.
# 3. Take integer part of result since k must be an integer.

for _ in range(int(input())):
    print(int(((1 + 8 * (sum(map(int, input().split())))) ** 0.5 - 1) / 2))


# https://github.com/VaHiX/codeForces/