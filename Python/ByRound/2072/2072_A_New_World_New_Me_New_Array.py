# Problem: CF 2072 A - New World, New Me, New Array
# https://codeforces.com/contest/2072/problem/A

# ==============================================================================
# Problem: Minimum Operations to Achieve Target Sum in Array
# Algorithm/Techniques: Mathematical Optimization
#
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==============================================================================

for s in [*open(0)][1:]:
    n, k, p = map(int, s.split())
    # Calculate the base number of operations needed using ceiling division
    r = -abs(k) // p  # This computes a value related to how many steps of size p are needed
    # The expression (-r <= n) evaluates to True (1) if -r is less than or equal to n, otherwise False (0)
    # Using this boolean as an exponent on r gives us the final result:
    # If -r <= n, then r**1 = r; else r**0 = 1
    print(-(r ** (-r <= n)))


# https://github.com/VaHiX/codeForces/