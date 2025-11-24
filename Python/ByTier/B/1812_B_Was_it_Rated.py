# Problem: CF 1812 B - Was it Rated?
# https://codeforces.com/contest/1812/problem/B

"""
Task: Determine if a given number n follows a specific pattern
Algorithm: Simple conditional check
Time Complexity: O(1) - Constant time comparison
Space Complexity: O(1) - Constant space usage

The problem checks if n equals 15, 20, or 21. If so, output "NO", otherwise "YES".
This is a straightforward pattern recognition problem with fixed values.
"""

n = int(input())

# Check if n is one of the forbidden values (15, 20, 21)
if n == 15 or n == 20 or n == 21:
    print("NO")
else:
    print("YES")


# https://github.com/VaHiX/CodeForces/