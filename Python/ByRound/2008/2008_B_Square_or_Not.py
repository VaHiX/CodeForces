# Problem: CF 2008 B - Square or Not
# https://codeforces.com/contest/2008/problem/B

# Problem: Check if a binary string could represent a square beautiful matrix.
# A beautiful matrix has 1s on edges and 0s inside.
# Algorithm:
# - For each test case, determine if the string can form a square matrix (r = c)
# - The matrix must have 1s on all edges and 0s in inner positions
# - Key insight: if a square matrix of size n×n exists, then we have:
#   - First row: all 1s
#   - Last row: all 1s
#   - Inner rows: start with 1, end with 1, middle is all 0s (since it's beautiful)
#   - So check if it's possible to partition the string into n rows of length n
#   - And all rows except first and last must start and end with 1 and have all 0s in between
# Time Complexity: O(n) for each test case where n is length of string
# Space Complexity: O(1)

for s in [*open(0)][2::2]:  # Read strings from input, skipping first line (test count)
    print("YNeos"[(s.find("0") - 1) ** 2 != len(s) - 1 :: 2])


# https://github.com/VaHiX/codeForces/