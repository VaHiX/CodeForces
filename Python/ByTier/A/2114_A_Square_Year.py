# Problem: CF 2114 A - Square Year
# https://codeforces.com/contest/2114/problem/A

# =============================================================================
# Problem: Express a 4-digit year as (a + b)^2 where a and b are non-negative integers.
# Algorithm:
#   - For each input string s, convert it to an integer n.
#   - Compute the square root of n, call it r.
#   - Check if r*r equals n. If so, try splitting n into two 2-digit parts a and b
#     such that (a + b)^2 = n.
#   - If valid split found, output a and b; else output -1.
#
# Time Complexity: O(t * log(n)) where t is number of test cases and n is up to 9999.
# Space Complexity: O(1) - only using constant extra space (no arrays, etc.)
# =============================================================================

for n in [*open(0)][1:]:
    # Convert string n to integer
    num = int(n)
    
    # Calculate square root and cast to int
    r = int(num ** 0.5)
    
    # Check if r is exact square root (r*r == num)
    # If not, then no solution exists -> return -1
    # Otherwise, split the number into two parts of 2 digits each:
    # a = first half, b = second half
    # Verify that (a + b)^2 equals original number
    print(*([r := int(t := int(n) ** 0.5), 0], [-1])[r < t])


# https://github.com/VaHiX/codeForces/