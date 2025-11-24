# Problem: CF 2071 A - The Play Never Ends
# https://codeforces.com/contest/2071/problem/A

# ==============================================================================
# Problem: A. The Play Never Ends
# Purpose: Determine if the spectator in the first match can also be the spectator in the k-th match.
# Algorithm: Pattern recognition based on modular arithmetic
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==============================================================================

for k in [*open(0)][1:]:  # Read all lines from stdin, skip first (number of test cases)
    print("YNEOS"[int(k) % 3 != 1 :: 2])  # Check if k % 3 == 1, then "YES", else "NO"


# https://github.com/VaHiX/codeForces/