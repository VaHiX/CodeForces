# Problem: CF 2091 C - Combination Lock
# https://codeforces.com/contest/2091/problem/C

# C. Combination Lock
# Purpose: For a given n, output a permutation of 1 to n such that every cyclic shift has exactly one fixed point.
# Algorithm: The solution uses a simple pattern:
#   - If n is even, return -1 (no valid permutation exists)
#   - If n is odd and greater than 1, construct a specific permutation
#   - If n is 1, return [1]
# Time Complexity: O(n) per test case
# Space Complexity: O(n) for storing the result

for n in [*open(0)][1:]:  # Read all lines except first (number of test cases) and iterate over them
    n = int(n)  # Convert input string to integer
    print(*([-1], range(n := int(n), 0, -1))[n % 2])  # Print either -1 or the constructed sequence based on parity of n


# https://github.com/VaHiX/codeForces/