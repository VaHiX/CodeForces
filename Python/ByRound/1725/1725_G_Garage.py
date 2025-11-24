# Problem: CF 1725 G - Garage
# https://codeforces.com/contest/1725/problem/G

"""
Code purpose: Find the N-th smallest suitable number for Pak Chanek's garage problem.
The problem involves finding areas of squares that can be formed with specific right triangle configurations.

Algorithm:
1. The problem involves finding areas of squares where the square's area equals a specific formula
2. For a right triangle with sides a and b (where a < b), the area of the square is related to the triangle's dimensions
3. The pattern of suitable numbers follows a mathematical sequence
4. The formula is derived from the mathematical relationship between the triangle sides and square area

Time Complexity: O(1) - Constant time operation
Space Complexity: O(1) - Constant space usage
"""

# The solution uses a mathematical formula to directly compute the N-th suitable number
# The pattern follows a specific sequence where:
# - For n=1, the result is 3
# - For n>1, the result is 4 + (4*n - 3) // 3
print(*(4 + (4 * n - 3) // 3 if n != 1 else 3 for n in [int(input())]))


# https://github.com/VaHiX/CodeForces/