# Problem: CF 2038 L - Bridge Renovation
# https://codeforces.com/contest/2038/problem/L

# ==============================================================================
# L. Bridge Renovation
# 
# Purpose:
#   Calculate the minimum number of standard 60-unit planks needed to cover three bridges
#   with widths 18, 21, and 25 units, requiring 'n' planks per bridge.
#
# Algorithm/Technique:
#   For each bridge width (18, 21, 25), calculate how many 60-unit planks are needed
#   to cover n planks of that width using ceiling division.
#   The total is the sum of these values.
#
# Time Complexity: O(1) - constant time calculation
# Space Complexity: O(1) - only using a few variables
# ==============================================================================

n = int(input())
# For each bridge width (18, 21, 25), compute how many 60-unit planks are needed.
# This is done using ceiling division: (n * width + 59) // 60
# The "+ 59" ensures that we round up correctly when dividing by 60.
print(n - (-n // 6))  # Simplified formula equivalent to sum of ceil(n*wid/60) for wid in [18,21,25]


# https://github.com/VaHiX/codeForces/