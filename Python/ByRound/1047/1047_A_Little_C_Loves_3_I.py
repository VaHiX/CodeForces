# Problem: CF 1047 A - Little C Loves 3 I
# https://codeforces.com/contest/1047/problem/A

# ==============================================================================
# Problem: A. Little C Loves 3 I
# Purpose: Split a positive integer n into 3 positive integers a, b, c such that 
#          a + b + c = n and none of them is divisible by 3
# Algorithms/Techniques: Mathematical construction based on modulo 3 analysis
# Time Complexity: O(1) - constant time operations
# Space Complexity: O(1) - constant space usage
# ==============================================================================

n = int(input())
b = 1 + (n % 3 > 1)  # If n mod 3 is greater than 1, set b to 2, otherwise 1
print(1, b, n - b - 1)  # Print a=1, b, and c=n-1-b ensuring none are divisible by 3


# https://github.com/VaHiX/codeForces/