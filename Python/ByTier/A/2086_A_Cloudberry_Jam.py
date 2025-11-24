# Problem: CF 2086 A - Cloudberry Jam
# https://codeforces.com/contest/2086/problem/A

# ==============================================================================
# Problem: Cloudberry Jam
# Purpose: Given n jars of jam, determine how many kilograms of cloudberries are needed.
# Algorithm: Mathematical derivation based on the relationship between berries, sugar,
#            and final jam yield with 25% evaporation.
#
# Time Complexity: O(1) - Constant time per test case
# Space Complexity: O(1) - Constant space used
# ==============================================================================

# Read all input lines and skip the first one (which contains number of test cases)
for i in [*open(0)][1:]:
    # Convert input to integer and multiply by 2 to get required berries
    print(2 * int(i))


# https://github.com/VaHiX/codeForces/