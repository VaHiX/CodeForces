# Problem: CF 2044 A - Easy Problem
# https://codeforces.com/contest/2044/problem/A

# =============================================================================
# Problem: Count ordered pairs (a,b) of positive integers such that a = n - b
# Algorithm: Mathematical pattern recognition
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# 
# For any n >= 2, we need positive integers a and b such that a = n - b.
# Since both a and b must be positive integers:
# - b must be at least 1
# - a = n - b must be at least 1, so b <= n-1
# - This gives us range: 1 <= b <= n-1
# - Number of valid values for b equals n-1
# 
# The pattern shows that for any n >= 2, answer is n-1
# =============================================================================
for i in [*open(0)][1:]:  # Read all lines and skip first (test cases count)
    print(int(i) - 1)     # For each n, output n-1 as the answer


# https://github.com/VaHiX/codeForces/