# Problem: CF 2048 A - Kevin and Combination Lock
# https://codeforces.com/contest/2048/problem/A

# ==============================================================================
# Problem: Kevin and Combination Lock
# Purpose: Determine if a given integer x can be reduced to 0 using specific operations:
#   - If x != 33, remove two consecutive '3's (if exist)
#   - If x >= 33, subtract 33
# Algorithm/Technique: Mathematical analysis based on modular arithmetic
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==============================================================================

for i in [*open(0)][1:]:  # Read all input lines, skip first (number of test cases)
    print("YNEOS"[int(i) % 33 > 0 :: 2])  # Output "YES" if x is not divisible by 33, else "NO"


# https://github.com/VaHiX/codeForces/