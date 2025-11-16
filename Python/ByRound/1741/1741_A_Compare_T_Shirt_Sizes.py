# Problem: CF 1741 A - Compare T-Shirt Sizes
# https://codeforces.com/contest/1741/problem/A

# ==============================================================================
# Problem: Compare T-Shirt Sizes
# Algorithms/Techniques: String parsing, custom comparison logic
# Time Complexity: O(n) per test case, where n is the length of the input strings
# Space Complexity: O(1) - only using a few variables for computation
# ==============================================================================

for s in [*open(0)][1:]:  # Read all lines except first (number of test cases)
    x, y = ("ML".find(x[-1]) * len(x) for x in s.split())  # Parse sizes into comparable values
    print("=<>"[(x < y) - (y < x)])  # Compare and output result: '<', '>', or '='


# https://github.com/VaHiX/codeForces/